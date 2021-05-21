#include <vector>
#include <queue>
using namespace std;

//https://leetcode.com/problems/binary-tree-level-order-traversal/
/*
 * 	A very standard breadth first search problem.
 *
 * 	Using a Queue, we can traverse the binary tree layer by layer, fairly easily.
 * 	That's all I have to say actually
 */

struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode(): val(0), left(nullptr), right(nullptr) {}
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
	TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

class Solution {
public:
	vector<vector<int>> levelOrder(TreeNode* root) {
		vector<vector<int>> res;
		if (!root) return res;

		queue<TreeNode*> queue;
		queue.push(root);

		while (!queue.empty()) {
			int width = queue.size();
			vector<int> layer;

			while (width--) {
				TreeNode* node = queue.front(); queue.pop();
				layer.push_back(node->val);
				if (node->left) queue.push(node->left);
				if (node->right) queue.push(node->right);
			}
			res.push_back(layer);
		}
		return res;
	}
};