
//https://leetcode.com/problems/flatten-a-multilevel-doubly-linked-list/
/*
 * 	This is a linked list problem.
 *
 *  We will iterate through the linked list. Once we found a node with child chain, then we will recursively call on the
 *  child chain to flatten it and obtain its tail node. Then, we essentially have to
 *
 *  	- Make curr.next to be the curr.child
 *  	- Make the curr.child to be null
 *  	- Make node.child.prev to be curr
 *  	- Make childTail.next to be curr.next
 *  	- Make curr.next.prev to be childTail
 *
 *  (These are not logically ordered yet. You will have to check properly in your code)
 */


struct Node {
	int val;
	Node* prev;
	Node* next;
	Node* child;
};


class Solution {
public:
	Node* flatten(Node* head) {
		flattenAndGetTail(head);
		return head;
	}

	Node* flattenAndGetTail(Node* head) {
		Node* prev = nullptr;
		while (head) {
			// Contains another level of linked list
			if (head->child) {
				Node* next = head->next;
				Node* childTail = flattenAndGetTail(head->child);
				prev = childTail;

				head->next = head->child;
				head->child->prev = head;
				head->child = nullptr;

				childTail->next = next;
				if (next) next->prev = childTail;
				head = childTail->next;
			}
			else {
				prev = head;
				head = head->next;
			}
		}
		return prev;
	}
};