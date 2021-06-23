#include <stack>
using namespace std;

//https://leetcode.com/problems/reverse-linked-list-ii/
/*
 * 	This is a Linked list problem.
 *
 * 	We are required to only reverse parts of the linked list. Let's see how can we do it.
 *
 * 	The first thought is to use Stack for the job. Stack is well known for its ability to reverse things.
 * 	Therefore we traverse the linked list, keep a reference of the node just before the section to reverse,
 * 	push everything to reverse into the stack, and also keep a reference to the node after reversal section.
 *
 * 	Then, if we were to pop the nodes from stack, all of them will be in correct order.
 *
 * 	Time taken is O(2N), and O(N) space as well.
 *
 * 	=======================================================
 *
 * 	Turns out one pass solution also can be done. First we traverse and keep a reference to the node just before
 * 	the section to reverse like above, then for all the nodes that needs to be reversed, we REVERSE THEIR NEXT
 * 	like so:
 * 		(2) -> (3) -> (4)
 * 	to
 * 		(2) <- (3) <- (4)
 *
 * 	Then, we should have a linked list that looks like this (Assume left = 2, right = 4):
 *
 * 		(1) -> (2) <- (3) <- (4)  (5)
 *
 * 	(1) is kept in our reference. (5) and (4) should also be in our variables. (2) is referenced by (1)'s next.
 * 	We have all we need to reverse the list:
 * 		(1) next is set to (4)
 * 		(2) next is set to (5)
 * 	and we are done in one pass! O(N) time and O(1) space
 */

struct ListNode {
	int val;
	ListNode* next;
	ListNode() : val(0), next(nullptr) {}
	ListNode(int x) : val(x), next(nullptr) {}
};


class Solution {
public:

	//	Stack solution
	ListNode* reverseBetween(ListNode* head, int left, int right) {
		//	Dummy node
		ListNode d;
		d.next = head;
		ListNode* end = &d;
		ListNode* start = nullptr;
		stack<ListNode*> stk;

		//	Traverse to the start, just before the node to reverse
		for (int i = 1; i < left; ++i)
			end = end->next;

		//	Node before reversal part
		start = end;

		//	Push all nodes to reverse into stack
		for (int i = 0; i < right - left + 1; ++i) {
			end = end->next;
			stk.push(end);
		}

		//	Node after reversal
		end = end->next;

		//	Keep appending the nodes in the stack
		while (!stk.empty()) {
			start->next = stk.top(); stk.pop();
			start = start->next;
		}
		start->next = end;

		return d.next;
	}




	//	One pass solution
	ListNode* reverseBetween2(ListNode* head, int left, int right) {
		//		Dummy node
		ListNode d;
		d.next = head;
		ListNode* pt = &d;
		ListNode* start = nullptr;

		//	Traverse to the node just before reversal section
		for (int i = 1; i < left; ++i)
			pt = pt->next;

		//	Node before reversal part
		start = pt;
		pt = pt->next;

		//	Reverse all the nodes inside to reversal.
		ListNode* prev = nullptr;
		for (int i = 0; i < right - left + 1; ++i) {
			ListNode* next = pt->next;
			pt->next = prev;
			prev = pt;
			pt = next;
		}

		//	Connect reversed part to correct order
		start->next->next = pt;
		start->next = prev;

		return d.next;
	}
};