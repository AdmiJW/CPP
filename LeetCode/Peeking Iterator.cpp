#include <vector>
using namespace std;

//https://leetcode.com/problems/peeking-iterator/
/*
 *	 A Design Question.
 *
 *	Constructor - Initialize the hold variable, which holds the value to be returned on the next() call
 *				  Also store the iterator itself
 *
 *	peek() - Returns the hold variable without changing anything
 *	next() - Returns the value in hold variable. Also updates the hold variable with next available value
 *			 from original iterator
 *	hasNext() - Check if there is a valid value in the hold variable
 */

class Iterator {
public:
	struct Data;
	Data* data;
	Iterator(const vector<int>& nums);
	Iterator(const Iterator& iter);

	virtual int next() = 0;
	virtual bool hasNext() const = 0;
};


//	Works with only Integer
class PeekingIterator : public Iterator {
private:
	int hold = INT32_MIN;
public:
	PeekingIterator(const vector<int>& nums) : Iterator(nums) {
		hold = Iterator::hasNext() ? Iterator::next() : INT32_MIN;
	}

	int peek() {
		return hold;
	}

	int next() {
		int temp = hold;
		hold = Iterator::hasNext() ? Iterator::next() : INT32_MIN;
		return temp;
	}

	bool hasNext() const {
		return hold != INT32_MIN;
	}
};



//	Works with templates
//	However, this way the Iterator.next() must return a pointer
template <typename T>
class PeekingIterator2 : public Iterator {
private:
	const T* hold;
public:
	PeekingIterator2(const vector<T>& nums) : Iterator(nums) {
		hold = Iterator::hasNext() ? Iterator::next() : nullptr;		//	Iterator::next() if not return pointer, will be error
	}

	T peek() {
		return *hold;
	}

	T next() {
		T* temp = hold;
		hold = Iterator::hasNext() ? Iterator::next() : nullptr;
		return *temp;
	}

	bool hasNext() const {
		return hold != nullptr;
	}
};