#include <queue>
#include <vector>
using namespace std;

//https://leetcode.com/problems/average-of-levels-in-binary-tree/
/*
 * 	This is a Tree problem, easily solved using level-order traversal.
 *
 * 	Using a queue, we can easily perform operations in level-wise order. Each iteration, the queue will contain
 * 	all elements in one level. Sum them up, average them, and add to results list
 *
 * 	------------------------------------------------------
 *
 * 	However, it is entirely possible using depth first search. In recursion (or Stack), we need to keep track of
 * 	what levels we are in, and sum them all into one result array as well as update the level element frequency.
 *  At the end of DFS, convert them into average, and return
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
	vector<double> averageOfLevels(TreeNode* root) {
		vector<double> res;
		if (!root) return res;
		queue<TreeNode*> queue;
		queue.push(root);

		while (!queue.empty()) {
			int size = queue.size();
			double avg = 0;
			for (int i = 0; i < size; ++i) {
				TreeNode* polled = queue.front(); queue.pop();
				avg += polled->val;

				if (polled->left) queue.push(polled->left);
				if (polled->right) queue.push(polled->right);
			}
			res.push_back(avg / size);
		}
		return res;
	}
};