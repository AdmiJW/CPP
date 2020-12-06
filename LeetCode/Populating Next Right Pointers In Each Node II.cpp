#include <queue>
using namespace std;

//https://leetcode.com/problems/populating-next-right-pointers-in-each-node-ii/

/*
 * 	This is a Tree BFS / DFS problem. The hard part is to solve it in O(1) space
 *
 * 	The most easiest implementation is to use Queue to perform level order search. At each iteration,
 * 	the nodes at the same level should all be placed in Queue. Taking note of the number of nodes in the
 * 	queue, pop them out and connect one to the next, except the last one. Also push the child nodes into the
 * 	queue as well for next level iteration (Be careful not to connect across levels!)
 *
 * 	-------------------------------------------------------------------------------------------------
 *
 * 	To avoid using Stack, we should use the fact that from top-down, the upper level must all have the next
 * 	pointer already populated. How would we use the upper level's next pointer to aid us in connecting the nodes
 * 	in current level?
 *
 * 	For DFS solution, preferably we should always encounter the leftmost node in the level, and upper level
 * 	has all next pointer populated. In that way:
 *
 * 		As soon as we encounter a node, check if the node's rightmost child node is connected or not. If not,
 * 		start the connection process across the whole level.
 * 		This is done by using the fact that current node has the next pointer already populated. Using loops,
 * 		find the next closest node to connect.
 * 		Once connected, this is not finished. We shouldn't leave the connection done halfway in a level. Set
 * 		current node to that closest node, and continue the process until hit the level's end.
 *
 * 	Then, we recurse on the lower nodes, knowing this level connection is established, it is safe to recurse.
 *
 * 	---------------------------------------------------------------------------------------------------
 *
 * 	The most ingenious solution is using the concept of linked list.
 *
 * 	Start from top level - Level 1.
 *
 * 	While the node is not null:
 *
 * 		Set up a linked list equivalent structure for the level:
 * 		>	Create a dummy node, and set tail to be dummy node.
 * 		>	While node is not null, then
 * 				if node left exists, connect it to linked list, and update tail
 * 				then
 * 				if node right exists, connect it to linked list, and update tail
 * 			Once done, proceed to the node's next
 *
 * 		>	Once the node hit null, it means the level is done traversing. How do we go to the next level's
 * 			leftmost node? Notice the dummy node is head of linked list, and the leftmost node is connected
 * 			next to head! Go to it!!!
 *
 */

struct Node {
	int val;
	Node* left;
	Node* right;
	Node* next;
};



class Solution {
public:
	Node* connect(Node* root) {
		if (!root) return nullptr;
		queue<Node*> queue;
		queue.push(root);

		while (!queue.empty()) {
			int levelSize = queue.size();

			while (levelSize-- > 1) {
				Node* node = queue.front();
				queue.pop();
				Node* next = queue.front();

				if (node->left) queue.push(node->left);
				if (node->right) queue.push(node->right);
			}

			//	Last node in the level shouldn't be connected
			Node* node = queue.front();
			queue.pop();
			if (node->left) queue.push(node->left);
			if (node->right) queue.push(node->right);
		}
		return root;
	}


	//	Own solution based on last problem. 
	Node* connect2(Node* node) {
		if (!node) return nullptr;

		Node* curr = node;
		Node* rightmost = curr->right ? curr->right : curr->left;


		//	Loop to initiate the connecting process across a level
		//	Only iterate when current is not null (due to loop), rightmost node is not null (Have at least 1 child
		//	node) and rightmost next is still not set (to avoid repeat when a connected node is met again)
		while (curr && rightmost && !rightmost->next) {
			if (curr->left)
				curr->left->next = curr->right;

			//	Find the next node to connect for the rightmost node of current node.
			Node* next = curr->next;

			//	Skip useless nodes which does not have any child node
			while (next && !next->left && !next->right)
				next = next->next;

			//	If a node with child node is found, it can be connected.
			if (next) {
				rightmost->next = next->left ? next->left : next->right;
				curr = next;
				rightmost = next->right ? next->right : next->left;
			}
			// Otherwise we reached at the end of level.Break out of loop
			else break;
		}

		connect(node->left);
		connect(node->right);

		return node;
	}



	//	Optimal Solution - Linked List-like solution iReferred)
	Node* connect3(Node* root) {
		Node* curr = root;

		while (curr) {
			Node d;
			Node* dummy = &d;
			Node* tail = dummy;

			while (curr) {
				if (curr->left) {
					tail->next = curr->left;
					tail = tail->next;
				}
				if (curr->right) {
					tail->next = curr->right;
					tail = tail->next;
				}
				curr = curr->next;
			}
			curr = dummy->next;
		}
		return root;
	}

};