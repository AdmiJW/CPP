
struct ListNode {
	int val;
	ListNode* next;
	ListNode() : val(0), next(nullptr) {}
	ListNode(int x) : val(x), next(nullptr) {}
	ListNode(int x, ListNode* next) : val(x), next(next) {}
};

class Solution {
public:
	ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
		ListNode dummy;
		ListNode* tail = &dummy;

		while (l1 || l2) {
			//	List 2 is exhausted, or List 1's value is less than List 2's value
			if (!l2 || l1 && l1->val < l2->val) {
				tail->next = l1;
				tail = tail->next;
				l1 = l1->next;
			}
			else {
				tail->next = l2;
				tail = tail->next;
				l2 = l2->next;
			}
		}
		return dummy.next;
	}


	ListNode* mergeTwoLists2(ListNode* l1, ListNode* l2) {
		ListNode* primary = (!l2|| l1 && l1->val < l2->val) ? l1 : l2;	//	The list that has the smallest starting value
		ListNode* secondary = (primary == l1) ? l2 : l1;		//	The list with greater starting value
		ListNode* curr = primary;							//	Current pointer in the primary list
		ListNode* prev = nullptr;							//	The node previous to the current pointer
	
		while (curr && secondary) {
			//	The node in primary List is greater than the node in secondary list. Insert the secondary list node behind the primary list's node
			if (curr->val > secondary->val) {
				ListNode* nextSecondary = secondary->next;
				if (prev) prev->next = secondary;
				prev = secondary;
				secondary->next = curr;
				secondary = nextSecondary;
			}
			//	Otherwise primary List Node is lesser than secondary list node. Proceed in primary list
			else {
				prev = curr;
				curr = curr->next;
			}
		}
		//	Secondary list haven't exhausted means all remaining nodes in secondary is greater than
		//	all nodes in primary. So append to primary list's tail
		if (secondary)
			prev->next = secondary;

		return primary;
	}



	ListNode* mergeTwoLists3(ListNode* l1, ListNode* l2) {
		//	Base cases. Either node is null, just return the other one
		if (!l1) return l2;
		if (!l2) return l1;

		//	Otherwise we have to pick the lesser node, and recurse to obtain the next node supposed to connect
		//	Then return the lesser node
		if (l1->val < l2->val) {
			l1->next = mergeTwoLists3(l1->next, l2);
			return l1;
		}
		else {
			l2->next = mergeTwoLists3(l1, l2->next);
			return l2;
		}
	}
};