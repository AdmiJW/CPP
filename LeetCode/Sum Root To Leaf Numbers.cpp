#include <string>
using namespace std;


//https://leetcode.com/problems/sum-root-to-leaf-numbers/
/*
 * 	A BFS/DFS problem. Given every time i travel down one layer into the tree, then I would shift the value before one place to the left,
 * 	and then add the value of the current node into the value. This is done by simply multiply by 10 because
 * 		Eg: 53, if i want to append 1, then i multiply 10,
 * 			53 = 5(10) + 3, ---------> 53(10) = 5(10)(10) + 3(10) = 5(100) = 3(10) = 530
 * 			then i add 1 to become 531
 *
 * 	After that, check if the node is a leaf. If yes, then return value. Otherwise, continue the process into the search
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
	int sumNumbers(TreeNode* root) {
		return sumNumbers(root, 0);
	}


	int sumNumbers(TreeNode* node, int carry) {		
		if (!node) return 0;

		carry = carry * 10 + node->val;

		// Leaf node
		if (!node->left && !node->right) return carry;

		return sumNumbers(node->left, carry) + sumNumbers(node->right, carry);
	}
};