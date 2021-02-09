#include <stack>
using namespace std;

/*
 * 	This is a Binary Tree, Depth First Search, Recursion problem.
 *
 * 	Let's revise some key concepts:
 * 	>	In a BST, right subtree's every nodes are greater than parent.
 * 	>	Left subtree are, however, less than parent.
 *
 *	Therefore think, what value shall one node be incremented with? The answer is the right subtree's sum.
 *	We will call recurse on right subtree, obtain its subtree sum, update the node.val, and pass right subtree
 *	sum + node.val (before modified) into left subtree. This is In order traversal
 *
 *	Every recursion call will assiciate with a parameter sum, which represents the sum value derived from parent and
 *	its right subtree. Recurse right to obtain the sum, update node.val, then return the sum after recurse into left
 *	subtree.
 *
 *	Turns out, instead of returning the sum, we can just return the TreeNode, since the TreeNode does have the value needed
 *	to update the parent node
 *
 *	-----------------------------------------------------------------
 *
 *	Iterative solution is workable especially with Stack. This way just keep a variable sum that keeps adding, and we
 *	use in order traversal to update the nodes.
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
	//	Recursive solution - Post order traversal
	//	This initial solution was based on recursion function that returns sum of subtree without modification
	//	but the function itself DO modify the node values
	TreeNode* convertBST(TreeNode* root) {
		recurse(root, 0);
		return root;
	}
	int recurse(TreeNode* node, int sum) {
		if (!node) return 0;

		int rightSum = recurse(node->right, sum);
		int leftSum = recurse(node->left, rightSum + node->val + sum);

		node->val += rightSum + sum;
		return node->val + leftSum - sum;
	}


	//	In order traversal, shorter, concise
	int recurse2(TreeNode* node, int sum) {
		if (!node) return sum;
		node->val += recurse2(node->right, sum);
		return recurse2(node->left, node->val);
	}



	TreeNode* convertBST2(TreeNode* root) {
		if (!root) return nullptr;

		stack<TreeNode*> stack;
		int sum = 0;
		TreeNode* pt = root;

		while (pt || !stack.empty()) {
			if (pt) {
				stack.push(pt);
				pt = pt->right;
			}
			else {
				TreeNode* pop = stack.top(); stack.pop();
				pop->val += sum;
				sum += (pop->val - sum);

				pt = pop->left;
			}
		}
		return root;
	}
};