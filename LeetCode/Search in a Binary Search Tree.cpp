//https://leetcode.com/problems/search-in-a-binary-search-tree/
/*
 * Simple binary search tree problem. Just find according to binary search tree rules and see if it is found or leads to null.
 */


struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode() : val(0), left(nullptr), right(nullptr) {}
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
	TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}x
};

class Solution {
public:
	TreeNode* searchBST(TreeNode* root, int val) {
		if (!root) return nullptr;
		if (root->val == val) return root;
		if (root->val > val) return searchBST(root->left, val);
		return searchBST(root->right, val);
	}
};