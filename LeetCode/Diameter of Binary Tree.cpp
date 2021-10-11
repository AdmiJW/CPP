#include <vector>
using namespace std;

//https://leetcode.com/problems/diameter-of-binary-tree/
/*
 * This is a binary tree problem.
 *
 * This problem can be broken down into the same problem for each subnode, thus the use of recursion here.
 * The idea is, the longest diameter is simply the maximum depth of left subtree + maximum depth of right subtree for a given parent node
 * (root). However, we don't necessary need to pass through the root node of the original problem, Instead, every node in the tree can
 * potentially become the root node that is passed through in the diameter. Therefore take into account of that.
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
	int res = 0;

	int diameterOfBinaryTree(TreeNode* root) {
		getDepthAndUpdateRes(root);
		return res;
	}

	int getDepthAndUpdateRes(TreeNode* root) {
		if (!root) return 0;
		// Get depth of both sides of the tree.
		int left = getDepthAndUpdateRes(root->left);
		int right = getDepthAndUpdateRes(root->right);

		// If I connected left and right subtree, will it give me longest diameter?
		res = max(res, left + right);
		// Return maximum depth of this subtree.
		return max(left, right) + 1;
	}
};