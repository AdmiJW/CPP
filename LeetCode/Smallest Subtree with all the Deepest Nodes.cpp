#include <queue>
#include <cmath>
using namespace std;

//https://leetcode.com/problems/smallest-subtree-with-all-the-deepest-nodes/

/*
 * 	This is a DFS Postorder Traversal / BFS + DCA (Deepest (or lowest) Common Ancestor) problem
 *
 * 	Firstly, observe the following:
 * 	For every node, it may contain the following cases:
 * 		>	It has the deepest node in left subtree ONLY
 * 		>	It has the deepest node in right subtree ONLY
 * 		>	It has the deepest node in both subtree
 * 		>	It has none subtree which has the deepest node
 *
 * 	If say that we know, on a node, the maximum depth of its left subtree and right subtree, what action can we do?
 *
 * 		>	If the left subtree and right subtree reports a depth which is equal to the maximum depth, that means
 * 			both the subtree contains the deepest node! Therefore we conclude that this node is the deepest common
 * 			ancestor. Record
 * 		>	If the left subtree only that reports a depth, surely that in the left subtree there are LOWER node
 * 			which is the deepest common ancestor. Do nothing. Similar case goes to right subtree.
 *
 * 	Therefore we can modify the normal depth searching algorithm. When it returns the depth of subtree from both
 * 	sides, we can check and determine the correct action. Except for this:
 *
 * 		>	If the left subtree or right subtree returned highest depth seen so far (Breaking the record), then
 * 			current node will be the DCA, and we have to update the maximum depth. This case particularly occurs
 * 			on leaf node.
 * 			When encountered a NULL node, we can just return the depth passed in as argument back.
 *
 * 	-----------------------------------------------------------------------------------------------
 *
 * 	The idea of the BFS + DSA solution is to
 * 		>	First locate the DEEPEST leftmost node and DEEPEST rightmost node using BFS. The first node and
 * 			last node in the queue of last level will be it.
 * 		>	Using this 2 informations, we can run a recursive function to find out the deepest common ancestor
 * 			of those 2 nodes:
 *
 * 				>	If node is null (Not found), or node is equal to deepest rightmost node or deepest leftmost
 * 					node, return node.
 * 				>	Otherwise recurse on left and right subtree. Obtain the return values
 * 				>	If left and right subtree both returns some value (Means the deepest nodes are found in both
 * 					sides), THIS NODE is the deepest common ancestor. Return current node.
 * 				>	If left subtree returns null, that means (probably) the deepest node is at the right subtree.
 * 				>	COnversely, return left subtree value if right subtree value is null.
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

	TreeNode* res = nullptr;
	int maxDepth = 0;

public:
	TreeNode* subtreeWithAllDeepest(TreeNode* root) {
		recurse(root, 1);
		return res;
	}
	int recurse(TreeNode* node, int depth) {
		if (!node) return depth;

		int left = recurse(node->left, depth + 1);		//Obtain max depth of left subtree
		int right = recurse(node->right, depth + 1);	//Obtain max depth of right subtree

		if (left == right && left == maxDepth) res = node;	//	Deepest node in both sides
		else if (fmax(left, right) > maxDepth) {			//	If new maximum is found. This is the max node
			maxDepth = fmax(left, right);
			res = node;
		}
		return fmax(left, right);
	}







	TreeNode* subtreeWithAllDeepest2(TreeNode* root) {
		if (!root) return root;

		queue<TreeNode*> queue;
		TreeNode* deepestLeft = nullptr;
		TreeNode* deepestRight = nullptr;	
		queue.push(root);

		//	Using BFS, obtain the deepest left most and rightmost node.
		while (!queue.empty()) {
			int sizeOfLvl = queue.size();
			for (int i = 0; i < sizeOfLvl; ++i) {
				TreeNode* polled = queue.front(); queue.pop();
				if (!i) deepestLeft = polled;
				if (i == sizeOfLvl - 1) deepestRight = polled;

				if (polled->left) queue.push(polled->left);
				if (polled->right) queue.push(polled->right);
			}
		}
		//With the deepest left and right nodes, find their deepest common ancestor
		return findDCA(root, deepestLeft, deepestRight);
	}
	//	Recurse method to find Deepest Common Ancestor, provided the two nodes to search for
	TreeNode* findDCA(TreeNode* node, TreeNode* deepestLeft, TreeNode* deepestRight) {
		if (!node || node == deepestLeft || node == deepestRight) return node;

		TreeNode* left = findDCA(node->left, deepestLeft, deepestRight);
		TreeNode* right = findDCA(node->right, deepestLeft, deepestRight);

		if (left && right) return node;	//Both left and right contains the deepest Nodes! The node
										//currently is deepest common ancestor!
		else if (!left) return right;	//Left side returns no result of deepest nodes. Return right
		return left;					//Right side returns no result of deepest nodes. Return left
	}
};