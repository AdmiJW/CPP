#include <cmath>

/*
 * 	This is a Binary Tree Depth First Search - Postorder traversal problem.
 *
 * 	To obtain the 'tilt' of a parent node, we have to first
 * 		>	Find the sum of nodes in left subtree (Left)
 * 		>	Find the sum of nodes in right subtree (Right)
 * 		>	Calculate the absolute difference in the sum of left and right subtree (Parent)
 * 		>	Return the sum to upper level (Left + Right + Parent)
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
	int findTilt(TreeNode* root) {
		int res = 0;
		recurse(root, res);
		return res;
	}

	int recurse(TreeNode* node, int& res) {
		if (!node) return 0;

		int left = recurse(node->left, res);
		int right = recurse(node->right, res);

		res += std::abs(left - right);

		return node->val + left + right;
	}
};