
//https://leetcode.com/problems/design-hashmap/
/*
 * 	A HashMap is simply an array, but to access an element, we use what is called as 'keys', which
 * 	must be hashable, like Strings (in Java, every object is hashable).
 *
 * 	Now, A HashMap has an array of fixed size to store elements, as well as a hashing function, which
 * 	maps keys to the indices of the array. With that, all elements can be accessed in approximated O(1)
 * 	time!
 *
 * 	Collision may happen, where 2 different keys will be hashed into the very same index. In that case,
 * 	a collision is said to be happened, and it has to be resolved.
 * 	One of such way to resolve, is to use Linkedlist. Instead of storing one element in each index, it
 * 	stores linked list, so when collision happens, it will only add elements to the linked list. of course,
 * 	the data structure should be optimized to have collision occur as little as possible.
 */

class MyHashMap {
public:
	MyHashMap() : MyHashMap(1000) {}
	MyHashMap(int capacity) : capacity(capacity) {
		this->arr = new ListNode * [capacity] {};
		// cout << (arr[0]? "Yes" : "No");
		// cout << "Done";
	}


	void put(int key, int value) {
		int idx = getIndex(key);

		if (arr[idx]) {
			ListNode* res = search(arr[idx], key);

			//	If search is null, means the head of linked list is the actual node
			if (!res) arr[idx]->val = value;
			//	If result value is not same key, means not found!
			else if (!res->next) res->next = new ListNode(key, value);
			//	Found the result
			else res->next->val = value;
		}
		else arr[idx] = new ListNode(key, value);
	}

	int get(int key) {
		int idx = getIndex(key);
		if (!arr[idx]) return -1;

		ListNode* res = search(arr[idx], key);
		//	Head of linked list is result
		if (!res) return arr[idx]->val;
		//	If next is null means not found. Otherwise next node is the result
		return res->next ? res->next->val : -1;
	}

	void remove(int key) {
		int idx = getIndex(key);
		if (!arr[idx]) return;

		ListNode* res = search(arr[idx], key);
		//	Head of linked list is result
		if (!res) arr[idx] = arr[idx]->next;
		//	No result found: Do nothing
		else if (!res->next) return;
		//	Skip the node to delete it
		else {
			ListNode* toDel = res->next;
			res->next = res->next->next;
			delete toDel;
		}
	}

private:
	class ListNode {
	public:
		ListNode* next;
		int key, val;
		ListNode(int key, int val) : key(key), val(val), next(nullptr) {}
	};
	int capacity;
	ListNode** arr;


	//	Private Utilities functions
	int getIndex(int key) {
		return key % this->capacity;
	}

	//	Search and returns the ListNode in a linked list. It returns the previous node prior
	//	to the actual node itself. If result is at start of list, returns null. If result is
	//	not found, returns the tail of list, where next node is null
	ListNode* search(ListNode* head, int key) {
		if (head->key == key) return nullptr;
		while (head->next && head->next->key != key)
			head = head->next;
		return head;
	}
};