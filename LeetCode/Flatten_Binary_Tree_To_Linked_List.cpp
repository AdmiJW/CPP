#include <stack>
using namespace std;

//https://leetcode.com/problems/flatten-binary-tree-to-linked-list/
/*
 * 	This is a tree, Depth first search - Preorder traversal problem
 *
 * 	Multiple solutions available. See below for a bit of explaination
 */

struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode() : val(0), left(nullptr), right(nullptr) {}
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
	TreeNode(int x, TreeNode* left, TreeNode* right): val(x), left(left), right(right) {}
};


class Solution {
public:
	//	Initial attempt - Top down, flatten left then right idea
	//	Recursive function takes in parent and child and
	//	returns the lastly connected node
	//	will connect parent with child in right subtree
	void flatten(TreeNode* root) {
		recurse(new TreeNode, root);
	}
	TreeNode* recurse(TreeNode* parent, TreeNode* child) {
		if (!child) return parent;
		TreeNode* right = child->right;

		parent->right = child;
		TreeNode* last = recurse(child, child->left);
		child->left = nullptr;
		return recurse(last, right);
	}


	//	Recursive solution - Right - Left- Root reversed postorder
	//	Idea is that the recursion will flatten right subtree first, returning
	//	the head of flattened subtree. Then, pass in the head of right flattened to flatten
	//	left subtree, then finally connect with the root node.
	void flatten2(TreeNode* root) {
		recurse2(root, nullptr);
	}
	TreeNode* recurse2(TreeNode* root, TreeNode* prev) {
		if (!root) return prev;
		prev = recurse2(root->right, prev);
		prev = recurse2(root->left, prev);
		root->right = prev;
		root->left = nullptr;
		return root;
	}


	//	Iterative method using Stack. This one is less intuitive.
	//	For each node on stack, push right node, then left node. Now
	//	the top of stack should be left node if exists, else right node.
	//	If none, it will be previous node's right or left node
	void flatten3(TreeNode* root) {
		if (!root) return;
		stack<TreeNode*> stack;
		stack.push(root);

		while (!stack.empty()) {
			TreeNode* top = stack.top(); stack.pop();
			if (top->right) stack.push(top->right);
			if (top->left) stack.push(top->left);
			if (!stack.empty()) top->right = stack.top();
			top->left = nullptr;
		}
	}


	//	Iterative method in O(1) space using Morris Traversal algorithm inspired idea.
	//	The idea is, say a node doesn't have left subtree. This means it is already nicely
	//	linked list!
	//	But if it has a left subtree, grab the last node called predecessor which is the last
	//	if I perform preorder traversal, and connect it to the current node's right, which is
	//	what it is supposed to connect.
	//	Then move current node's left to right. Set left to null and you're done.
	void flatten4(TreeNode* root) {
		while (root) {
			if (root->left) {
				TreeNode* predecessor = root->left;
				while (predecessor->right)
					predecessor = predecessor->right;
				predecessor->right = root->right;
				root->right = root->left;
				root->left = nullptr;
			}
			root = root->right;
		}
	}

};