#include <vector>
#include <queue>
using namespace std;

class Node {
public:
	int val;
	vector<Node*> children;
	Node() {}
	Node(int _val) : val(_val) {}
	Node(int _val, vector<Node*> _children) : val(_val), children(_children) {}
};

//https://leetcode.com/problems/n-ary-tree-level-order-traversal/
/*
 *  This is a BFS, level order traversal problem of tree.
 *
 *  For BFS, we use queue for the job, recording the size of the layer in each iteration so we don't interfere
 *  between levels.
 */

class Solution {
public:
	vector<vector<int>> levelOrder(Node* root) {
		vector<vector<int>> res;
		if (!root) return res;

		queue<Node*> bfs;
		bfs.push(root);

		while (!bfs.empty()) {
			res.push_back({});
			for (int i = bfs.size(); i > 0; --i) {
				Node* poll = bfs.front();
				bfs.pop();
				res.back().push_back(poll->val);
				for (Node* child : poll->children)
					bfs.push(child);
			}
		}
		return res;
	}
};