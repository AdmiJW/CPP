#include <utility>
using namespace std;

struct ListNode {
	int val;
	ListNode* next;
	ListNode() : val(0), next(nullptr) {}
	ListNode(int x) : val(x), next(nullptr) {}
	ListNode(int x, ListNode* next) : val(x), next(next) {}
};


class Solution {
public:
	//	Two pass, counting length solution
	ListNode* swapNodes(ListNode* head, int k) {
		//	Evaluate length of the linked list
		int len = 0;
		ListNode* curr = head;
		while (curr) {
			++len;
			curr = curr->next;
		}

		//	Search for the corresponding nodes, kth node and n-k th node
		int other = len - k + 1;
		ListNode* first = nullptr, *second = nullptr;
		curr = head;

		while (!first || !second) {
			if (len == other) second = curr;
			if (len == k) first = curr;			//	Do not use else if. It may happen where n-k and k is same node

			curr = curr->next;
			--len;
		}

		//	Swap and return head
		int temp = second->val;
		second->val = first->val;
		first->val = temp;
		return head;
	}


	//	Two pass, reversing linked list solution
	ListNode* swapNodes2(ListNode* head, int k) {
		auto result = getAndReverse(head, k);
		ListNode* node1 = result.second;
		result = getAndReverse(result.first, k);
		ListNode* node2 = result.second;

		int temp = node1->val;
		node1->val = node2->val;
		node2->val = temp;
		return result.first;
	}
	pair<ListNode*, ListNode*> getAndReverse(ListNode* head, int k) {
		pair<ListNode*, ListNode*> res;
		ListNode* prev = nullptr;

		while (head) {
			if (!(--k)) res.second = head;

			ListNode* next = head->next;
			head->next = prev;
			prev = head;
			head = next;
		}
		res.first = prev;
		return res;
	}


	//	Two pointers, one pass solution
	ListNode* swapNodes3(ListNode* head, int k) {
		ListNode* n1 = nullptr, * n2 = nullptr;

		for (ListNode* p = head; p; p = p->next) {
			//	If slow pointer is already set up, move it forward
			n1 = n1 ? n1->next : nullptr;

			//	Met the first node to swap. Now setup the slow pointer!
			if (!(--k)) {
				n2 = p;
				n1 = head;
			}
		}
		int temp = n1->val;
		n1->val = n2->val;
		n2->val = temp;
		return head;
	}
};