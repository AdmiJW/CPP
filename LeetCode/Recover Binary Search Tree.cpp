#include <vector>
using namespace std;

//https://leetcode.com/problems/recover-binary-search-tree/

/*
 * 	This is a Tree DFS, In order traversal problem.
 *
 * 	Given the BST have 2 of their nodes swapped, that means that still, the BST is valid except for 2 of their nodes.
 * 	Here, we have to utilize the property of BST that the inorder traversal of the nodes will result in a sorted
 * 	array.
 *
 * 	Now, since 2 of the nodes are swapped, it is like swapping 2 of the elements in a sorted array. Let's see how it
 * 	shall looks like:
 *
 * 		Sorted: 1,2,3,4,5,6,7,8,9
 * 		Swapped: 1,2,8,4,5,6,7,3,9
 *
 * 	As we can see, the 8 and 3 are swapped. When traversing through the array, we can easily detect the swapped elements
 * 	by look at:
 * 		>	(8) is one of swapped elements, because the very next element is lower than 8 itself, which disrupts the flow
 * 			of the sorted array
 * 		>	(3) is one of swapped elements, because the element (3) is actually less than the previous element, which
 * 			disrupts the flow of sorted array as well
 *
 * 	Therefore, when doing in order traversal, we can actually use recursive method to solve, while passing the mutable
 *	array around so we can easily store information at any of the calls
 *
 *	At every call, we basically have to provide several informations:
 *		>	The pointer to the previous node
 *		>	The pointer to the first swapped element
 *		>	The pointer to the second swapped element
 *
 *	If at one of the calls, we detect the previous element value is greater than the current node's value, then we know:
 *		>	If the pointer to swapped element is null, we know that the previous element is the swapped node. Simply
 *			assign previous node to the first swapped element
 *		>	If the pointer to the swapped element is not null, we know that the current element is the swapped node.
 *
 *	One particular case though: If the swapped elements are next to each other
 *		Swapped: 1,2,4,3,5,6,7,8,9
 *
 *		>	In this case, the first swapped element will only be detected when we are on element (3). Only on element (3)
 *			we get to know that (4) is one of swapped element.
 *			To solve this, whenever we detected the first element, we also assign the current node as second element.
 *			Only when the second element is detected again, we overwrite it.
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
	void recoverTree(TreeNode* root) {
		TreeNode* arr[3] = {};
		recurse(root, arr);

		int temp = arr[1]->val;
		arr[1]->val = arr[2]->val;
		arr[2]->val = temp;
	}


	void recurse(TreeNode* node, TreeNode* nodes[]) {
		if (node == nullptr) return;

		recurse(node->left, nodes);

		if (nodes[0] != nullptr && nodes[0]->val > node->val) {
			if (nodes[1] == nullptr) {
				nodes[1] = nodes[0];
				nodes[2] = node;
			}
			else {
				nodes[2] = node;
			}
		}

		nodes[0] = node;
		recurse(node->right, nodes);
	}

};