#include <vector>
#include <unordered_map>
using namespace std;

//https://leetcode.com/problems/construct-binary-tree-from-inorder-and-postorder-traversal/

/*
 * 	This is a array, tree and DFS question.
 * 	Given Post order and In order traversal of the binary tree, we have to recreate the binary tree itself.
 *
 * 	We can take advantage of a property when we reverse the post order: Post order: ( Left > Right > Root )
 * 																		Post Reverse: ( Root > Right > Left )
 *
 * 	Therefore, we can always assume that in Post order reversed, the first element is always going to be the Node to be created in the recursion call
 * 	We call the node to be created 'root'
 *
 * 	Now, knowing the node to be created, we need to determine which other elements go into left subtree and which goes into right subtree
 * 	Using the In order traversal, this can be determined if we can determine the position of the root (Preferably using HashMap position querying?)
 *
 *	In order traversal: ( Left > Root > Right)
 *	Therefore:
 *						left subtree		right subtree
 *						<------------       ----------->
 *						[ e, e, e, e, ROOT, e, e, e, e ]
 *
 *
 *
 *	Therefore, the basic algorithm for each recursion call is basically:
 *
 *	buildTree(int inorderLeft, int inorderRight) {
 *		- Create new node based on current postorder ROOT pointer
 *		- Decrement postorder ROOT pointer
 *		- Obtain the index of currently created ROOT from inorder array
 *		- Further split the current inorder array range into left and right subtree range.
 *
 *		- Recurse to build right subtree
 *		- Recurse to build left subtree
 *
 *		- Return ROOT.
 *	}
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
	vector<int> inorder;
	vector<int> postorder;
	unordered_map<int, int> inorderIndex;
	int postorderIndex;


	TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
		this->inorder = inorder;
		this->postorder = postorder;

		postorderIndex = postorder.size() - 1;

		for (int i = 0; i < inorder.size(); ++i)
			inorderIndex[inorder[i]] = i;

		return buildTree(0, inorder.size() - 1);
	}

	TreeNode* buildTree(int inorderLeft, int inorderRight) {
		if (inorderLeft > inorderRight) return nullptr;

		// Create a new node based on current position in postorder array
		TreeNode* node = new TreeNode(postorder[postorderIndex]);

		// Get position of the current element in the inorder array
		int split = inorderIndex[postorder[postorderIndex]];

		// Since we used this element already, decrement position
		--postorderIndex;
	
		// Build right subtree
		node->right = buildTree(split+1, inorderRight);
		// Build left subtree
		node->left = buildTree(inorderLeft ,split- 1);

		return node;
	}

};