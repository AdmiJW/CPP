
#include <unordered_set>
using namespace std;

//https://leetcode.com/problems/intersection-of-two-linked-lists/
/*
 * 	This is a Linked List Problem
 *
 *	----------------------------------------------------------
 *
 *	Brute force solution is O(N^2) time. For each node in linked list A, check if it is intersecting with linked list B
 *	by running iteration every time. Obviously if one of the linked list is long, it will take a lot of time
 *
 *	-----------------------------------------------------------
 *
 *	Instead, we record every node in linked list A through a Set, and run a iteration in linked list B to check if any
 *	node in linked list B is in the set. If yes, it will be the first node to be intersecting with linked list A, due
 *	to iteration always run from left to right.
 *
 *	Time is O(N) while taking space O(N) as well
 *
 *	-----------------------------------------------------------
 *
 *	Note what it said: Every node is 1 to 10^9. So, let's transform the linked list A so that when iterating linked list
 *	B, we can identify that some nodes are nodes in linked list A. At the end, transform linked list A back to its original
 *	form.
 *
 *	One of such transformation we can perform, is to make all vlaues in linked list A negative. Then when we iterate through
 *	linked list B, if we meet a negative valued node, immediately we can tell it is intersecting node!
 *
 *	Time is O(N) while space is O(1)
 *
 *	------------------------------------------------------------
 *
 *	We can offset one of the longer linked lists, so that both two pointers would reach the end at the same time. definitely,
 *	if they intersect, at one moment the two pointers will point to the very same intersected node!
 *
 *	>	Count lengths of both linked list
 *	>	Offset the longer linked list
 *	>	Run iteration and check if two pointers are same
 *
 *	Time is O(N) while space is O(1)
 */

struct ListNode {
	int val;
	ListNode* next;
	ListNode(int x) : val(x), next(nullptr) {}
};


class Solution {
public:

	//	Brute force solution
	ListNode* getIntersectionNode(ListNode* headA, ListNode* headB) {
		while (headA) {
			ListNode* temp = headB;

			while (temp && temp != headA)
				temp = temp->next;

			if (temp == headA) return temp;
			headA = headA->next;
		}
		return nullptr;
	}


	//	Set solution
	ListNode* getIntersectionNode2(ListNode* headA, ListNode* headB) {
		unordered_set<ListNode*> A;
		for (; headA; headA = headA->next)
			A.insert(headA);

		for (; headB; headB = headB->next)
			if (A.count(headB)) return headB;

		return nullptr;
	}


	//	In place marking solution
	ListNode* getIntersectionNode3(ListNode* headA, ListNode* headB) {
		ListNode* A = headA;
		for (; A; A = A->next)
			A->val = -A->val;

		ListNode* res = nullptr;
		for (; headB; headB = headB->next) {
			if (headB->val < 0) {
				res = headB;
				break;
			}
		}

		for (; headA; headA = headA->next)
			headA->val = -headA->val;

		return res;
	}


	//	Offset length solution
	ListNode* getIntersectionNode4(ListNode* headA, ListNode* headB) {
		ListNode* A = headA, * B = headB;
		int lenA = 0, lenB = 0;

		for (; A; A = A->next) ++lenA;
		for (; B; B = B->next) ++lenB;

		//	A will be longer, B will be shorter
		A = lenA > lenB ? headA : headB;
		B = A == headA ? headB : headA;

		//	Offset
		for (int i = abs(lenA - lenB); i > 0; --i)
			A = A->next;

		while (A) {
			if (A == B) return A;
			A = A->next;
			B = B->next;
		}
		return nullptr;
	}
};