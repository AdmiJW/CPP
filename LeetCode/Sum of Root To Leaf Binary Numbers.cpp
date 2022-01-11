
using namespace std;


//https://leetcode.com/problems/sum-of-root-to-leaf-binary-numbers/
/*
 * 	This is a DFS problem of Binary Trees
 *
 * 	Remember, that given a tree, we could perform the following traversals:
 * 		>	Pre-order Traversal (root > left > right)
 * 		>	In-order Traversal	(left > root > right)
 * 		>	Post-order Traversal(left > right > root)
 *
 * 	And since a tree is essentially a type of graph, we can perform the following search algorithm:
 * 		>	Depth first search (DFS)
 * 		>	Breadth first search (BFS)
 *
 * 	Since the question requires us to form the numbers from the root to leaf, DFS is required as BFS can't let us directly know
 * 	what is the number extending from the root to leaf.
 *
 * 	Note that on every node, we are essentially shifting the number to left by 1 bit, then adding the node's value.
 * 		>	Either we perform << Left shift operation of 1 bit, then add the node.val
 * 		>	Or we just multiply the integer value by 2, then add the node.val
 *
 * 	The easiest way to implement is by using recursion DFS of pre-order traversal. On every node, perform left shifting, add node.val
 * 	and pass the value to child nodes. If it is a leaf node, directly return the value
 *
 * 	To implement iteratively, we have to mimic the recursive method: keeping the values associated with each node stored in the Stack
 * 	Note that Java recommends using the class ArrayDeque (of Interface Deque) for Stack and Queue operations instead of
 * 	Stack and LinkedList itself
 * 	Instead of using one stack for the TreeNode and one stack for the values, use the Java's convenient class Pair from javafx.
 * 	It allows us to store a pair of key value.
 *
 * 	=========================================================================================================
 *
 * 	The harder way to solve is to using Binary Tree Morris Traversal Algorithm. For every node encountered, we check to see if it
 * 	contains a left subtree. If it does, once we traverse into the left subtree, we need a way to travel back to the parent node
 * 	so that we could explore the right subtree.
 *
 * 	This is done by establishing a link between the parent node and the left subtree's rightmost node. Find the predecessor node
 * 	(Left subtree's rightmost node) and connect the predecessor node's right to the parent node. After the link is established,
 * 	safely explore the parent node's left subtree.
 *
 * 	Once we got back to the parent node, the same function is going to be called again. The function shall discover there is a cycle
 * 	in the left subtree that connects us back to the parent node. In that case, it knows that the left subtree had been explored.
 * 	Therefore, disconnect the link and go to the right subtree
 *
 * 	If there is no left subtree however, we shall go to right subtree directly, forgetting the parent node essentially.
 *
 * 	To make the function suit the problem, the function to find the predecessor shall return some information:
 * 		>	The depth of the subtree, for backtracking purposes
 * 		>	Is the predecessor a leaf node? To determine if the value so far shall be added to result
 *
 * 	Note that we have to use backtracking here. Once we traversed into the left subtree, when we go back to the parent node,
 * 	the value is already including the subtree binary bits. To backtrack, we need to perform right shift by the depth
 *
 * 	When we travel back to parent node, we may or may not be travelling back from a leaf node. A leaf node will have the property
 * 	of having no left subtree, and right subtree connects back to parent node (The morris temporary link).
 *
 * 	Lastly, when travelling to the right subtree, we need to check also if the right subtree is a leaf node. If yes, add value to
 * 	result
 *
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
public:
	int sumRootToLeaf(TreeNode* root, int val = 0) {
		if (root == nullptr) return 0;
		val = (val << 1) | root->val;
		if (!root->left && !root->right) return val;
		return sumRootToLeaf(root->left, val) + sumRootToLeaf(root->right, val);
	}

};