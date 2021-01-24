#include <queue>
#include <vector>
using namespace std;

//https://leetcode.com/problems/merge-k-sorted-lists/
/*
 * This question is highly related to the merging process in Merge Sort algorithm.
 * Do check it out if haven't
 *
 * The core intuition is very similar to how we merge 2 linked lists in Merge Sort.
 * However this time we have K sorted lists instead of just 2! How?
 *
 * One brute forcey way is:
 * 		While there is still lists that aren't finish yet, iterate through all the HEAD of
 * 		K lists. Find out the minimum one, to append to the new linked list.
 *
 * 	The time complexity is approximately O(NK) because:
 * 		while there are elements still left, an iteration of K times will run to find minimum node.
 * 		There are total of N elements.
 *
 *	------------------------------------------------------------------------------------
 *
 *	The expensive part of above algorithm is the iteration of K times. Can we search out the minimum
 *	node in shorter time complexity? O(Log N)? - Heaps!
 *
 *	Push every Head of the sorted linked list into the Heap. It will sort out automatically for us.
 *	Then pop out the smallest one, append to tail of new linked list, then check:
 *	If the popped linked list has next node, push the next node into Heap.
 *
 *	Time complexity reduced to O(N log K), but space O(K) is traded off
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
	//	Brute-forcey way. Iterate K each time, leading
	//	to O(KN) time
	ListNode* mergeKLists(vector<ListNode*>& lists) {
		ListNode dummy;
		ListNode* tail = &dummy;

		while (1) {
			ListNode* next = &dummy;
			int index = -1;

			for (int i = 0; i < lists.size(); ++i) {
				if (lists[i] && lists[i]->val < next->val) {
					index = i;
					next = lists[i];
				}
			}

			if (next == &dummy) break;

			tail->next = next;
			tail = tail->next;
			lists[index] = next->next;
		}
		return dummy.next;
	}



	//Heap Solution
	class Comparator {
	public:
		bool operator() (const ListNode* l, const ListNode* r) {
			return l->val < r->val;
		}
	};
	ListNode* mergeKLists2(vector<ListNode*>& lists) {
		priority_queue<ListNode*, vector<ListNode*>, Comparator > heap;
		
		for (ListNode* l : lists) 
			if (l) heap.push(l);

		ListNode dummy;
		ListNode* tail = &dummy;

		while (!heap.empty()) {
			ListNode* pop = heap.top(); heap.pop();
			tail->next = pop;
			tail = tail->next;

			if (pop->next) heap.push(pop->next);
		}

		return dummy.next;
	}
};