
//=======================
//	NAME: SOH JUN WEI
//	A20EC0151
//=======================
#include <string>
using namespace std;



class MyQueue {
public:
	//	Constructor
	MyQueue(): queue(new int[_CAPACITY]), _size(0), frontIndex(0), backIndex(0) {}
	//	Destructor
	~MyQueue() {
		delete[] queue;
	}

	//	Function A - Insert Elements via push()
	void push(const int e) {
		if (_size >= _CAPACITY) throw "Unable to Push - Full capacity reached";

		queue[backIndex] = e;
		backIndex = (backIndex + 1) % _CAPACITY;
		++_size;
	}

	//	Function B - Remove Elements via poll()
	int poll() {
		if (!_size) throw "Unable to Poll - Empty Queue";
		
		--_size;
		int res = queue[frontIndex];
		frontIndex = (frontIndex + 1) % _CAPACITY;
		return res;
	}

	//	Check Size via size()
	bool isEmpty() {
		return !_size;
	}


private:
	const int _CAPACITY = 100;
	int* queue;
	int _size;
	int frontIndex;
	int backIndex;
};