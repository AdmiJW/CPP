#include <vector>
using namespace std;

struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode() : val(0), left(nullptr), right(nullptr) {}
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
	TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

//https://leetcode.com/problems/path-sum-ii/
/*
 * 	This is a backtracking, tree DFS problem.
 *
 * 	We have to find path from ROOT to LEAF where SUM=TARGET.
 *
 * 	Since we have to record paths, using DFS with backtracking is the ideal choice here instead of BFS, as it has
 * 	difficulties tracking the path
 */

class Solution {
public:

	vector<vector<int>> pathSum(TreeNode* root, int targetSum) {
		vector<vector<int>> res;
		if (!root) return res;

		vector<int> path;
		backtrack(root, targetSum, path, res);
		return res;
	}

	void backtrack(TreeNode* curr, int target, vector<int>& path, vector<vector<int>>& res) {
		target -= curr->val;
		path.push_back(curr->val);

		// Successfully sum to target and it is a leaf node.
		if (!curr->left && !curr->right && !target) {
			res.emplace_back( vector<int>(path) );
		}
		// Otherwise, it may be (Not equal to sum), or (is not leaf node)
		else {
			if (curr->left)
				backtrack(curr->left, target, path, res);
			if (curr->right)
				backtrack(curr->right, target, path, res);
		}

		// Remove current value before returning
		path.pop_back();
	}

};
