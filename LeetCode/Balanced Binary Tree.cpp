#include <stack>
#include <unordered_map>
using namespace std;

//https://leetcode.com/problems/balanced-binary-tree/
/*
 * 	This is a Binary Tree DFS - Postorder traversal problem.
 *
 * 	For every node, we want to obtain the maximum depth of the left and right subtree. Then, check if the difference
 * 	in depths exceed 1. If it does, it is unbalanced. Otherwise not.
 *
 * 	Instead of top down approach where on each node, we obtain the depths, and if it is ok, recurse to check on child
 * 	nodes, which means the depth is repeatedly obtained, we should be doing bottom up approach.
 *
 * 	In bottom up approach, if the child node is found to be already unbalanced, it will return some kind of flag to
 * 	indicate inbalance, and thus parent node can immediately return false. Otherwise, return the maximum depth of the
 * 	child node. Only then, parent node is able to compare immediately and return result without having to recurse into
 * 	child nodes again.
 *
 * 	-----------------------------------------------------------------
 *
 * 	An iterative method can be implemented using HashMaps. See on Binary_Tree/Binary_Tree_Postorder_Traversal for more
 * 	information on how to implement post order traversal using Stack.
 *
 * 	Once the nodes are ready in post order form in Stack, we should pop the nodes.
 * 	For every node, we query the depth of left child and right child using the HashMap. If absent, simply get default value
 * 	of 0.
 * 	Compare the depths and immediately return if found imbalance.
 *
 * 	-----------------------------------------------------------------------
 *
 * 	Again, 1 Stack method is entirely possible. Also see Binary_Tree/Binary_Tree_Postorder_Traversal
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
	bool isBalanced(TreeNode* root) {
		return recurse(root, 1) != 1;
	}
	int recurse(TreeNode* node, int depth) {
		if (!node) return depth - 1;

		int leftDepth = recurse(node->left, depth + 1);
		if (leftDepth == -1) return -1;		//	Early termination. No need search right subtree

		int rightDepth = recurse(node->right, depth + 1);

		if (rightDepth = -1 || abs(rightDepth - leftDepth) >= 2) return -1;
		return max(leftDepth, rightDepth);
	
	}



	bool isBalanced2(TreeNode* root) {
		if (!root) return true;

		stack<TreeNode*> temp;
		stack<TreeNode*> stack;
		temp.push(root);

		while (!temp.empty()) {
			TreeNode* pop = temp.top(); temp.pop();
			stack.push(pop);

			if (pop->left) temp.push(pop->left);
			if (pop->right) temp.push(pop->right);
		}

		unordered_map<TreeNode*, int> depth;

		while (!stack.empty()) {
			TreeNode* pop = stack.top(); stack.pop();
			auto gotleft = depth.find(pop->left);
			auto gotright = depth.find(pop->right);

			int leftdeep = gotleft == depth.end() ? 0 : gotleft->second;
			int rightdeep = gotright == depth.end() ? 0 : gotright->second;
		
			if (abs(leftdeep - rightdeep) >= 2) return false;
			depth[pop] = max( leftdeep, rightdeep ) + 1;
		}
		return true;
	}


	bool isBalanced3(TreeNode* root) {
		if (!root) return true;

		stack<TreeNode*> stack;
		TreeNode* last;
		TreeNode* curr = root;
		unordered_map<TreeNode*, int> depth;

		while (curr || !stack.empty()) {
			if (curr) {
				stack.push(curr);
				curr = curr->left;
			}
			else {
				curr = stack.top();

				if (!curr->right || curr->right == last) {
					stack.pop();
					
					auto findL = depth.find(curr->left);
					auto findR = depth.find(curr->right);

					int left = findL == depth.end() ? 0 : findL->second;
					int right = findR == depth.end() ? 0 : findR->second;

					if (abs(left - right) >= 2) return false;
					depth[curr] = max(left, right) + 1;
					last = curr;
					curr = nullptr;
				}
				else {
					curr = curr->right;
				}
			}
		}
		return true;
	}
};