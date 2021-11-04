using namespace std;


struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode() : val(0), left(nullptr), right(nullptr) {}
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
	TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

//https://leetcode.com/problems/sum-of-left-leaves/

/*
 * 		This is a tree DFS problem.
 *
 * 		A leaf is a node which doesn't have any more child nodes. We have to find the sum of all left leaves
 *
 * 		At every node that we meet, we check if the left node of it is the leaf node
 * 			>	Check if current node has left node
 * 			>	Check if left node has left child. If yes it is not a leaf node
 * 			>	Check if left node has right child. If yes it is not a leaf node
 *
 * 		The problem can be solved iteratively or recursively.
 * 		Iterative method also uses DFS, with Stack data structure to aid us
 */

class Solution {
public:
	int sumOfLeftLeaves(TreeNode* root) {
		if (!root) return 0;
		
		// Left node is a left leaf.
		if (root->left && !root->left->left && !root->left->right)
			return root->left->val + sumOfLeftLeaves(root->right);

		return sumOfLeftLeaves(root->left) + sumOfLeftLeaves(root->right);
	}
};