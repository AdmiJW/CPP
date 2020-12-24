
//https://leetcode.com/problems/swap-nodes-in-pairs/

/*
 * 	This is a linked list problem.
 *
 * 	Remember this very useful key property of linked list:
 * 			We are always able to reshape a new linked list while keeping a pointer to existing linked list using only
 * 			O(1) space. All we need is a dummy node to get started
 *
 * 	The key insight to be obtained from the problem is: When we want to swap 2 adjacent nodes, we must know 4 things:
 * 			>	First node to swap
 * 			>	Second node to swap
 * 			>	The node before the first node, since it is pointing to first node, we have to reestablish the connection
 * 			>	The node after the second node. It is being pointed to by the second node. Now it should be pointed by
 * 				first node after swapping
 *
 * 	By using the dummy node method, we always have access to the tail node which we assume the linked list is already have
 * 	the adjacent nodes swapped (Condition #3 solved)
 *
 * 	We will have an iterator of the linked list. While the iterator is not null, we will do some processing:
 * 		>	If this is the first node that has to be swapped, record it in a variable and continue (Condition #1 solved)
 * 		>	Otherwise this is the second node (Condition #2). Then, we do following:
 * 			-	Record the second node's next (Condition #4 solved)
 * 			-	Connect tail to second node
 * 			- 	Connect recorded first node to second node, so that they appear swapped
 * 			-	First node will connect to the recorded second node's next (So that it don't point back to second node)
 * 			-	Update the tail of the new linked list
 *
 *
 * 	The time complexity is O(N) and space is O(1)
 *
 *  -----------------------------------------------------------------------
 *
 *  Recursive approach is also applicable. We have a recursion function which always return the swapped linked list
 * 	from behind. (Bottom up?)
 * 	The recursion will be called for the next 2 nodes.
 *
 * 	The base case is if the node is alone or null, then we cannot do any swappings. Return them.
 *
 * 	Otherwise the recursion surely will return the swapped linked list from behind. Then we perform swapping, and
 * 	return the second node which after swapped, will be the head.
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
public:

	//	Iterative method
	ListNode* swapPairs(ListNode* head) {
		ListNode* curr = head;
		ListNode* dummy = new ListNode();
		ListNode* newTail = dummy;
		ListNode* first = nullptr;

		while (curr) {
			if (!first) {
				first = curr;
				curr = curr->next;
			}
			else {
				ListNode* second = curr;
				curr = curr->next;

				newTail->next = second;
				second->next = first;
				newTail = first;
				newTail->next = nullptr; // Otherwise the first node may
										//still point at second node

				first = nullptr;
			}
		}

		if (first) newTail->next = first;

		return dummy->next;
	}



	//	Recursive method
	ListNode* swapPairs2(ListNode* head) {
		if (!head || !head->next) return head;

		ListNode* res = swapPairs2(head->next->next);
		ListNode* next = head->next;
		head->next = res;
		next->next = head;

		return next;
	}
};