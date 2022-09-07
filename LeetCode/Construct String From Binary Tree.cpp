#include <string>
using namespace std;



//https://leetcode.com/problems/construct-string-from-binary-tree/
/*
 * 	This is a DFS problem - Preorder traversal best solved using recursion
 *
 * 	The idea is that given a node, we represent in string with parenthesis like so:
 * 		root(left subtree)(right subtree)
 * 	Where left subtree and right subtree itself is also a parenthesis expression just like the one above.
 *
 *
 * 	Therefore we create a recursive function. It shall append the root value first, then check:
 *
 * 	>	If the node is leaf node, we are done and shall not add any unnecessary parenthesis.
 * 	>	Otherwise, we MUST put a parenthesis for left subtree. If we omit it, right subtree would be viewed as left subtree.
 * 	>	Check if right subtree is null. If true, omit the parenthesis altogether.
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
	string tree2str(TreeNode* root) {
		string res = "";
		recurse(root, res);
		return res;
	}

	void recurse(TreeNode* root, string& str) {
		str += to_string(root->val);

		if (!(root->left) && !(root->right)) return;

		str += '(';
		if (root->left) recurse(root->left, str);
		str += ')';

		if (root->right) {
			str += '(';
			recurse(root->right, str);
			str += ')';
		}
	}
};