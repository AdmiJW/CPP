
#include <stack>
#include <queue>
using namespace std;

//https://leetcode.com/problems/find-a-corresponding-node-of-a-binary-tree-in-a-clone-of-that-tree/
/*
 * This is a Tree, DFS or BFS problem.
 *
 * Since values are unique, we can just perform regular search in the cloned tree, returning ASAP when found the
 * cloned node value is equal to target node's value.
 *
 * --------------------------------------------------
 *
 * If the values can be repeated, now the node value is meaningless. We have to compare using memory references, whether
 * the original node explored points to same memory location with target node or not. If yes, then only return the
 * corresponding cloned node.
 *
 *
 * With this idea, we have to traverse 2 trees in parallel to each other.
 *
 * O(1) space is possible with Morris Traversal Algorithm, but it is harder to implement, and modifies the tree structure.
 */

struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};


class Solution {
public:

	//	Hacky solution. Since values is unique, directly searching in cloned node works
	TreeNode* getTargetCopy(TreeNode* original, TreeNode* cloned, TreeNode* target) {
		if (!cloned) return nullptr;
		if (cloned->val == target->val) return cloned;

		TreeNode* left = getTargetCopy(nullptr, cloned->left, target);
		return left ? left : getTargetCopy(nullptr, cloned->right, target);
	}

	//	Real solution - Iterate in corresponding pairs DFS recursion
	TreeNode* getTargetCopy2(TreeNode* original, TreeNode* cloned, TreeNode* target) {
		if (!original) return nullptr;
		if (original == target) return cloned;

		TreeNode* left = getTargetCopy2(original->left, cloned->left, target);
		return left ? left : getTargetCopy(original->right, cloned->right, target);
	}


	//	Real solution - Iterative BFS using Queue
	TreeNode* getTargetCopy3(TreeNode* original, TreeNode* cloned, TreeNode* target) {
		queue<TreeNode*> ori;
		queue<TreeNode*> clones;
		ori.push(original);
		clones.push(cloned);

		while (!ori.empty()) {
			TreeNode* o = ori.front(); ori.pop();
			TreeNode* c = clones.front(); clones.pop();

			if (o == target) return c;

			if (o->left) {
				ori.push(o->left);
				clones.push(c->left);
			}
			if (o->right) {
				ori.push(o->right);
				clones.push(c->right);
			}
		}
		return nullptr;
	}
};