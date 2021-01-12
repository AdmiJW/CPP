
//https://leetcode.com/problems/add-two-numbers/
/*
 * 	This is a linked list problem.
 *
 * 	If we want, we can also do it in place, Taking O(1) space. But we won't here
 *
 * 	The idea is direct: Using two pointers, add the two nodes. If exceed 10,
 * 	store it into carry variable. The next node, the carry need to be added.
 *
 * 	At the end, if the carry is still true, add a new node of 1.
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
	ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
		ListNode dummyInst;
		ListNode* dummy = &dummyInst;
		ListNode* tail = dummy;

		bool carry = false;

		while (l1 || l2) {
			int val = (l1 ? l1->val : 0) + (l2 ? l2->val : 0) + carry;
			carry = val >= 10;
			val %= 10;

			tail->next = new ListNode(val);
			tail = tail->next;

			l1 = l1 ? l1->next : l1;
			l2 = l2 ? l2->next : l2;
		}

		if (carry) tail->next = new ListNode(1);
		return dummy->next;
	}


	//	Recursive Method
	ListNode* addTwoNumbers(ListNode* l1, ListNode* l2, bool carry=false) {
		if (!l1 && !l2) {
			return carry ? new ListNode(1) : nullptr;
		}

		int sum = (l1 ? l1->val : 0) + (l2 ? l2->val : 0) + carry;
		
		ListNode* toAppend = addTwoNumbers(l1 ? l1->next : nullptr, l2 ? l2->next : nullptr, sum >= 10);
		ListNode* newNode = new ListNode(sum % 10);
		newNode->next = toAppend;

		return newNode;
	}
};