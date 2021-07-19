
struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

//https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-search-tree/
/*
 * 	This is a Binary Search Tree problem.
 *
 * 	Since the node p and q are guaranteed to be inside the BST, and recall that BST is sorted already,
 * 	we can find out the lowest common ancestor relatively easy.
 *
 * 	On a node, if we sense that the two searched nodes are in left and right subtree respectively, then
 * 	the current node must be the LCA already.
 *	Another case is when the node itself is one of searched node, then it is also LCA guaranteed.
 *
 *	Otherwise, both nodes must be in left subtree or right subtree together. We shall further our search
 *	in that direction.
 *
 *	Iterative approach is preferred. It runs in O(log N) time in balanced tree, otherwise O(N)
 */


class Solution {
public:
	TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
		int minVal = p->val < q->val ? p->val : q->val;
		int maxVal = p->val < q->val ? q->val : p->val;

		while (root) {
			// If node is one of searched, then another one must be descendant
			if (root == p || root == q) return root;

			int val = root->val;
			// p is left and q is in right. Then this must be Lowest Common Ancestor
			if (minVal < val && val < maxVal) return root;

			// Otherwise, it must be either in left subtree or right subtree
			if (val < minVal)
				root = root->right;
			else
				root = root->left;
		}
		return nullptr;
	}
};