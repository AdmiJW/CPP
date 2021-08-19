#include <vector>
using namespace std;

//https://leetcode.com/problems/maximum-product-of-splitted-binary-tree/
/*
 * 	This is a binary tree, DFS (Postorder traversal) problem
 *
 *  Whenever we remove one edge, two subtrees are formed. From the edge that we removed, the node connected
 *  below the removed edge will become the root of the subtree.
 *
 *  Therefore, for all nodes, we can consider what will happen it that node became the root of one of the
 *  subtrees, by removing the edge above it. However, how do we know what is the sum of the second subtree?
 *
 *  Turns out, if we know the sum of the entire tree beforehand, the sum of second subtree is no other than
 *
 *  	(wholeTreeSum - subtreeSum) = otherSubtreeSum
 *
 *  the sum of a subtree is easily obtainable by postorder traversal.
 */

struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode() : val(0), left(nullptr), right(nullptr) {}
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
	TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};


typedef long long int LONG;


class Solution {
	LONG res = 0;
	LONG wholeSum = 0;

public:
	// Find sum first, then find max product solution
	int maxProduct(TreeNode* root) {
		// Find sum of whole tree
		wholeSum = findProduct(root);
		// Find maximum product
		findProduct(root);
		return (int)(res % 1000000007);
	}

	// This function does two things:
	// > Returns the sum of subtree (First pass)
	// > Updates the res for product of two splitted binary tree based on wholeSum (Second pass)
	int findProduct(TreeNode* root) {
		if (!root) return 0;
		int subtreeSum = findProduct(root->left) + findProduct(root->right) + root->val;

		res = max(subtreeSum * (wholeSum - subtreeSum), res);
		return subtreeSum;
	}
};