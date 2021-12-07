
//https://leetcode.com/problems/convert-binary-number-in-a-linked-list-to-integer/
/*
 * 	THis is a bit manipulation - Linked list problem.
 *
 * 	When we traverse the linked list, we traverse from rightmost to leftmost. This means the digit we met earlier in the
 * 	linked list should be increase its digit position by 1 when we traverse to the next node.
 * 	Recall from binary representation, each position is 2^1, 2^2, 2^3 etc. This means that we have options:
 *
 * 	>	Use leftshift operator, which basically shift all bits to left by one
 * 	>	Use *2 every time we traverse the node.
 *
 * 	You should know that left shifting a binary number also multiplies by 2.
 * 	Eg: 101 ===> 1010   (5 ==> 10)
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

	//	BIT MANIPULATION ITERATIVE METHOD 
	int getDecimalValue(ListNode* head) {
		int res = 0;

		while (head) {
			res <<= 1;
			res += head->val;
			head = head->next;
		}

		return res;
	}



	//	Recursive Method - Done by passing value into next recursion call, and finally returning the result
	int getDecimalValueRecursion(ListNode* head) {
		return getDecimalValueRecursion(head, 0);
	}
	int getDecimalValueRecursion(ListNode* head, int val) {
		if (!head) return val;

		val <<= 1;
		val += head->val;
		
		return val;
	}




	//	MATH METHOD (*2 every time)
	int getDecimalValueMath(ListNode* head) {
		int res = 0;

		while (head) {
			res *= 2;
			res += head->val;
			head = head->next;
		}

		return res;
	}
};