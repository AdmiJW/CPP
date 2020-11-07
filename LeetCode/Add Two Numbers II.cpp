
#include <stack>

//https://leetcode.com/problems/add-two-numbers-ii/

/*
*	This is a Linked list problem.
* 
*	Given 2 linked list head node which represents the Most Significant Digit in two integers. We are asked to find their sum.
*	Return the result as a linked list as well.
* 
*	When we do arithmetic, we'll do it from behind. Only when it overflows above 9, we will have a carry of 1 which is carried to
*	the digit at the left side. 
*	Unfortunately, this is a linked list. We traverse in only one direction - left to right, not the other way around. 
*	This is disasterous in this case:
*				99999999999 + 1
*	In this case, each digit will have to carry that overflow to the frontmost. How can we do this?
* 
*	** Note that at the end of calculation, there might be still a carry like the example above. In that case we need to append
*		a extra linked list node of value 1 into the result
* 
*	------------------------------------------------------------------------------------------------------------------
* 
*	One way is to reverse the linked list, so that we can operate on the least significant digit first. To reverse a linked list,
*	we can do it recursively, which each recursion stack will return the partially reversed linked list.
* 
*	------------------------------------------------------------------------------------------------------------------
* 
*	Alternative way is to utilize the property of Stack. Since stack follows LIFO pattern, The moment we filled the stack with the
*	linked list integer, when we pop the first digit it will be the least significant digit.
* 
*	-------------------------------------------------------------------------------------------------------------------
* 
*	Also, recursion can be done without reversing the linked list itself. What we do is first find out the lengths of both the integers,
*	then basically 'shift' the longer one so that we are both operating on two valid digits.
* 
*	Eg:
*			12345 + 678	
*	Since the difference in length is 2, we start the recursion when the longer one, 12345 is shifted 2 digits, which we will start
*	recursion on 345 + 678.
* 
*	Recursion will go until the least significant bit, add them up and return the ListNode of their sum
*	Now on the upper recursion stack, If the received value is greater or equal to 10, it will know it is overflow and therefore add
*	1 to the currently computed value, and return up the recursion stack.
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
	//	Stack SOlution
	ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
		std::stack<ListNode*> s1;
		std::stack<ListNode*> s2;

		while (l1) {
			s1.push(l1);
			l1 = l1->next;
		}
		while (l2) {
			s2.push(l2);
			l2 = l2->next;
		}

		bool carry = false;
		int sum;
		ListNode* head = nullptr;

		while (!s1.empty() && !s2.empty()) {
			sum = s1.top()->val + s2.top()->val + (carry ? 1 : 0);
			s1.pop(); s2.pop();
			carry = sum >= 10;
			ListNode* li = new ListNode(sum % 10);

			li->next = head;
			head = li;
		}
		while (!s1.empty() || !s2.empty()) {
			ListNode* pop = s1.empty() ? s2.top() : s1.top();
			sum = pop->val + (carry ? 1 : 0);
			s1.empty() ? s2.pop() : s1.pop();
			carry = sum >= 10;
			ListNode* li = new ListNode(sum % 10);

			li->next = head;
			head = li;
		}

		if (carry) {
			ListNode* li = new ListNode(1, head);
			head = li;
		}

		return head;
	}



	//	Recursion without Reverse
	ListNode* addTwoNumbersRecurse(ListNode* l1, ListNode* l2) {
		int len1 = 0, len2 = 0;
		ListNode* curr = l1;
		while (curr) {
			len1++;
			curr = curr->next;
		}
		curr = l2;
		while (curr) {
			len2++;
			curr = curr->next;
		}

		curr = recurse(l1, l2, len1 - len2);
		if (curr->val >= 10) {
			ListNode* li = new ListNode(1);
			li->next = curr;
			curr->val = curr->val % 10;
			curr = li;
		}

		return curr;
	}
	ListNode* recurse(ListNode * l1, ListNode * l2, int offset) {
		if (!l1) return nullptr;

		ListNode* res;
		//	If offset negative, len2 is larger
		if (offset < 0) {
			res = recurse(l1, l2->next, offset + 1);
		}
		//	If offset positive, len1 is larger
		else if (offset > 0) {
			res = recurse(l1->next, l2, offset - 1);
		}
		else {
			res = recurse(l1->next, l2->next, offset);
		}


		ListNode* li = new ListNode();
		li->val = (offset >= 0 ? l1->val : 0) + (offset <= 0 ? l2->val : 0) + (res ? res->val / 10 : 0);
		if (res) res->val = res->val % 10;
		li->next = res;
		return li;
	}
};