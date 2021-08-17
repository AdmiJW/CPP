#include <vector>
using namespace std;

//https://leetcode.com/problems/count-good-nodes-in-binary-tree/
/*
 *	A fairly simple DFS / BFS recursion binary tree problem.
 *
 * 	Every node that we visit, if we have the information about the maximum value from root to current node,
 * 	then I am able to know the number of good nodes in the tree by the recurrence relation:
 *
 * 		(is myself a good node?) + (good node in left subtree) + (good node in right subtree).
 *
 * 	Therefore we always pass the maximum value seen so far into the recursion
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
	int goodNodes(TreeNode* root) {
		return goodNodes(root, INT32_MIN);
	}

	int goodNodes(TreeNode* root, int m) {
		if (!root) return 0;
		m = max(root->val, m);

		return (root->val >= m ? 1 : 0) + goodNodes(root->left, m) + goodNodes(root->right, m);
	}
};