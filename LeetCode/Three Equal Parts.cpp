#include <vector>
using namespace std;

//https://leetcode.com/problems/three-equal-parts/
/*
 * 	This is a Math, array problem. No fancy algorithm, just the idea is HARD to come up with (At least, I can't)
 *
 * 	In a binary representation, the leading 0 is insignificant. What's significant is the bits INCLUDING and AFTER the
 * 	first '1'. See:
 * 		0001010101
 * 	The important part is only the '0001010101'.
 *
 * 	Now, given an binary string, if we need to partition into 3 equal parts where value is same, the idea is:
 * 		THE "IMPORTANT PART" OF THREE PARTITIONS MUST BE SAME!
 *
 * 	Therefore, first we count the number of 1s in the string. If the count is indeed divisible by 3, then only we consider
 * 	if it is partitionable or not.
 * 	To check, we easily obtain the "IMPORTANT PART", by taking the strings from backwards, until we included count/3 '1' in them.
 * 	For example,
 * 			10101
 * 	Count = 3, and count/3 = 1.
 * 	From backwards, the substring "1" already contains one '1' bit in it. That's our "Important part", whether or not the final
 * 	partition is "01" or "1" does not matter first.
 *
 * 	Then, we try to check if the first partition is formable or not. Ignore the leading zeroes. Then, using two pointers technique
 * 	compare whether "important part" of partition 1 and partition 3 is same.
 * 	The same process goes for partition 2.
 *
 * 	Finally, if it passed all test where important part does equal, we already have the pointers to the end of first and second partition.
 */

class Solution {
public:
	vector<int> threeEqualParts(vector<int>& arr) {
		const int len = arr.size();
		//Obtain sum of 1's in the array
		int count1s = 0;
		for (int i: arr) count1s += i;
		
		// Impossible case - Early termination
		if (count1s % 3 != 0) return {-1, -1};
		if (count1s == 0) return {0,2};				// All 0, simply form the range
		count1s /= 3;
		
		int range1, range2, range3;
		// First step: From right to left, get n/3 included
		// This is not the final answer for the third subarray, as it may have padding zeroes. It simply defines the pattern that all three subarray have, ignoring leading 0s
		for (range3 = len-1; count1s != 0; --range3)
			count1s -= arr[range3];
		
		// Second step: From left to right, obtain the pattern defined by the range3, ignoring the padding zeroes.
		for (range1 = 0; arr[range1] == 0; ++range1) {}							// Ignore the padding zeroes
		
		for (int pointer = range3+1; pointer < len; ++pointer, ++range1)		// Now we check, both pointer shall always be equal to have three equal binaries
			if (arr[pointer] != arr[range1]) return {-1, -1};			// Mismatch
		
		
		// Third step: Ignore padding zeroes, then compare the leftover range as well.
		for (range2 = range1; arr[range2] == 0; ++range2) {}					// Ignore the padding zeroes
		
		for (int pointer = range3+1; pointer < len; ++pointer, ++range2)		// Now we check, both pointer shall always be equal to have three equal binaries
				if (arr[pointer] != arr[range2]) return {-1, -1};		// Mismatch
		
		return { range1 -1, range2 };
	}
};