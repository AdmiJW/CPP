#include <queue>
using namespace std;


//https://leetcode.com/problems/cousins-in-binary-tree/
/*
*	This is a Binary Tree problem.
* 
*	Since this problem involves depth, we can use BFS to allow for early termination.
*	The idea is:
*		Iterate layer by layer. Once one of x or y is found, we have no reason to go deeper into the layers. This is early termination and is better
*		as binary tree usually grow exponentially by depth.
* 
*	Keep a boolean flag to indicate whether one of x or y is found in the layer. Also keep int variable to reference the parent. Then, For each
*	node in current layer, check left and right (So we know who is the parent).
*	
*	At the end of layer, if only one node is located, then terminate early by returning false, since we know they are already not on the same level.
*/


struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode() : val(0), left(nullptr), right(nullptr) {}
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
	TreeNode(int x, TreeNode* left, TreeNode* right) :val(x), left(left), right(right) {}
};


class Solution {
public:

	bool isCousins(TreeNode* root, int x, int y) {
		if (!root || root->val == x || root->val == y) return false;
		queue<TreeNode*> bfs;
		bfs.push(root);

		bool isLocated = false;
		int parent = -1;

		// Note that we don't check root node. This can be checked early if you want.
		while (!bfs.empty()) {
			for (int size = bfs.size(); size; --size) {
				TreeNode* node = bfs.front(); 
				bfs.pop();

				// Left subtree
				if (node->left) {
					if (node->left->val == x || node->left->val == y) {
						if (isLocated) return true;
						isLocated = true;
						parent = node->val;
					}
					bfs.push(node->left);
				}
				// Right subtree
				if (node->right) {
					if (node->right->val == x || node->right->val == y) {
						// Same parent.
						if (parent == node->val) return false;
						if (isLocated) return true;
						isLocated = true;
						parent = node->val;
					}
					bfs.push(node->right);
				}
				
			}
			// Located 1 node on this level only, means different depth
			if (isLocated) return false;
		}
		// Iterated whole tree already.
		return false;
	}
};