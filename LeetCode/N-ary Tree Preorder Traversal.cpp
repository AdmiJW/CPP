#include <vector>
#include <stack>
using namespace std;

//https://leetcode.com/problems/n-ary-tree-preorder-traversal/
/*
 * This is simply a Tree traversal problem
 *
 * Instead of binary tree, now you faced with preorder traversal with
 * M-ary tree. However, the twist isn't big. Instead of checking left and
 * right, replce with a loop to check out the childrens
 *
 * Note in iterative method, you should push to the stack from right to left,
 * so the leftmost children will get popped first
 */

class Node {
public:
	int val;
	vector<Node*> children;

	Node() {}
	Node(int _val) : val(_val) {}
	Node(int _val, vector<Node*> _children) : val(_val), children(_children) {}
};


class Solution {
public:

	//	Recursive method
	vector<int> preorder(Node* root) {
		vector<int> res;
		recurse(root, res);
		return res;
	}
	void recurse(Node* root, vector<int>& res) {
		if (!root) return;
		res.push_back(root->val);

		for (Node* n : root->children)
			recurse(n, res);
	}


	//	Iterative method
	vector<int> preorder2(Node* root) {
		vector<int> res;
		if (!root) return res;
		stack<Node*> stk;
		stk.push(root);

		while (!stk.empty()) {
			Node* node = stk.top(); stk.pop();
			res.push_back(node->val);

			//	Right to Left!
			for (int i = node->children.size() - 1; i >= 0; --i) {
				Node* n = node->children[i];
				if (n) stk.push(n);
			}
		}
		return res;
	}
};