#include <cmath>
#include <stack>
#include <queue>

using namespace std;

//https://leetcode.com/problems/maximum-depth-of-binary-tree/

/*
 * 	This is a BFS / DFS Tree Traversal problem.
 *
 * 	It is most easily solved using recursion in 2 lines.
 * 	For BFS, we just count the possible levels there is. For DFS, we just record the level that each node is at, and update the
 * 	maximum value each time.
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
	int maxDepth(TreeNode* root) {
		if (!root) return 0;
		return 1 + fmax( maxDepth(root->left), maxDepth(root->right) );
	}

	
	int maxDepthBFS(TreeNode* root) {
		if (!root) return 0;
		
		queue<TreeNode*> bfs;
		bfs.push(root);

		int res = 0;

		while (!bfs.empty()) {
			res++;
			int size = bfs.size();
			while (size-- > 0) {
				auto node = bfs.front();
				bfs.pop();
				if (node->left) bfs.push(node->left);
				if (node->right) bfs.push(node->right);
			}
		}
		return res;
	}
	



	int maxDepthDFS(TreeNode* root) {
		if (!root) return 0;

		stack<pair<TreeNode*, int>> stack;
		stack.emplace(make_pair(root, 1));

		int res = 0;

		while (!stack.empty()) {
			auto pair = stack.top();
			stack.pop();
			res = fmax(pair.second, res);
			if (pair.first->left)
				stack.emplace(make_pair(pair.first->left, pair.second + 1) );
			if (pair.first->right)
				stack.emplace(make_pair(pair.first->right, pair.second + 1) );
		}
		return res;
	}
};
