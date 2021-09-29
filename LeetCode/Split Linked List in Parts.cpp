#include <vector>
using namespace std;

/*
 *  This is a linked list problem.
 *
 *  The idea involves a little math: First we must know the length of linked list.
 *
 *  Then, we can calculate:
 *  	- Each segment SHOULD HAVE AT LEAST len/k nodes
 *  	- Then, there may be leftover nodes of len%k. We distribute these leftover to each of the segment, 1 each.
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
	vector<ListNode*> splitListToParts(ListNode* head, int k) {
		// First, obtain length and nodes in each part
		int len = 0;
		vector<ListNode*> res(k, nullptr);

		for (ListNode* pt = head; pt; pt = pt->next) ++len;

		int baselen = len / k;
		int mod = len % k;


		// Splitting linked list. i means ith part
		for (int i = 0; i < k; ++i) {
			// Put baselen nodes into the result[i]
			res[i] = head;

			// Skip over x nodes where x is the node count that should be inside this part
			for (int nodeleft = baselen + (mod > 0 ? 1 : 0) - 1; head && nodeleft > 0; --nodeleft)
				head = head->next;

			// Go to next node if it is not null (Current node is the last node of current segment)
			if (head) {
				ListNode* next = head->next;
				head->next = nullptr;
				head = next;
			}
			// Mod node is used up.
			--mod;
		}
		return res;
	}
};