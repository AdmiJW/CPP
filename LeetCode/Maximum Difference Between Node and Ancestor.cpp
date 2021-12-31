#include <cmath>
#include <vector>
using namespace std;

//https://leetcode.com/problems/maximum-difference-between-node-and-ancestor/
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
		return recurse(root, root->val, root->val);
	}

	// Returns the maximum absolute difference of descendant's value with ancestor's value 
	int recurse(TreeNode* root, int minVal, int maxVal) {
		if (!root) return 0;
		int val = root->val;
		int localMax = max( abs(val - minVal), abs(val - maxVal));

		return max(
			localMax,
			max(
				recurse(root->left, min(val, minVal), max(val, maxVal)),
				recurse(root->right, min(val, minVal), max(val, maxVal))
			)
		);
	}

};