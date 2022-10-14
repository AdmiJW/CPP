#include <vector>
using namespace std;

// https://leetcode.com/problems/delete-the-middle-node-of-a-linked-list/
/*
 * This is a linked list problem.
 *
 * A way is to simply iterate 2 passes - One to determine length of linked list, and then remove the one at (n/2) + 1
 *
 * Another way is simply use two pointers - fast and slow to get the middle node.
 * Due to the nature of the problem, we could use a dummy node in front of head node
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
    ListNode* deleteMiddle(ListNode* head) {
        ListNode* dummy = new ListNode();
        dummy->next = head;

        ListNode* fast = head, *slow = dummy;

        while ( fast && fast->next ) {
            fast = fast->next->next;
            slow = slow->next;
        }

        slow->next = slow->next->next;
        return dummy->next;
    }
};