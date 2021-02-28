#include <array>
#include <stack>
#include <unordered_map>
#include <queue>
using namespace std;

//https://leetcode.com/problems/maximum-frequency-stack/
/*
 * 	This is a HashMap, Heap / Stack problem.
 *
 * 	The first solution is, we have to sort the values, so that when we pop, the correct element returns.
 * 	Immediately, the Heap Data structure comes to mind.
 *
 * 	We'll have a frequency table that maps values -> current frequency in the virtual stack. The frequency of
 * 	a value increments when pushed, and decrements everytime it is selected to be popped.
 *
 * 	Next, have a heap that stores tuples of 3 values - (value, index, frequency). The heap is going to sort primarily
 * 	by the frequency of the value at that time
 * 	**No need to update all previous values, they keep their state**
 * 	Only if the frequency are same, the sorting fall back to sort by index
 *
 * 	Time commplexity for both push and pop is approximately O(log N). Space is O(N) as it scales linearly with the input
 *
 * 	----------------------------------------------------------------------------
 *
 * 	Notice that we are sorting by frequency. Only when frequency ties with another, we fall back to their insertion Stack
 * 	order. Can't we use the property of Stack in any way? Yes we do.
 *
 * 	Keep a Map of Stacks. The Map will map from (frequencies)->(Stack), and the stack will keep the values in their insertion
 * 	order.
 *
 * 	Have a example: (Credit to leetcode user - softwareshortcut)
 *
 * 	// Stack Trace
	// push(5) - { [key:1, value: Stack<5>] }
	// push(7) - { [key:1, value: Stack<5,7>] }
	// push(5) - { [key:1, value: Stack<5,7>], [key:2, value: Stack<5>] }
	// push(7) - { [key:1, value: Stack<5,7>], [key:2, value: Stack<5,7>] }
	// push(4) - { [key:1, value: Stack<5,7,4>], [key:2, value: Stack<5,7>] }
	// push(5) - { [key:1, value: Stack<5,7,4>], [key:2, value: Stack<5,7>], [key:3, value: Stack<5,7>] }
	// pop()   - { [key:1, value: Stack<5,7,4>], [key:2, value: Stack<5,7>] } -> 5
	// pop()   - { [key:1, value: Stack<5,7,4>], [key:2, value: Stack<5>] } -> 7
	// pop()   - { [key:1, value: Stack<5,7,4>] } -> 5
	// pop()   - { [key:1, value: Stack<5,7>] } -> 4
 *
 * 	Since we are using Map for implementation, we need to keep track of the highest level for popping purposes. Also, we need
 * 	a frequency table for pushing purpose as well.
 *
 *	We are using Stack, so popping and pushing are both time complexity of O(1). Space is also O(N) since it scales linearly
 *	with the number of input
 */

class HeapComparator {
public:
	bool operator()(const array<int, 3>& lhs, const array<int, 3>& rhs) const {
		if (lhs[2] == rhs[2]) return rhs[1] > lhs[1];
		return rhs[2] > lhs[2];
	}
};


class FreqStack {
public:
	FreqStack() : index(0) {}

	void push(int x) {
		int f = freq[x] + 1;
		heap.push({ x, index++, f });
		freq[x] = f;
	}

	int pop() {
		auto popped = heap.top(); heap.pop();
		--freq[popped[0]];
		return popped[0];
	}

private:
	unordered_map<int, int> freq;
	priority_queue<array<int, 3>, vector<array<int, 3>>, HeapComparator> heap;
	int index;
};





class FreqStack2 {
public:
	FreqStack2() : height(0) {}

	void push(int x) {
		int f = freq[x] + 1;
		++freq[x];
		stacks[f].push(x);
		height = max(height, f);
	}

	int pop() {
		if (stacks[height].empty()) --height;
		int pop = stacks[height].top();
		stacks[height].pop();
		--freq[pop];
		return pop;
	}

private:
	unordered_map<int, int> freq;
	unordered_map<int, stack<int>> stacks;
	int height;
};