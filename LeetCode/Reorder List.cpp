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

	void reorderList(ListNode* head) {
		// Step 1 - Get middle node
		ListNode* slow = head;
		ListNode* fast = head;
		while (fast->next && fast->next->next) {
			slow = slow->next;
			fast = fast->next->next;
		}

		
		// Step 2 - Make the middle node's next point to null (Because it will be the end of left half of linked list)
		fast = slow->next;
		slow->next = nullptr;
		slow = fast;


		// Step 3 - Reverse the right half of the linked list
		ListNode* reversedHead = nullptr;
		while (slow) {
			ListNode* nxt = slow->next;
			slow->next = reversedHead;
			reversedHead = slow;
			slow = nxt;
		}


		// Step 4 - Interconnect normal and reversed linked list
		ListNode dummy;

		for (ListNode* tail = &dummy; head || reversedHead; ) {
			if (head) {
				tail->next = head;
				tail = head;
				head = head->next;
			}
			if (reversedHead) {
				tail->next = reversedHead;
				tail = reversedHead;
				reversedHead = reversedHead->next;
			}
		}
	}

};