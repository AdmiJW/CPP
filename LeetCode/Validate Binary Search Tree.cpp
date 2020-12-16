#include <stack>
#include <utility>
using namespace std;
typedef long long int LONG;

/ https://leetcode.com/problems/validate-binary-search-tree/
/*
 * 	This is a BST DFS - Preorder Traversal or Inorder traversal problem
 *
 *  Every node, the left subtree must only have the value at maximum up to the current node's value. Similarly,
 *  the right subtree must only have the value at minimum from the current node's value.
 *
 *  This can be done using pre order traversal. Every recursive call we would pass in the boundary where the node
 * 	is valid. As soon as detect the value of the node does not fall in valid range, immediately return false, which
 * 	will then be returned up to the recursion stack.
 *
 * 	Preorder traversal iteratively is very intuitive. Explore node, push both sides into stack and continue
 *
 * 	----------------------------------------------------------------------
 *
 * 	Recall the property of Inorder traversal of BST - The values will be recorded as if it is sorted. Therefore,
 * 	for a valid BST, the values recorded must always be sorted from smallest to largest. If during the traversal
 * 	we detect some value disrupts the STRICTLY INCREASING ORDER, immediately return false
 *
 * 	As well, this is done more easily using global variable (or mutable variable) with recursion
 *
 * 	To implement Inorder Travversal using iterative approach is also plausible. However, the method is not as
 * 	intuitive. See the algorithm:
 *
 * 		>	While root has left subtree, push to stack and makee root as left subtree itself
 * 		>	Now root shall be null. Pop the top of stack to be root, which is leftmost node of current tree
 * 		>	Do something with that node
 * 		>	Explore the right subtree. Set root to right, and while root has left subtree, push to stack and
 * 			make root as left subtree.
 */

struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode() : val(0), left(nullptr), right(nullptr) {}
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
	TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};


class Solution {
public:
	// Recursive method using Preorder Traversal
	bool isValidBST(TreeNode* root) {
		return validate(root, INT64_MIN, INT64_MAX);
	}
	bool validate(TreeNode* node, LONG left, LONG right) {
		if (!node) return true;
		if (node->val <= left || node->val >= right) return false;

		return validate(node->left, left, node->val) && validate(node->right, node->val, right);
	}




	// Iterative method using Preorder traversal
	bool isValidBST2(TreeNode* root) {
		if (!root) return true;

		stack<TreeNode*> dfs;
		stack< pair<LONG, LONG> > minmax;
		dfs.push(root);
		minmax.push(make_pair(INT64_MIN, INT64_MAX));

		while (!dfs.empty()) {
			TreeNode* node = dfs.top(); dfs.pop();
			auto bound = minmax.top(); minmax.pop();

			if (bound.first >= node->val || bound.second <= node->val)
				return false;

			if (node->left) {
				dfs.push(node->left);
				minmax.push(make_pair(bound.first, node->val));
			}

			if (node->right) {
				dfs.push(node->right);
				minmax.push(make_pair(node->val, bound.second));
			}
		}
		return true;
	}


	LONG prev = INT64_MIN;
	// Inorder traversal method
	bool isValidBST3(TreeNode* root) {
		return isValid(root);
	}
	bool isValid(TreeNode* node) {
		if (!node) return true;
		if (!isValid(node->left)) return false;
		if (node->val > prev) {
			prev = node->val;
			return isValid(node->right);
		}
		return false;
	}


	// Inorder Traversal method using iteratively
	bool isValidBST4(TreeNode* root) {
		stack<TreeNode*> rootStacks;

		while (root) {
			rootStacks.push(root);
			root = root->left;
		}

		while (!rootStacks.empty()) {
			root = rootStacks.top(); rootStacks.pop();
			if (root->val > prev) prev = root->val;
			else return false;
			root = root->right;

			while (root) {
				rootStacks.push(root);
				root = root->left;
			}
		}
		return true;
	}


};