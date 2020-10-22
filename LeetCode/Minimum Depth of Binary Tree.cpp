

#include <queue>

/*
	This is mainly a BFS problem.

	Sure we can surely solve this problem by DFS. However with DFS, we have to traverse through all the nodes in order to ensure
	the minimum depth is found. Imagine a tree where the left subtree has a depth of 500 and right subtree with only depth of
	1. In this case DFS always has to traverse through all the nodes to reach the solution.

	Instead, we shall perform BFS algorithm instead. We will be travelling level by level, and once on a level a node is found to
	be leaf node, immediately return the result.

*/

struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode() : val(0), left(nullptr), right(nullptr) {}
	TreeNode(int v) : val(v), left(nullptr), right(nullptr) {}
	TreeNode(int v, TreeNode* left, TreeNode* right) :
		val(v), left(left), right(right) {}
};

class Solution {
public:
	int minDepth(TreeNode* root) {
		if (root == nullptr) return 0;

		std::queue<TreeNode*> nodes;
		nodes.push(root);
		int level = 0;
		int elements = 0;

		while (!nodes.empty()) {
			elements = nodes.size();
			level += 1;

			while (elements-- > 0) {
				TreeNode* popped = nodes.front();
				nodes.pop();

				if (popped->left == nullptr && popped->right == nullptr) {
					return level;
				}
				if (popped->left != nullptr) {
					nodes.push(popped->left);
				}
				if (popped->right != nullptr) {
					nodes.push(popped->right);
				}
			}
		}
		return 0;
	}
};