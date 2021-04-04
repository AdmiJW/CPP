#include <vector>
using namespace std;

//https://leetcode.com/problems/design-circular-queue/
/*
 * 	This is a design data structure problem - For queue
 *
 * 	If the two pointers - front and rear of the queue runs out of space after use, then the
 * 	queue is not so efficient. say I have a queue of size 5, I push 5 elements, and pop 5 elements.
 * 	Then the queue should be reusable with 5 space left!
 *
 * 	This type of queue is efficient, and is called "Ring Buffer", where last position of the queue is
 * 	essentially connected back to the first position in the queue.
 *
 * 	Turns out, it is easily done via two pointers and a modulus operation. Say my queue is of size 5,
 * 	and the rear pointer is now at index 4 (last position). If I want to enqueue some elements, the
 * 	next index to work on is actually just (i+1) % 5, where 5 is the capacity of the queue. WIth this,
 * 	I get back index 0, which is start of queue! (Just check if the queue is full or not so we don't
 * 	overwrite useful data).
 */

//	Uses a bit of iterator instead of integer values as pointer
class MyCircularQueue {
private:
	int capacity;
	int size;
	vector<int> queue;
	vector<int>::iterator front, rear;
public:
	MyCircularQueue(int k): capacity(k), size(0), queue(vector<int>(k,0)) {
		front = queue.begin();
		rear = queue.end() - 1;
	}

	bool enQueue(int value) {
		if (size == capacity) return false;

		rear = (rear + 1 == queue.end()) ? queue.begin() : rear + 1;
		++size;
		*rear = value;
		return true;
	}

	bool deQueue() {
		if (!size) return false;

		front = (front + 1 == queue.end()) ? queue.begin() : front + 1;
		--size;
		return true;
	}


	int Front() {
		if (!size) return -1;
		return *front;
	}

	int Rear() {
		if (!size) return -1;
		return *rear;
	}

	bool isEmpty() {
		return !size;
	}

	bool isFull() {
		return size == capacity;
	}
};