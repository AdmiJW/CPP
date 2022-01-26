#include <vector>
#include <stack>
using namespace std;


//https://leetcode.com/problems/all-elements-in-two-binary-search-trees/
/*
 * 	This is a traversal + sort problem
 *
 * 	First of all, we know that the inorder traversal (Left -> Root -> Right) of an binary search tree is always in ascending order
 * 	(Sorted)
 *
 * 	Knowing this property, if we perform an inorder traversal on each individual tree, we would get 2 sorted lists containing
 * 	all the elements in sorted order.
 * 	Now, we shall perform MERGE function to merge those 2 sorted arrays into one single sorted array.
 * 	Keep 2 pointers. Whoever value is smaller, gets added to the result array, and have its pointer move forward.
 * 	Note if one pointer reached the end, just add the remaining elements of another one
 *
 * 	Time complexity is overall O(N + M), since we are traversing each element fixed number of times.
 * 	However, space complexity is O(N + M), since we will first obtain the inorder traversal result of both BST, which contains
 * 	all the elements in both BST.
 *
 * 	---------------------------------------------------------------------------------------------------
 *
 * 	Can we optimize the space?
 *
 * 	The core idea to space optimization is that we should find a way to keep only the minimum element of both BST. Only when one
 * 	of the minimum element is appended into result array, we update it with the next minimum element. How? Using the
 * 	iterative method for inorder traversal.
 *
 * 	Remember in a BST, the leftmost element is always the minimum one, then the parent node.
 * 	Therefore we could use a STACK to store the nodes of the left part of the tree (Meaning to ignore all the right subtrees)
 *
 * 	We would use a function which when passed in a node, will store the LEFT traversal of the tree starting from that node
 * 	into the stack.
 *
 * 	Say we have tree 				(5)
 * 								(1)		(7)
 * 							(0)	  (2)
 *
 * 	Then we will push (5), go left, push (1), and go left, push (8). THat's it!
 *
 * 	If we do this to both BST, we would have 2 Stacks, each having the LEFT traversal. Now, the top of stack contains the
 * 	minimum element of both the BST. Compare them, find the minimum one, and add it to the result.
 *
 * 	Now, we have to update that one stack that gets popped, to have second minimum element at the top of stack.
 * 	This is done by calling the function of LEFT traversal once again, but pass the popped node's right child as the argument.
 * 	This shall update the whole stack to contain the second smallest node. (If exists).
 *
 * 	This step needs to be done because the node's right contains nodes that are greater than the popped node, but SMALLER than
 * 	the PARENT node
 *
 * 	With this, the space complexity shall be reduced down to O(log N + log M), whoever tree has the greatest height
 * 	(If we don't consider the result array into the space complexity)
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
	vector<int> getAllElements(TreeNode* root1, TreeNode* root2) {
		vector<int> root1InOrder, root2InOrder;
		inOrderTraversal(root1, root1InOrder);
		inOrderTraversal(root2, root2InOrder);

		vector<int> res(root1InOrder.size() + root2InOrder.size());
		int pt1 = 0, pt2 = 0;

		while (pt1 < root1InOrder.size() && pt2 < root2InOrder.size()) {
			if (root1InOrder[pt1] < root2InOrder[pt2]) {
				res[pt1 + pt2] = root1InOrder[pt1];
				++pt1;
			}
			else {
				res[pt1 + pt2] = root2InOrder[pt2];
				++pt2;
			}
		}

		while (pt1 < root1InOrder.size()) {
			res[pt1 + pt2] = root1InOrder[pt1];
			++pt1;
		}

		while (pt2 < root2InOrder.size()) {
			res[pt1 + pt2] = root2InOrder[pt2];
			++pt2;
		}
		
		return res;
	}




	vector<int> getAllElements2(TreeNode* root1, TreeNode* root2) {
		stack<TreeNode*> stk1, stk2;
		vector<int> res;

		fillStackLeft(root1, stk1);
		fillStackLeft(root2, stk2);

		while (!stk1.empty() && !stk2.empty()) {
			if (stk1.top()->val > stk2.top()->val) {
				TreeNode* pop = stk2.top();
				stk2.pop();
				res.push_back(pop->val);
				fillStackLeft(pop->right, stk2);
			}
			else {
				TreeNode* pop = stk1.top();
				stk1.pop();
				res.push_back(pop->val);
				fillStackLeft(pop->right, stk1);
			}
		}

		while (!stk1.empty()) {
			TreeNode* pop = stk1.top();
			stk1.pop();
			res.push_back(pop->val);
			fillStackLeft(pop->right, stk1);
		}

		while (!stk2.empty()) {
			TreeNode* pop = stk2.top();
			stk2.pop();
			res.push_back(pop->val);
			fillStackLeft(pop->right, stk2);
		}

		return res;
	}


	// Populates the stack with STRICTLY left nodes in the tree
	void fillStackLeft(TreeNode* node, stack<TreeNode*>& stk) {
		while (node) {
			stk.push(node);
			node = node->left;
		}
	}


	// Simply fills the res with the inorder traversal of the root node.
	void inOrderTraversal(TreeNode* root, vector<int>& res) {
		if (!root) return;
		inOrderTraversal(root->left, res);
		res.push_back(root->val);
		inOrderTraversal(root->right, res);
	}
};