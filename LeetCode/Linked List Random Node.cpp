
#include <string>

//https://leetcode.com/problems/linked-list-random-node/

/*
 * 	This is a Reservoir Sampling Problem, which is a statistics / probability problem, not really related to programming
 *
 * 	Given a buffer of data (Represented by linked list), we have to pick out nodes randomly and return value of it.
 * 	Every node must have approximately same probability of being chosen.
 *
 * 	Since it is a buffer, means we are unable to find out the length of the whole data. We shouldn't store the whole buffer
 * 	in the memory first and randomly select, as the buffer itself may be very large to store entirely in the memory.
 *
 *	Therefore in real situation, a O(N) time complexity is a must. We have to at least iterate through each node of the list.
 *
 *	How would we go about selecting random nodes then, if we are just iterating forward? Flipping coins?
 *	Holding a node, we receive the next element. If we are to flip the coin to decide whether the element should be replaced
 *	or not, it is not random.
 *		>	The first coin should be always selected first. As the N size goes larger, the probability of first element
 *			being replaced increases, and thus probability of it selected is going to be smaller.
 *
 *	Therefore, what if we assign a random number to each of the nodes, and pick out the node with the maximum random number?
 *	That indeed is a random way. In the case of selecting 1 node only, the time complexity is O(N). In each node we iterate,
 *	a random number is generated. If it is greater than the one we holding, replace it.
 *
 *	However if we were to select k elements, we should be using a heap instead where the element's assigned random number is
 *	the sorting key in the heap. The heap will be of size k and at last, it shall contain the k most maximum random number
 *	assigned nodes. The time complexity rises to O(N log N)
 *
 *	--------------------------------------------------------------------------------------------------------
 *
 *	There is a better way than just assigning each element random numbers, which is reservoir sampling.
 *
 *	Ask yourself, if I have 3 elements.
 *		>	Element 1 shall always be selected and held first
 *		>	What is the probability that element 2 shall replace element 1?
 *			The answer is 1/2. It has half the chance of replacing
 *		>	What is the probability that element 3 shall replace whatever we are holding?
 *
 *	The answer turns out to be 1/3. Let's see:
 *
 *		The probability of Elem 1 Selected is: P(select elem 1) * P(e1 not being replaced)
 *		The probability of Elem 2 Selected is: P(select elem 2) * P(e2 not being replaced)
 *		The probability of Elem 3 Selected is: P(select elem 3)
 *		and each of these probability must be equal.
 *
 *	Perhaps the probability that we should assign to selecting Nth node is 1/n?
 *
 *	P(select elem1) is 1. Then, P(e1 not replaced) turns out to be COMPLEMENT of P(e2 selected) and P(e3 selected), which is
 *			(1 - P(e2 selected) ) * (1 - P(e3 selected) )
 *	Surely, P(e1 not replaced) is then (1-P(e2 selected)) * (1-P(e3 selected)) * .... * (1-P(eN selected)) for N length list.
 *
 *	which is (1 - 1/2) * (1 - 1/3) * ... * (1 - 1/n)
 *
 *	Now, turns out by simplification using algebra, equation
 *			P(e1) = P(e1 selected) * P(e2 not selected) * P(e3 not selected) ... P(eN not selected)
 *	can be simplified to
 *			1/n
 *
 *	That means all the element has equal probability of being chosen! (This can be more easily proven by induction)
 *
 *	-----------------------------------------------------------
 *
 *	Therefore for selecting k elements, a random int from 1 to current index is selected. If it is less than k,
 *	we immediately place the current element in the array of index random number generated.
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
	ListNode* head;
public:
	Solution(ListNode* head) : head(head) {}

	//	Algorithm R - The simplest Reservoir sampling algorithm
	int getRandom() {
		int cnt = 1;
		ListNode* hold = head;
		ListNode* it = head->next;

		while (it) {
			cnt++;
			//	Obtain floating number from 1 to cnt
			int rand = std::rand() % cnt + 1;
			if (rand == cnt)
				hold = it;
			it = it->next;
		}
		return hold->val;
	}


	//	The assign random numbers to each node and find maximum solution
	int getRandom2() {
		int prob = std::rand();
		ListNode* hold = head;
		ListNode* it = head;

		while (it->next) {
			it = it->next;
			int rand = std::rand();
			if (rand > prob) {
				hold = it;
				prob = rand;
			}
		}

		return hold->val;
	}
};