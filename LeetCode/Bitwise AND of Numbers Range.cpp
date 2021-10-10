using namespace std;

//https://leetcode.com/problems/bitwise-and-of-numbers-range/
/*
 * This is a bit manipulation problem. My idea is as follows:
 *
 * Iterating from [left, right] is going to result in TLE because of potential 2^31 iterations. Instead, we view
 * from binary form: They are just 31 bits of 0 and 1.
 *
 * My idea is, we have 31 bit positions, and if we AND everything in [left, right], say we have a number x which is in
 * range left < x < right, if it is bit 0 at index i, then surely the result will always be 0 in that bit position.
 *
 * Therefore I will check to see whether there is an integer which is in range [left,right] and at index i of binary
 * representation, it is bit 0 or not. If it does, I am sure that the result will have bit 0 in that index as well.
 *
 * In my algo, start out with the res = left & right. Then, iterate 31 times for each of the bit position. We'll try
 * to see if there is an integer which is bit 0 in the index i and is in range [left, right].
 */

class Solution {
public:

    int rangeBitwiseAnd(int left, int right) {
		int res = left & right;
		long long int curr = left;

		// Attempt all the bit positions up to bit 31;
		for (int i = 0; i < 31; ++i) {
			// Left position itself is already zero and previously ANDed with res.
			if (!(curr & (1 << i))) continue;
			// Otherwise we try to make the bit become zero and see if it is in range or not
			// Adding with bit 1 at that position will result in LEAST next greater integer with 0 at that bit.
			curr += (1 << i);
			if (curr > right) break;

			res &= curr;
		}
		return res;
    }

};