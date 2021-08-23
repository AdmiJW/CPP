#include <unordered_set>
#include <stack>
using namespace std;

//https://leetcode.com/problems/two-sum-iv-input-is-a-bst/
/*
 * This is a BST problem.
 *
 * Firstly, we can apply the original solution to two sum problem - using a HashSet to check presence of a
 * value.
 * Perform DFS on the tree. For each node, check if k - node.val existed in Set or not. If yes, return true.
 * if not, record node value in Set and continue.
 *
 * -------------------------
 *
 * Another solution with better space complexity (O(H)) where H is height of tree, is to utilize BST property-
 * ability to find value in O(Log N) time. FOr each node, find if the node with k - node.val is present in the
 * tree or not.
 * 	This will use O(N log N) time and O(log N) stack space, assuming tree is balanced.
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

	// DFS with a HashSet solution
	bool findTarget(TreeNode* root, int k) {
		unordered_set<int> set;
		return dfs(root, k, set);
	}

	// Performs in order traversal on tree to see if two numbers can form to k
	bool dfs(TreeNode* node, int k, unordered_set<int>& prev) {
		if (!node) return false;

		// Check if using this node's value, can we form k?
		if (prev.count(k - node->val)) return true;
		// Record current node
		prev.insert(node->val);

		//Search left & Right subtree
		return dfs(node->left, k, prev) || dfs(node->right, k, prev);
	}




	// O(log N) - Assume optimized tree - stack space solution - Nested DFS
	bool findTarget2(TreeNode* root, int k) {
		if (!root) return false;
		stack<TreeNode*> dfs;
		dfs.push(root);

		while (!dfs.empty()) {
			TreeNode* node = dfs.top();
			dfs.pop();
			if (find(root, k - node->val, node)) return true;

			if (node->right) dfs.push(node->right);
			if (node->left) dfs.push(node->left);
		}
		return false;
	}

	bool find(TreeNode* node, int t, TreeNode* ignored) {
		if (!node) return false;
		return node->val == t && node != ignored || find((node->val < t) ? node->right : node->left, t, ignored);
	}
};