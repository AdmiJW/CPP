
struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode() : val(0), left(nullptr), right(nullptr) {}
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
	TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

//https://leetcode.com/problems/trim-a-binary-search-tree/
/*
 * 	This is a Binary Search Tree DFS recursion problem, although can be solved iteratively.
 *
 * 	To think recursively, we simply have to think of each node individually. What has to be done
 *  on each node?
 *  Base case is, if node is null, simply return null.
 *  Otherwise, we have to trim the tree's left and right subtree first. Assume that recursion will
 *  return the trimmed subtree's root, so we just connect them.
 *
 *  Let's think of possible cases:
 *
 *  	>	Node Fall in range - Then, the node must be included in final tree (Not trimmed). We just
 *  							 return the current node, which is connected to trimmed left and right
 *  							 subtree
 *  	>	Node smaller than low - Node trimmed. However the right subtree might fall in range. SO
 *  							    return trimmed right subtree
 *  	>	Node larger than high - Node trimmed. However the left subtree might fall in range. So
 *  								return the trimmed left subtree
 *
 *  --------------------------------------------------------------------------
 *
 *  To solve iteratively, the solution is harder to come up, but still very possible.
 *
 *  First, locate the new root of the tree, which is the first node that falls in range.
 *  If root is not in range, if it is higher, locate left, otherwise right.
 *
 *  Once new root is located, simply trim the left and right subtree, knowing the properties:
 *
 *  >	Left subtree value will never go higher than root, so no need check any right child. Just check
 *  	if value go too low, then replace the node where its left child is too low, to the left child's
 *  	right subtree.
 *  >	Right subtree value will never go lower than root, so no need check any left child. Just check
 *  	if value go too hgih, then replace the node where its right child is too high, to the right child's
 *  	left subtree.
 */


class Solution {
public:

	//	First solution using DFS
	TreeNode* trimBST(TreeNode* root, int low, int high) {
		if (!root) return nullptr;

		root->left = trimBST(root->left, low, high);
		root->right = trimBST(root->right, low, high);

		if (root->val >= low && root->val <= high) return root;
		return root->left ? root->left : root->right;
	}


	//	Slightly optimized to avoid redundant computation
	TreeNode* trimBST2(TreeNode* root, int low, int high) {
		if (!root) return nullptr;

		if (root->val < low) return trimBST2(root->right, low, high);
		if (root->val > high) return trimBST2(root->left, low, high);

		root->left = trimBST2(root->left, low, high);
		root->right = trimBST2(root->right, low, high);
		return root;
	}


	//	Iterative solution. Find root, trim left subtree, trim right subtree
	TreeNode* trimBST3(TreeNode* root, int low, int high) {

		//	Search for the new root which falls in valid range
		while (root) {
			if (root->val < low) root = root->right;
			else if (root->val > high) root = root->left;
			else break;
		}

		//	Trim the left subtree, which value always less than root
		TreeNode* dummy = root;
		while (dummy && dummy->left) {
			if (dummy->left->val < low)
				dummy->left = dummy->left->right;
			else dummy = dummy->left;
		}

		//	Trim the right subtree, which value always greater than root
		dummy = root;
		while (dummy && dummy->right) {
			if (dummy->right->val > high)
				dummy->right = dummy->right->left;
			else dummy = dummy->right;
		}

		return root;
	}
};