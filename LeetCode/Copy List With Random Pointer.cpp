#include <unordered_map>
using namespace std;

//https://leetcode.com/problems/copy-list-with-random-pointer/
/*
 * 	This is obviously a Linked List problem, with one solution using HashMap
 *
 * 	One easy solution is to use a HashMap which maps from original node to cloned node. This way
 * 	when cloning the Linked List, we can know easily whether a node has been cloned before or not
 * 	when assigning next node or random node.
 *
 * 	O(N) time with O(N) space cost
 *
 * 	-----------------------------------------------------------------
 *
 * 	Let's try constant space solution. The core problem is able to:
 * 		>	Know a cloned node exists or not
 * 		>	Able to retrieve cloned node in O(1) without going through linked list
 *
 * 	Given constant space, we can try to modify the Linked List itself! We just have to return it to
 * 	original form before finishing.
 *
 * 	(A) -> (A clone) -> (B) -> (B clone) -> (C) -> (C clone) ...
 *
 * 	For each original node, create its clone node, and put it as original node's next. Cloned node's
 * 	next will be the next original node.
 *
 * 	Then, in another loop, since we know already that original node's next is the cloned node, assigning
 * 	random pointer is easy.
 *
 * 	Finally, return original linked list back to original state. For each original node, get reference to
 * 	its clone node, then:
 * 		>	Original node will connect back to clone node's next
 * 		>	Clone node will connect to next original node's next (Cloned), if exists.
 *
 * 	Time is O(3N) but O(1) space complexity
 */


struct Node {
	int val;
	Node* next;
	Node* random;
	Node(int _val) : val(_val), next(nullptr), random(nullptr) {}
};


class Solution {
public:
	Node* copyRandomList(Node* head) {
		unordered_map<Node*, Node*> map;
		Node dummy(0);
		Node* tail = &dummy;

		while (head) {
			map.insert({ {head, new Node(head->val)} } );

			if (head->random) {
				map.insert({ {head->random, new Node(head->random->val)} });
				map[head]->random = map[head->random];
			}

			tail->next = map[head];
			tail = tail->next;
			head = head->next;
		}

		return dummy.next;
	}


	Node* copyRandomList2(Node* head) {
		if (!head) return nullptr;
		Node* pt;

		//	Insert clone node into old node's next
		for (pt = head; pt; pt = pt->next->next) {
			Node* clone = new Node(pt->val);
			clone->next = pt->next;
			pt->next = clone;
		}

		//	Assign Random
		for (pt = head; pt; pt = pt->next->next) {
			if (pt->random)
				pt->next->random = pt->random->next;
		}

		Node* cloned = head->next;
		//	Disconnect
		for (pt = head; pt; pt = pt->next) {
			Node* clone = pt->next;
			pt->next = clone->next;
			if (pt->next) clone->next = pt->next->next;
		}

		return cloned;
	}
};