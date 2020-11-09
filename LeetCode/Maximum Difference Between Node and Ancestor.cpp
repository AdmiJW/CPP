#include <cmath>
#include <array>

/*
 * 	This is a Binary Tree Depth First Search problem
 *
 * 	There is 2 approach - Top down or bottom up. Top down is easier to implement and more clean. However I first came up
 * 	with bottom up.
 *
 * 	To find the maximum difference between node and ancestor, we could have a recursion function that returns the
 * 	maximum node and minimum node of the left and right subtree. Then, we could try to find the difference from those
 * 	max and min, updating the global variable when a greater difference was found.
 *
 * 	----------------------------------
 *
 * 	Instead of having a recursion function which reports the maximum and minimum value in subtree, why don't we just
 * 	report the maximum and minimum value of the ancestors down to the child nodes?
 * 	Since taking the absolute difference makes no difference whether it is child - ancestor or ancestor - child,
 * 	implementing this way is much more elegant, and clean
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
	int maxAncestorDiff(TreeNode* root) {
		if (!root) return 0;
		
		int res = 0;
		recurse(root, res);

		return res;
	}

	void recurse(TreeNode* node, int min, int max, int& res) {
		if (!node) return;

		res = std::fmax(res, std::abs(node->val - min));
		res = std::fmin(res, std::abs(node->val - max));

		recurse(node->left, std::min(min, node->val), std::max(max, node->val), res);
		recurse(node->right, std::min(min, node->val), std::max(max, node->val), res);
	}



	std::array<int, 2> recurse(TreeNode* node, int& res) {
		std::array<int, 2> left = { node->val, node->val };
		std::array<int, 2> right = { node->val, node->val };
		if (node->left) 
			left = recurse(node->left, res);
		if (node->right)
			right = recurse(node->right, res);

		int max = INT_MIN;
		int min = INT_MAX;
		for (int i : left) {
			max = std::fmax(max, i); min = std::fmin(min, i);
		}
		for (int i : right) {
			max = std::fmax(max, i); min = std::fmin(min, i);
		}

		res = std::fmax(res, std::abs(node->val - max));
		res = std::fmax(res, std::abs(node->val - min));

		return std::array<int, 2>{ {
			std::fmin(node->val, min),
			std::fmax(node->val, max)
		} };
	}
};