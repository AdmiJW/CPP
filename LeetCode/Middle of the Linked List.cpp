//https://leetcode.com/problems/middle-of-the-linked-list/
/*
 * 	This is a two pointers, linked list problem.
 *
 * 	We start with 2 pointers - one slow and one fast. At each iteration, slow pointer moves 1 node, and fast
 * 	pointer moves 2 node at a time.
 *
 * 	Therefore, when the fast pointer had moved until the end of the linked list, the slow pointer should be pointing
 * 	at the middle of linked list.
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
	ListNode* middleNode(ListNode* head) {
        if (!head) return head;

        ListNode* slow = head, *fast = head;

        while (fast->next && fast->next->next) {
            slow = slow->next;
            fast = fast->next->next;
        }

        return ( !(fast->next) )
            ? slow
            : slow->next;
	}
};