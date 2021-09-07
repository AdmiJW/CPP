//https://leetcode.com/problems/reverse-linked-list/
/*
 * 	This is a Linked List problem.
 *
 * 	To reverse the linked list in linear time and constant space, we'll use 3 pointers:
 * 		- Previous node, current node and next node
 * 	At each iteration, point the current node's pointer to previous node, then do the same with
 * 	the following nodes.
 * 	At the end, the last node will be the new head of reversed linked list
 *
 * 	---------------------
 *
 * 	Recursive solution:
 * 	The recursive function will obviously return the head of REVERSED linked list.
 * 	The base case is when head is null, or head.next is null (Means when reversed, it is the head)
 *
 * 	In other cases, obtain the head of reversed list, and reverse the next node's pointer to point to yourself
 */

struct ListNode {
	int val;
	ListNode* next;
	ListNode() : val(0), next(nullptr) {}
	ListNode(int x) : val(x), next(nullptr) {}
	ListNode(int x, ListNode* next) : val(x), next(next) {}
};


class Solution {
public:
	ListNode* reverseList(ListNode* head) {
		ListNode* prev = nullptr;
		while (head) {
			ListNode* next = head->next;
			head->next = prev;
			prev = head;
			head = next;
		}
		return prev;
	}


	ListNode* reverseList2(ListNode* head) {
		if (!head || !(head->next)) return head;
		ListNode* realHead = reverseList2(head->next);
		head->next->next = head;
		head->next = nullptr;
		return realHead;
	}
};