
#define NULL '\0'

//https://leetcode.com/problems/linked-list-cycle-ii/

/*
	This is a linked list, cycle, Floyd Tortoise and Hare algorithm problem.

	To detect a cycle in linked list is simple using two pointers. One goes 2 step at a time while another goes one step at a time.
	If they collide at some point, that means there definitely is a cycle in the linked list. Otherwise the fast pointer would've
	ended up at the tail of linked list which is NULL.

	Now, how to find the beginning of the cycle? THis needs some visualization

	Let the beginning node of cycle be A
	Let the node where 2 pointer meet be B
	Let the distance from head node to A be x
	Let the distance from A to B be y
	Let the distance from B to A back (not reverse direction) be z

	Look:

				(B)---( )
				/		\
			[z]( )		( ) [y]
		[x]		\		/
	( )---( )---(A)---( )

	Now. Relate those information:
	At point B when they meet, slow pointer moved x + y distance
							   fast pointer moved (x+y+z) + y distance = x + 2y + z
	Since fast pointer move at twice speed, the distance fast pointer covered must be 2x that of slow pointer's
	Therefore,
								x + y = 2( x + 2y + z )
	Simplify,
								x = z
	The distance from beginning to A is equal to the distance from B to A! 
	Therefore put one of pointers back to head, so that
		One pointer will move x distance
		One pointer will move z distance
	When they collide again, that is the point of entry of cycle!
*/

struct ListNode {
	int val;
	ListNode* next;
	ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
	ListNode* detectCycle(ListNode* head) {
		if ( !head ) return NULL;

		ListNode* slow = head;
		ListNode* fast = head;

		do {
			fast = fast->next;
			slow = slow->next;
			if (!fast) return NULL;
			fast = fast->next;
		} while (fast && fast != slow);

		if ( !fast ) return NULL;

		slow = head;

		while (fast != slow) {
			fast = fast->next;
			slow = slow->next;
		}
		return fast;

	}
};