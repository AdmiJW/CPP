#include <queue>
using namespace std;

//https://leetcode.com/problems/add-one-row-to-tree/
/*
 * 	This is a Tree DFS / BFS problem
 *
 * 	For BFS, we will use level order traversal using Queues. Traverse layer by layer, until we reached
 * 	at the layer d-1. This means we have all the nodes at layer d-1, and we are going to insert new nodes
 * 	at layer d, right below current layer of d-1.
 *
 * 	For each node at d-1, first keep reference to their childrens. Then, their left and right child will be
 * 	assigned a new node, then, connect the old childrens to the new childrens. That's it.
 *
 * 	---------------------------------------------------------------------
 *
 * 	For DFS, use counting down of layer. Once the depth had reached 1, we know that this node at this recursion
 * 	call is a node at d-1. So keep reference to the children, insert new node as direct children, connect the
 * 	old children to the new nodes.
 *
 * 	Note that special cases is when d=1, which the root of the tree has to be changed. Take care of the special
 * 	case separately.
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
	TreeNode* addOneRow(TreeNode* root, int v, int d) {
		if (d == 1) {
			TreeNode* newroot = new TreeNode(v);
			newroot->left = root;
			return newroot;
		}

		queue<TreeNode*> queue;
		queue.push(root);

		//	Treaverse layers to reach layer d-1
		for (int level = 1; level < d - 1; ++level) {
			for (int size = queue.size(); size > 0; --size) {
				TreeNode* poll = queue.front(); queue.pop();
				if (poll->left) queue.push(poll->left);
				if (poll->right) queue.push(poll->right);
			}
		}

		//	We have the nodes to d-1. For each node, insert new node, and connect descendants to the new node 
		while (!queue.empty()) {
			auto poll = queue.front(); queue.pop();
			auto oldleft = poll->left;
			auto oldright = poll->right;
			poll->left = new TreeNode(v);
			poll->right = new TreeNode(v);
			poll->left->left = oldleft;
			poll->right->right = oldright;
		}
		return root;
	}




	//	DFS recursion method, to countdown depth. If it is 1, create a new node
	TreeNode* addOneRow2(TreeNode* root, int v, int d) {
		if (d == 1) {
			TreeNode* newnode = new TreeNode(v);
			newnode->left = root;
			return newnode;
		}
		recurse(root, v, d - 1);
		return root;
	}
	void recurse(TreeNode* root, int v, int d) {
		if (!root) return;

		if (d == 1) {
			TreeNode* orileft = root->left;
			TreeNode* oriright = root->right;
			root->left = new TreeNode(v);
			root->right = new TreeNode(v);
			root->left->left = orileft;
			root->right->right = oriright;
		}
		else {
			recurse(root->left, v, d - 1);
			recurse(root->right, v, d - 1);
		}
	}
};