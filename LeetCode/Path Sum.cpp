using namespace std;

//https://leetcode.com/problems/path-sum/
/*
 * 	A simple Tree DFS problem.
 *
 * 	Every subtree is simply a subproblem. We have to minus the node.val from targetSum every node, and see if it
 * 	can be reduced to 0 at a leaf node.
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
	bool hasPathSum(TreeNode* root, int targetSum) {
		if (!root) return false;

		int newTarget = targetSum - root->val;
		if ( !(root->left) && !(root->right) ) return newTarget == 0;
		return hasPathSum(root->left, newTarget) || hasPathSum(root->right, newTarget);
	}
};