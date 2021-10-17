#include <vector>
#include <unordered_map>
using namespace std;

//https://leetcode.com/problems/path-sum-iii/submissions/
/*
*	This is a DFS (and kinda backtracking) problem.
* 
*	On recursion of every node, we can have a 'queue' kinda data structure that keep track of every node we have encountered along the path.
*	Then, we can iterate through the path to perform a "Suffix sum" to determine if there is any path that sums up to target, that must end at
*	current node.
* 
*	However, the time complexity of this algorithm goes up to O(ND) where N = number of nodes, D = max depth of tree, worst case O(N^2) if is linear
* 
*	---------------------
* 
*	(Solution)
* 
*	Instead, if we keep a reference (map) to prefix sum -> frequency, what can it do?
*	A prefix sum keep track of available paths from root node to current node. On recursion, we know the sum from root node to current node.
*	Now, if we want to know if there is any intermediate paths, we know we have to eliminate some path that starts with root to somewhere, which
*	we'll look it up in the map in O(1) time.
* 
*	The time complexity is thus reduced to O(N).
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


	// O(N^2) DFS solution
	int pathSum(TreeNode* root, int targetSum) {
		vector<int> path;
		return pathSum(root, targetSum, path);
	}

	int pathSum(TreeNode* node, int target, vector<int>& path) {
		if (!node) return 0;

		path.push_back(node->val);
		int res = 0, backwardSum = 0;
		for (int i = path.size() - 1; i >= 0; --i) {
			backwardSum += path[i];
			if (backwardSum == target) ++res;
		}
		res += pathSum(node->left, target, path);
		res += pathSum(node->right, target, path);
		path.pop_back();
		return res;
	}



	// O(N) solution using prefix sum (Not from root->leaf, but leaf->root)
	int pathSum2(TreeNode* root, int targetSum) {
		unordered_map<int, int> freq;
		freq[0] = 1;
		return pathSum2(root, targetSum, 0, freq);
	}

	int pathSum2(TreeNode* node, int target, int curr, unordered_map<int, int>& freq) {
		if (!node) return 0;

		curr = curr + node->val;
		int res = 0;
		if (freq.count(curr - target))
			res = freq[curr - target];

		++freq[curr];
		res += pathSum2(node->left, target, curr, freq);
		res += pathSum2(node->right, target, curr, freq);
		--freq[curr];
		return res;
	}
};