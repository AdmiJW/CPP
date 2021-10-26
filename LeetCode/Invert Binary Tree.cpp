//https://leetcode.com/problems/invert-binary-tree/
/*
* This is a binary tree problem.
* 
* A common binary tree problem. To invert a tree, simply flip every node's left
* subtree and right subtree. Perform this on every node in the tree.
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
	
	TreeNode* invertTree(TreeNode* root) {
		if (!root) return nullptr;
		TreeNode* temp = root->left;
		root->left = root->right;
		root->right = temp;

		invertTree(root->left);
		invertTree(root->right);
	}
};