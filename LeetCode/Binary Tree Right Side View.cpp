
#include <vector>
#include <queue>
using namespace std;


//https://leetcode.com/problems/binary-tree-right-side-view/
/*
 * 	This is a recursion - DFS/ BFS Level order traversal problem.
 *
 * 	First let's talk about recursion. How can we solve in recursion?
 * 	In normal preorder traversal, the ordering is always root -> left -> right. Therefore the leftmost
 * 	node is always explored first.
 * 	If we do the reverse, then the rightmost node will always be explored first before its left part!
 *
 * 	However, consider this case:
 *
 * 			( )
 * 			/ \
 * 		  ( )  ( )
 * 		  /
 * 		( )
 *
 * 	How do we add the last node at level 2? (Root is lvl 0).
 * 	In the recursion, we are passing around the result list. Also, the recursion has a property: if the node
 * 	explored is the very first node to be seen in the current level, then it must be the rightmost one!
 * 	Therefore, check the list's size. It is equivalent to the node levels added. If current level haven't been occupied
 * 	yet, do add it!
 *
 * 	----------------------------------------------------------------------------------------------
 *
 * 	We could also perform a level order traversal (BFS). However, do it reversely so the rightmost node is always
 * 	at the front of the queue in each level.
 *
 */

struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode() : val(0), left(nullptr), right(NULL) {}
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
	TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

class Solution {
public:
	vector<int> rightSideView(TreeNode* root) {
		vector<int> res;
		recurse(root, 0, res);
		return res;
	}
	void recurse(TreeNode* node, int level, vector<int>& res) {
		if (!node) return;

		if (level == res.size())
			res.push_back(node->val);

		recurse(node->right, level + 1, res);
		recurse(node->left, level + 1, res);
	}




	vector<int> rightSideView2(TreeNode* root) {
		vector<int> res;
		queue<TreeNode*> level;
		if (root) level.push(root);

		while (!level.empty()) {
			int size = level.size();
			res.push_back(level.front()->val);

			while (size-- > 0) {
				TreeNode* node = level.front(); level.pop();
				if (node->right) level.push(node->right);
				if (node->left) level.push(node->left);
			}
		}
		return res;
	}

};