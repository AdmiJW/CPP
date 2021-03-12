#include <string>
#include <unordered_set>
using namespace std;

//https://leetcode.com/problems/check-if-a-string-contains-all-binary-codes-of-size-k/
/*
 * 	This is a HashSet, Bit Manipulation problem
 *
 * 	We have to check if all permutations of the bit string of size k exists as substring in string s.
 * 	By thinking, the total number of permutations will be 2^k in size. Also, since the size is always
 * 	fixed, we can run a sliding window (some call it rolling hash technique) to update the bit string
 * 	in our window.
 *
 * 	Say k is 5 and current window is 10101. The next bit is 1. We will be left shifting the window by
 * 	1 time, so it becomes 101010. Now for the LSB, since last bit is 1, we add 1 so LSB becomes 1 as well.
 * 	Now, discard the MSB. THis can be done via AND operation with a mask of all 1.
 * 	The mask would be 11111, which is easily obtained by 100000 - 1 = (1 << 5) - 1
 *
 * 	Since there are 2^k total permutations, we can ignore the individual values, and record them in a
 * 	HashSet. At the end, simply check if the HashSet size is 2^k.
 *
 * 	Instead of Hashset, one can also use a boolean array and a count down counter for improved performance
 * 	due to lower level of abstraction.
 */

class Solution {
public:
	bool hasAllCodes(string s, int k) {
		//	Impossible case
		if (k > s.length()) return false;

		unordered_set<int> vals;
		int supposed = 1 << k;
		int mask = supposed - 1;

		int val = 0;
		//	Window Initialization
		for (int i = 0; i < k; ++i) val = (val << 1) + (s[i] - '0');
		vals.insert(val);

		//	Iteration
		for (int i = k; i < s.length(); ++i) {
			val = (val << 1) + (s[i] - '0');
			val &= mask;
			vals.insert(val);
		}

		return vals.size() == supposed;
	}
};