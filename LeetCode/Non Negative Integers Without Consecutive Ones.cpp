#include <vector>
using namespace std;

//https://leetcode.com/problems/non-negative-integers-without-consecutive-ones/
/*
 * 	This is an interesting Dynamic Programming Question
 *
 * 	One brute force solution is to go through from 0 to N, check if each one is valid or not. Since N goes up to 10^9,
 * 	it will simply get time limit exceeded.
 *
 * 	===============================================================
 *
 * 	A better recursive solution (accepted, but slow), is to intelligently construct valid bit strings. Imagine a recursive
 * 	solution that given a N, it will return number of valid representations available from [n, lim].
 *
 * 	It is built based on idea that in our recursion tree:
 * 		>	If current bit is a '0', then we can append a '1' or '0' to it.
 * 		>	If current bit is a '1', then we can append a '0' only to it.
 *
 * 	In our recursion, the base cases are:
 * 		>	When n provided exceeds limit
 * 		>	When the latest 2 bits (LSB) are 11 (Consecutive 1, defied the rule)
 * 	which we return 0 as there is no valid representations.
 *
 * 	Otherwise we return
 * 			1 (Itself is a valid repr) + recurse( append 1 ) + recurse( append 0 )
 *
 * 	This solution takes O(X) time where X= solution and O(32) space.
 *
 * 	================================================================
 *
 * 	Onto DP, the idea is that given M bits for us to fill, we can derive number of valid representations we can form using
 * 	the DP result from M-1 bits to fill.
 *
 * 	We'll imagine we have 2 arrays:
 * 		>	latest1[i] - At ith index, we have (i+1) bits to fill, and the leftmost bit is 1. Eg: i=3 => ( 1XX )
 * 		>	latest0[i] - At ith index, we have (i+1) bits to fill, and the leftmost bit is 0. Eg: i=3 => ( 0XX )
 *
 * 	So, to fill is quite simple:
 * 		>	On latest1[i], since latest bit is 1, next bit can only be 0. Copy value from latest0[i-1]
 * 		>	On latest0[i], latest bit is 0. We can put 0 or 1 as next bit. Put latest0[i-1] + latest1[i-1]
 *
 * 	Now the next problem is we need representations that are in the range of [0, N]! Say N = 26. We make observation:
 * 		bin(26) = 11010
 *
 * 	The idea is: From behind, whenever we encounter a '1', we encountered the same case as in latest1[i]! To ensure
 * 	the representations are in valid range, we can put the '1' as '0', then any bits to the right can be any valid combinations
 *
 * 	There are '1' bits at i={1,3,4}
 * 			11010				=> 1 case only
 * 			110[0]X				=> latest0[1]
 * 			1[0]XXX				=> latest0[3]
 * 			[0]XXXX				=> latest0[4]
 *
 * 	However, notice that the case 11010, 110[0]X are invalid because of consecutive ones. Simply validate them and the problem
 * 	is solved.
 *
 * 	Of course, you might notice that latest0[] are simply fibonacci numbers, and reduce the DP solution to use only O(1) space
 */

class Solution {
public:
	// Recursive solution
	int findIntegers(int n) {
		return recurse(1, n) + 1;			// +1 because 0 need to be accounted too
	}

	// Given a number n, will return number of representations available [n, lim]
	int recurse(int n, int lim) {
		if (n > lim || (n & 3) == 3)
			return 0;
		int sum = 1;
		sum += recurse((n * 2) + 1, lim);		// Left shift and +1
		sum += recurse(n * 2, lim);				// Left shift without +1
		return sum;
	}


	//================================================================
	// Dynamic Programming solution
	int findIntegers2(int n) {
		int latest1[32] = {};
		int latest0[32] = {};
		latest1[0] = 1;
		latest0[0] = 1;

		// Fill DP array
		for (int i = 1; i < 32; ++i) {
			latest1[i] = latest0[i - 1];
			latest0[i] = latest0[i - 1] + latest1[i - 1];
		}

		int res = checkValid(n) ? 1 : 0;
		for (int bit = 0; n > 0; ++bit, n /= 2) {
			if ((n & 1) == 1 && checkValid((n ^ 1)))
				res += latest0[bit];
		}
		return res;
	}

	// Check if a number has consecutive 1's in it
	bool checkValid(int n) {
		while (n > 0) {
			if ((n & 3) == 3) return false;
			n /= 2;
		}
		return true;
	}
};