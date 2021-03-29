#include <vector>
using namespace std;

//	https://leetcode.com/problems/flip-binary-tree-to-match-preorder-traversal/
/*
 * 	This is a DFS problem, checking each node in Preorder traversal order
 *
 * 	First and foremost, notice that each node is assigned UNIQUE value. This means a lot:
 * 	>	If left subtree mismatch, flip it. If mismatch again, it means impossible to match the voyage already
 * 		due to unique values.
 * 		If the values are not unique, there may be cases where for example, left and right subtree are same value.
 * 		This will further extend the time complexity.
 *
 *
 * 	We have a recursive function, taking in crucial information:
 * 	>	node
 * 	>	index of voyage. It indicates the current node supposed to be value
 *
 *	The function returns a index value. Index value indicates the next index in voyage array that is supposed to come next
 *	in DFS. Return -1 to indicate failure.
 *
 *	If node is null, return index as it is without modifying. If node value mismatch, return -1.
 *	Otherwise, node match. Check subtree. Recurse left subtree. If left subtree mismatched (return -1), try flipping and attempt
 *	again. If fail, return -1 to upper level. Otherwise finally use that returned index to recurse on right subtree, and return
 *	the value.
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
	vector<int> flipMatchVoyage(TreeNode* root, vector<int>& voyage) {
		vector<int> res;

		if (recurse(root, voyage, 0, res) == -1) {
			res.clear();
			res.push_back(-1);
		}
		return res;
	}

	int recurse(TreeNode* node, vector<int>& voyage, int idx, vector<int>& res) {
		if (!node) return idx;
		if (node->val != voyage[idx]) return -1;

		//	Try going left
		int next = recurse(node->left, voyage, idx + 1, res);

		//	Left child mismatched (Eliminate the possibility that left n right child are same, because node val are unique).
		//	Therefore try flipping and attempt again. 
		if (next == -1) {
			TreeNode* temp = node->left;
			node->left = node->right;
			node->right = temp;

			next = recurse(node->left, voyage, idx + 1, res);
			if (next == -1) return -1;

			res.push_back(node->val);		//	Successful flip need to be recorded
		}

		next = recurse(node->right, voyage, next, res);
		return next;
	}
};