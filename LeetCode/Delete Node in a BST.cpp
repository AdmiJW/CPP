//https://leetcode.com/problems/delete-node-in-a-bst/
//	For introduction to deleting nodes in BST, see TOPICS -> DATA_STRUCTURES -> BINARYSEARCHTREE


using namespace std;


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

	TreeNode* deleteNode(TreeNode* root, int key) {
		// Cases - Either root is null, or root is not the node we are looking to delete.
		if (!root) return nullptr;
		if (root->val > key) {
			root->left = deleteNode(root->left, key);
			return root;
		}
		if (root->val < key) {
			root->right = deleteNode(root->right, key);
			return root;
		}

		// Cases - root is the node we want to delete
		// 1 - Root has both childs - We have to locate the replacer, and delete it from where the replacer originally was
		if (root->left && root->right) {
			// Algorithm to find leftmost node in right subtree
			TreeNode* replacor = root->right;
			while (replacor->left)
				replacor = replacor->left;

			// Replace current node (to delete) with replacor's value
			root->val = replacor->val;

			// Remove replaced node from where it was
			root->right = deleteNode(root->right, replacor->val);

			return root;
		}
		// 2 - Root has only one child or no child at all.
		return (root->left) ? root->left : root->right;
	}

};