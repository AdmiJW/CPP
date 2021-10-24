
struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode() : val(0), left(nullptr), right(nullptr) {}
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
	TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

///https://leetcode.com/problems/count-complete-tree-nodes/

/*
 * 	This can be done very naively with a basic BFS or DFS, but we could do it in O( log n * log n) time complexity.
 *
 * 	The key here is that given the tree is a complete binary tree where nodes must be in the left at the last layer. We can find out the
 * 	maximum height of the tree by iterating through the left node every time.
 * 	Now we know the max height of the tree, we shall check if we go along the right node of the tree, is the height also same as the maximum height?
 *
 * 	If the maximum height is equal to the height if I went right node first then left node all the way, that means the very last node of the tree
 * 	shall be in the right subtree. We know that the left subtree part is complete of max height.
 * 	If the height of the tree if I went right node first then left node all the way is not equal, in fact, one less than the maximum height, that
 * 	means the very last node of the tree shall be in the left subtree. Now we know that the right subtree part is complete of the maximum height - 1
 *
 * 	How do we went ahead and find out the number of nodes in the left part or right part? It so happens that the count is 2^(Height - 1).
 * 	Therefore we could use bit manipulation to perform this power of 2, through shifting of bits.
 */

class Solution {
public:

	int nodes;

	// Get Height -> Iterate rightmost solution
	int countNodes(TreeNode* root) {
		if (!root) return 0;

		TreeNode* curr = root;
		int height = 0;
		while (curr) {
			curr = curr->left;
			++height;
		}
		nodes = (1 << height) - 1;
		locateMissingNode(root, height - 1);
		return nodes;
	}

	bool locateMissingNode(TreeNode* node, int height) {
		if (!height) {
			if (node) return true;

			--nodes;
			return false;
		}

		return (locateMissingNode(node->right, height - 1) ||
			locateMissingNode(node->left, height - 1));
	}
};