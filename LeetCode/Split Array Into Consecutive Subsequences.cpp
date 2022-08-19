#include <unordered_map>
#include <queue>
#include <vector>
using namespace std;


//https://leetcode.com/problems/split-array-into-consecutive-subsequences/
/*
 * 	This is a HashMap, Greedy problem
 *
 * 	One solution is to simulate the behavior of the problem. For each element e, we can either extend an existing
 * 	subsequence [..., e], or start a new subsequence of length 1 consisting of only e itself [e].
 *
 * 	This is the greedy behavior of the problem. We try to extend existing subsequence first, then only if we have no
 * 	choice, we create a new subsequence.
 *
 * 	At the end, check if all existing subsequences are greater than 3.
 *
 *  Therefore, we could use a HashMap, where table[i] maps to a collection of sequences that ends with element i.
 *  If we were to extend an existing subsequence, we would greedily want to extend the shortest one. Therefore,
 *  table[i] should be a Heap storing the length of subsequences, where when we peek() or poll(), will return the
 *  shortest subsequence available to extend.
 *
 *  ============================================================
 *
 *  A more optimal solution is to extend the above idea. For each element e:
 *
 *  	1. If e can extend an existing subsequence, then use it to extend.
 *  	2. Else, e should be able to start a new subsequence of at least length 3: [e, e+1, e+2]
 *  	3. Otherwise, e is left alone and thus the problem fails.
 *
 *  Due to case (2) where we have to know if e+1 and e+2 is available, we have to initialize a frequency table,
 *  vacant[i] that maps to number of element i that are not used in forming subsequences yet.
 *
 *  The rest would be to just implement the above logic. This time, Time/space complexity is reduced to O(N),
 *  and allows for early return once an element e is detected cannot be used in forming subsequences.
 */


class Solution {
public:


	// HashMap + PriorityQueue solution. Slow.
	bool isPossible(vector<int>& nums) {
		// Stores existing sequences in HashTable by last element
		// Each HashTable entry stores collection of sequences (as length only) in ascending order
		unordered_map<int, priority_queue<int, vector<int>, greater<int>>> table;

		// I use a counter to count number of subsequences that below length 3
		int counter = 0;

		for (int i : nums) {
			// Can extend an existing subsequence
			if (table.count(i - 1) && !table[i - 1].empty()) {
				int prevLen = table[i - 1].top();
				table[i - 1].pop();
				table[i].push(prevLen + 1);

				if (prevLen + 1 == 3) --counter;
			}
			// Cannot extend. Start a new subsequence
			else {
				table[i].push(1);
				++counter;
			}
		}

		return counter == 0;
	}



	// O(N) HashMap solution
	bool isPossible2(vector<int>& nums) {
		// vacant[i] maps to number of i that we haven't used up
		unordered_map<int, int> vacant;
		// seq[i] maps to number of subsequences that end with i
		unordered_map<int, int> seq;

		// Add all numbers to vacant first
		for (int i : nums) ++vacant[i];

		// Iterate again. All element must either:
		//		1. Extend one of previous existing subsequences. (Priority)
		//		2. Start a new subsequence of at least length 3
		// If both cases cannot be satisfy, then immediately return false
		for (int i : nums) {
			// Check if current i already used up by subsequences
			if ( !vacant[i] ) continue;
			--vacant[i];

			// Case 1
			if ( seq[i - 1] > 0 ) {
				++seq[i];
				--seq[i - 1];
			}
			// Case 2
			else if (vacant[i+1] > 0 && vacant[i+2] > 0) {
				--vacant[i + 1];
				--vacant[i + 2];
				++seq[i + 2];
			}
			else return false;
		}

		// Successfully used all elements in sequence of length 3 or more.
		return true;
	}
};