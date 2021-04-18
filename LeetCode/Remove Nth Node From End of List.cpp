struct ListNode {
	int val;
	ListNode* next;
	ListNode() : val(0), next(nullptr) {}
	ListNode(int x) : val(x), next(nullptr) {}
	ListNode(int x, ListNode* next) : val(x), next(next) {}
};

//https://leetcode.com/problems/remove-nth-node-from-end-of-list/
/*
 * 	This is a linked list problem, where linked list usually relates to two pointers
 *
 * 	Say linked list is length L
 * 	Make a fast pointer that is N steps ahead of the head node. Then, while fast pointer is not reached
 * 	the end, move both slow and fast pointer. At the end, fast pointer will be at Lth node, and slow pointer
 * 	will be at L - Nth node, which is the node we want to delete!
 *
 * 	Edge case is when L = N, then we detect it when fast pointer is already null to begin with after moving.
 * 	Then, simply return head.next
 */

class Solution {
public:
	ListNode* removeNthFromEnd(ListNode* head, int n) {
		ListNode* slow = head;
		ListNode* fast = head;

		while (n--) fast = fast->next;

		//	Edge case: Remove first element
		if (!fast) return head->next;

		while (fast->next) {
			fast = fast->next;
			slow = slow->next;
		}

		//	Reached. Remove the next node of slow pointer
		slow->next = slow->next->next;
		return head;
	}
};