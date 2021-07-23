
//https://leetcode.com/problems/binary-tree-pruning/
/*
 * 	This is a easy-medium Binary Tree, DFS (Postorder Traversal) problem.
 *
 * 	Given a node and asked to prune it, we need to do the same thing to left and right subtree.
 * 	At the end of pruning both subtree, if they ended up being completely pruned (null), and current node is 0 as well,
 * 	prune current node.
 *
 * 	Base case is when node is null, then we return null.
 * 	Otherwise, return null only when after pruning both subtrees, both left and right are null, and node val is 0
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
	TreeNode* pruneTree(TreeNode* root) {
		if (!root) return nullptr;

		root->left = pruneTree(root->left);
		root->right = pruneTree(root->right);
		if (!root->left && !root->right && !root->val)
			return nullptr;
		return root;
	}
};