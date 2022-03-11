using namespace std;


// https://leetcode.com/problems/rotate-list/
/*
 * 	This is a two-pointers question. We are asked to rotate the linked list k steps to the right. Notice that the k might be larger than the linked list size.
 * 	This is example of limited state space question where it will be a cycle if k is larger than the linked list, it will go back to the original state and loop again.
 * 	Dealing with this kind of limited state space question, we need to find the loop and use modulo to prevent unnecessary calculations.
 *
 * 	The basic idea is to find out the length of the linked list. Then we have to modulo k by the length
 * 	Notice if k is now 0, then just return head. The rotation will end up at same place.
 * 	Then, move the pointer to the length - k'th node. This is the node which the rotated linked list ends. Save the next node in temp variable and put this node's next
 * 	as null.
 * 	Iterate to the end of the linked list and attach the head to end of linked list.
 */



struct ListNode {
	int val;
	ListNode *next;
	ListNode() : val(0), next(nullptr) {}
	ListNode(int x) : val(x), next(nullptr) {}
	ListNode(int x, ListNode *next) : val(x), next(next) {}
};


class Solution {
public:
	ListNode* rotateRight(ListNode* head, int k) {
		if (!head) return nullptr;

		// Step 1 - Obtain tail and length of linked list
		ListNode* tail = head;
		int length = 1;

		while (tail->next) {
			++length;
			tail = tail->next;
		}

		// Step 2 - Remove redundant rotations by modulo k
		k = k % length;

		// Step 3 - Tail connect to head to create a cycle
		tail->next = head;

		// The (N-k)th node  will be head of rotated list. Disconnect its previous and return
		ListNode* curr = head;
		for (int i = 0; i < length - k; ++i) {
			tail = curr;
			curr = curr->next;
		}

		tail->next = nullptr;
		return curr;
	}
};