using namespace std;

//https://leetcode.com/problems/odd-even-linked-list/
/*
*	This is a linked list problem.
* 
*	With my idea, simply construct two linked list from existing nodes: Oddlist and Evenlist. Then at the end, connect
*	them two and return the combined linked list.
* 
*	Using the concept of dummy node, everything can be done much more easier and readable way.
* 
*	Keep track of 4 items: oddHead, oddTail, evenHead, evenTail. Iterate through the original linked list and append them
*	to oddTail or evenTail accordingly. 
*	At the end, connect oddTail to evenHead (Not the dummy node), and point evenTail to null. Return the oddHead (Not the dummy node)
* 
*/

struct ListNode {
	int val;
	ListNode* next;
	ListNode() : val(0), next(nullptr) {}
	ListNode(int x) : val(x), next(nullptr) {}
	ListNode(int x, ListNode* next) : val(x), next(next) {}
};



class Solution {

	ListNode* oddEvenList(ListNode* head) {
		ListNode oddHead;
		ListNode evenHead;
		ListNode* oddTail = &oddHead;
		ListNode* evenTail = &evenHead;

		for (int i = 1; head; ++i, head = head->next) {
			// Odd
			if (i & 1) {
				oddTail->next = head;
				oddTail = oddTail->next;
			}
			// Even
			else {
				evenTail->next = head;
				evenTail = evenTail->next;
			}
		}

		evenTail->next = nullptr;
		oddTail->next = evenHead.next;
		return oddHead.next;
	}

};