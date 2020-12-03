#include <stack>

//https://leetcode.com/problems/increasing-order-search-tree/

/*
 * 	This is a Binary Search Tree DFS (Inorder traversal) Problem. Surprisingly, it seems to be easier implemented
 * 	iterative than recursively, using Stack.
 *
 * 	Given Binary Search Tree, we want to reorder them so that root node is minimum node and the right node points to
 * 	next minimum larger node. Remember this is like finding sorted list in BST, thus inorder traversal algorithm comes
 * 	into mind.
 *
 * 	Using Stack, we would place the nodes to be explored later. Why we would want to explore a node later? because there
 * 	is a smaller node at left subtree.
 * 	Therefore, when facing a node:
 *
 * 		If the node has left subtree:
 * 			Push current node into Stack
 * 			Push left node into Stack so it is explored first before current node
 * 			Remove current node's left pointer so it no longer points to left subtree to prevent revisiting
 *
 * 		Now, otherwise the node has no left subtree:
 * 			Append current node to the tail of resulting 'list'
 * 			If the node has a right subtree, push right node into Stack
 *
 * 	And that's it!
 *
 * 	==============================================================================================
 *
 * 	THe recursion algorithm is just like Stack implementation above. Each recursion call we pass in the tail node so the node
 * 	can be easily append to it.
 *
 * 	Each recursion call should return the updated pointer so it can be easily updated in the parent call.
 *
 * 	Therefore, in each recursion call,
 * 			If the node passed is null, return the tail pointer untouched
 * 			Otherwise, first recurse on the left subtree. Once returned the updated pointer, set the current call's
 * 			tail pointer to the updated one
 * 			Then, append the current node to the tail's right. Move the tail to point to current node.
 * 			Then, recurse on right subtree. Since it returns the updated pointer, return the recursion return value.
 */

struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode() : val(0), left(nullptr), right(nullptr) {}
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
	TreeNode(int x, TreeNode* left, TreeNode* right) :
		val(x), left(left), right(right) {}
};


class Solution {
public:

	//	Iterative Stack Solution
	TreeNode* increasingBST(TreeNode* root) {
		TreeNode head;
		TreeNode* headptr = &head;
		TreeNode* tail = headptr;

		std::stack<TreeNode*> stack;
		stack.push(root);

		while (!stack.empty()) {
			TreeNode* pop = stack.top();
			stack.pop();

			if (pop->left) {
				stack.push(pop);
				stack.push(pop->left);
				pop->left = nullptr;
			}
			else {
				tail->right = pop;
				tail = pop;

				if (pop->right)
					stack.push(pop->right);
			}
		}
		TreeNode* ans = headptr->right;
		return ans;
	}


	//	Recursive Solution, passing tail reference all around
	TreeNode* increasingBST2(TreeNode* root) {
		TreeNode head;
		recurse(&head, root);
		return head.right;
	}
	TreeNode* recurse(TreeNode* tail, TreeNode* node) {
		if (!node) return tail;

		tail = recurse(tail, node->left);
		node->left = nullptr;

		tail->right = node;
		tail = tail->right;

		TreeNode* right = node->right;
		node->right = nullptr;
		return recurse(tail, right);
	}
};