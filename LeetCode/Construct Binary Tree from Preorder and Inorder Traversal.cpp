#include <unordered_map>
#include <vector>
using namespace std;

//https://leetcode.com/problems/construct-binary-tree-from-preorder-and-inorder-traversal/
/*
 * 	This is a Tree, DFS problem.
 *
 * 	Problems that goes with tree, are often better solved with recursion. Similar case applies here.
 * 	First, remind that
 * 		>	Preorder: Root > Left > Right
 * 		>	Inorder: Left > Root > Right
 *
 * 	When we first receive both arrays, we must realize the fact that:
 * 		>	In preorder, first element must be the root of whatever tree we are building.
 * 		>	Then, knowing the root node, we can check where the current root node is located in the
 * 			inorder traversal.
 *
 * 			Once located, new information will be exposed to us by looking in Inorder traversal:
 *
 * 					Left subtree nodes			 Right subtree nodes
 * 					<------------------- ( ROOT ) -------------------->
 *
 * 	Therefore, we have successfully divided the problem into smaller subproblems to be solved by our
 * 	imiginary recursion function!
 *
 * 	In my solution, I pass the left and right limit of both inorder and preorder traversal arrays to
 * 	indicate the range of nodes that are included in the subtree.
 *
 * 	However, turns out we actually don't need to impose the right limit on preorder array, due to
 * 	the recursive function only checks for the first element and nothing else. Also we can simply
 * 	check whether it is invalid left and right limit for inorder traversal to determine base case.
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
	TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
		const int len = preorder.size();
		//	Construct mapper for nodeVal -> inorder index
		unordered_map<int, int> lookup;
		for (int i = 0; i < len; ++i)
			lookup[inorder[i]] = i;

		return buildTreeNode(preorder, inorder, 0, len - 1, 0, len - 1, lookup);
	}

	
	//	Recursive function to build a TreeNode
	TreeNode* buildTreeNode(vector<int>& preorder, vector<int>& inorder, int preLeft, int preRight, int inLeft, int inRight, unordered_map<int, int>& lookup) {
		//	Base case
		if (inLeft > inRight) return nullptr;

		//	We know that the first element to the preLeft in inorder[] is the root
		TreeNode* root = new TreeNode(preorder[preLeft]);
		int rootIdxInInorder = lookup[preorder[preLeft]];
		int leftSubtreeSize = rootIdxInInorder - inLeft;

		//	Left subtree. Preorder spans from current idx +1, until the end of left subtree size.
		//	Inorder spans from left limit until the index of current node in inorder traversal, minus 1
		root->left = buildTreeNode(preorder, inorder, preLeft + 1, preLeft + leftSubtreeSize, inLeft, rootIdxInInorder - 1, lookup);
		//	Right subtree. Preorder spans from the end of left subtree size, until right limit
		//	Inorder spans from index of current node in inorder traversal +1, until right limit
		root->right = buildTreeNode(preorder, inorder, preLeft + leftSubtreeSize + 1, preRight, rootIdxInInorder + 1, inRight, lookup);

		return root;
	}
};