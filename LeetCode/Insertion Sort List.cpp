//https://leetcode.com/problems/insertion-sort-list/

/*
 * 	This is, obviously a insertion sort problem, with linked list.
 *
 * 	The basic idea of insertion sort is that we keep trying to insert elements one by one into a partially sorted
 * 	linked list. Do this with every element, then the whole list will be sorted at the end.
 *
 * 	For this to be achieved in a linked list, we can have a fake head pointer which shall point at the start of the
 * 	sorted linked list. Initially, it will be empty but hopefully at the end, it will point to head of fully sorted
 * 	linked list.
 * 	Therefore, we will be expanding this supposedly sorted linked list one by one element. From the original, unsorted
 * 	list, we will be trying to insert the element into the partially sorted linked list. This is done by just having this
 * 	element and iterate through the partially sorted linked list until it found its supposed place.
 *
 * 	The element will be inserted and have the connections established (The node has to point at a valid next, and
 * 	also the element previous to the inserted node also have to point to this inserted node).
 *	After that, we continue with the next element in the original linked list. Note that all the nodes in the partially
 *	linked list are all nodes that is previous to the pointer in original linked list, so we don't worry about messing up
 *	the original linked list
 *
 *	===============================================================================================================
 *
 *	One solution is by recursive method though (Although in theory it is worse due to O(N) space of recursive stack)
 *
 *	The recursive works by first recurse until the end of the list, and returning the partially sorted list from the
 *	backwards. Then on the current node, try to insert the node into the partially sorted list, and return the
 *	head of partially sorted list back up one recursion layer
 *
 */
struct ListNode {
	int val;
	ListNode* next;
	ListNode() : val(0), next(nullptr) {}
	ListNode(int val) : val(val), next(nullptr) {}
	ListNode(int val, ListNode* next) : val(val), next(next) {}
};


class Solution {
public:
	ListNode* insertionSortList(ListNode* head) {
		if (!head || !head->next) return head;

		ListNode* sorted = insertionSortList(head->next);

		//	If current node was the head, then connect and return this node
		if (head->val <= sorted->val) {
			head->next = sorted;
			return head;
		}

		//	Otherwise the head of partially sorted linked list won't change. Insert current node and return head
		ListNode* curr = sorted;
		while (curr->next && curr->next->val < head->val) {
			curr = curr->next;
		}

		ListNode* temp = curr->next;
		curr->next = head;
		head->next = temp;

		return sorted;
	}



	ListNode* insertionSortListIterative(ListNode* head) {
		if (!head) return nullptr;

		ListNode* sortedHead = nullptr;
		ListNode* toInsert = head;
		ListNode* nextToInsert = toInsert;

		while (toInsert) {
			nextToInsert = toInsert->next;
			sortedHead = insertion(toInsert, sortedHead);
			toInsert = nextToInsert;
		}

		return sortedHead;
	}
private:
	ListNode* insertion(ListNode* nodeToInsert, ListNode* sortedHead) {
		//	If current node was the head, then connect and return this node
		if (!sortedHead || nodeToInsert->val <= sortedHead->val) {
			nodeToInsert->next = sortedHead;
			return nodeToInsert;
		}

		//	Otherwise the head of partially sorted linked list won't change. Insert current node and return head
		ListNode* curr = sortedHead;
		while (curr->next && curr->next->val < nodeToInsert->val) {
			curr = curr->next;
		}

		ListNode* temp = curr->next;
		curr->next = nodeToInsert;
		nodeToInsert->next = temp;

		return sortedHead;
	}
};