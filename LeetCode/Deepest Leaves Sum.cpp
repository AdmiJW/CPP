#include <queue>
using namespace std;

//https://leetcode.com/problems/deepest-leaves-sum/
/*
 * 	This is a BFS Level order traversal / DFS problem
 *
 * 	For deepest level in a Tree, it is best performed using a level order traversal using Queue. On every level,
 * 	we pop out the nodes at the layer, and sum their values.
 * 	If after popping all the nodes and there's no nodes left in the Queue, it is the final layer. Return immediately.
 *
 * 	-------------------------------------
 *
 * 	For DFS however, we need to record 2 information: deepestLayer and the sum of that deepest layer so far.
 * 	We perform preorder traversal on each node, and in the node, check its layer with deepest layer.
 *
 * 	>	If currLayer = deepestLayer, add the node value to the sum.
 * 	>	If currLayer > deepestLayer, reset sum to 0. Don't forget to add the current node value too.
 *
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
	//	Level order BFS traversal solution
	int deepestLeavesSum(TreeNode* root) {
		if (!root) return 0;

		queue<TreeNode*> queue;
		queue.push(root);

		while (!queue.empty()) {
			int size = queue.size();
			int sum = 0;

			while (size--) {
				TreeNode* node = queue.front(); queue.pop();
				sum += node->val;
				if (node->left) queue.push(node->left);
				if (node->right) queue.push(node->right);
			}

			if (queue.empty()) return sum;
		}
		return 0;
	}



	//	DFS solution. An mutable array is used for state recording {maxDepth, sum}
	int deepestLeavesSum2(TreeNode* root) {
		int* record = new int[2]{ 0,0 };
		dfs(root, 1, record);
		int res = record[1];
		delete[] record;
		return res;
	}
	void dfs(TreeNode* root, int depth, int* record) {
		if (!root) return;
		if (depth > record[0]) {
			record[0] = depth;
			record[1] = 0;
		}
		if (depth == record[0]) record[1] += root->val;

		dfs(root->left, depth + 1, record);
		dfs(root->right, depth + 1, record);
	}
};