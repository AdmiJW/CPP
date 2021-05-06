#include <vector>
using namespace std;

//https://leetcode.com/problems/convert-sorted-list-to-binary-search-tree/
/*
 * 	This is a recursion, breadth first search, tree problem
 *
 * 	Given a sorted list, you know that the list is N length, and the best candidate to pick as root for
 * 	balanced tree is, the middle element, since every node to the left is in left subtree, and every node
 * 	at the right is in right subtree, picking the middle element ensures the left and right are balanced.
 *
 * 	The problem comes when you don't know the lenght of list. Here propose 2 kind of solutions:
 *
 * 	>	Solution 1: Convert linked list into array, using O(N) extra space.
 * 		Once converted list into array, middle element is easy to get. Therefore algorithm:
 * 		-	FInd middle element via calculation of middle index given start index and end index
 * 		-	Create root node on middle element
 * 		-	Assign root left child to be recursion of left subarray, up until current middle node
 * 		-	Assign root right child to be recursion of right subarray, from current middle node
 *
 * 	>	Solution 2: At each recursion call, iterate thru the list to find middle element.
 * 		Since each recursion layer divides the linked list into 2, at most there will be LOG N calls. Therefore
 * 		time complexity is O(N log N), space is due to stack function calls, depth of DFS is O(log N)
 *
 * 		- 	Find middle element via iteration. Every recursive call require you to pass in the starting node and ending node
 * 			Use two pointers (slow & fast pt) technique to find middle
 * 		-	Create root node on middle element
 * 		-	Assign root left child to be recursion call (left, mid)
 * 		-	Assign root right child to be recursion call (mid.next, right)
 * 		-	Note: If recursion receive start == end, return null.
 */

struct ListNode {
	int val;
	ListNode* next;
	ListNode() : val(0), next(nullptr) {}
	ListNode(int x): val(x), next(nullptr) {}
	ListNode(int x, ListNode* next) : val(x), next(next) {}
};

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

	//	O(N) time, O(N) space solution
	TreeNode* sortedListToBST(ListNode* head) {
		vector<TreeNode*> nodes;
		while (head) {
			nodes.push_back(new TreeNode(head->val));
			head = head->next;
		}
		return recurse(nodes, 0, nodes.size() - 1);
	}
	TreeNode* recurse(vector<TreeNode*>& nodes, int from, int to) {
		if (from == to) return nodes[from];
		if (from > to) return nullptr;

		int mid = from + (to - from) / 2;
		nodes[mid]->left = recurse(nodes, from, mid - 1);
		nodes[mid]->right = recurse(nodes, mid + 1, to);
		return nodes[mid];
	}


	//	O(N log N) time, O(log N) stack space (recursion) solution
	TreeNode* sortedListToBST2(ListNode* head) {
		if (!head) return nullptr;
		return recurse2(head, nullptr);
	}
	TreeNode* recurse2(ListNode* head, ListNode* end) {
		if (head == end) return nullptr;
		ListNode* fast = head, * slow = head;

		while (fast != end && fast->next != end) {
			fast = fast->next->next;
			if (fast == end) break;
			slow = slow->next;
		}
		TreeNode* root = new TreeNode(slow->val);
		root->left = recurse2(head, slow);
		root->right = recurse2(slow->next, end);
		return root;
	}


};