#include <unordered_set>
using namespace std;

//https://leetcode.com/problems/linked-list-cycle/
/*
 * 	This is a Linked List Problem. Optimised solution requires concept of two pointers
 *
 * 	If a linked list contains a cycle, then there will never be an end (null). Conversely,
 * 	a linked list without cycle will eventually reach null
 *
 * 	The direct way would be to simply record the seen nodes. How can i check for seen
 * 	nodes in O(1) time? Sets or Maps will do.
 *
 * 	-----------------------------------------------------------
 *
 * 	To do it in O(1) space complexity, it would require Floyd's so-called Cycle Detection Algorithm,
 * 	aka Tortoise and Hare Algorithm.
 * 	It is a two pointers algorithm which one pointer is faster than the other.
 *
 * 	The idea is that, if there is a cycle in the linked list, both pointers will go into the loop, and
 * 	since both pointers travel at different speeds, eventually the pointers will meet at some point.
 *
 * 	On the other hand, if there is no cycle, then fast pointer will reach to null.
 *
 * 	The algorithm can be extended to trace back the starting node of the cycle, which requires a bit more
 * 	code. However, it is not needed in this case.
 */


struct ListNode {
	int val;
	ListNode* next;
	ListNode(int x) : val(x), next(nullptr) {}
};


class Solution {
public:
	//	Direct Way. Using HashSet to record past seen nodes
	bool hasCycle(ListNode* head) {
		unordered_set<ListNode*> seen;

		while (head) {
			if (seen.count(head)) return true;
			seen.insert(head);
			head = head->next;
		}
		return false;
	}


	//	Floyd's Tortoise and Hare (Two pointers) algorithm
	bool hasCycle2(ListNode* head) {
		if (!head) return false;

		ListNode* slow = head;
		ListNode* fast = head->next;

		while (fast && fast->next) {
			if (slow == fast) return true;
			
			slow = slow->next;
			fast = fast->next->next;
		}
		return false;
	}
};