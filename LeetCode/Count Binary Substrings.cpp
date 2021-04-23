#include <string>
using namespace std;

//	https://leetcode.com/problems/count-binary-substrings/
/*
 * 	This is a String, possibly two pointers problem
 *
 * 	The first intuitive for me is, if I found a pair of indices i,j which are different, they form a valid pair.
 * 	Now, if they can be expanded, when i-1,j+1 is same character as i,j, then it is forming another pair.
 *
 * 	Iterate thru the string in window size of 2, then if they are different character, attempt to expand the
 * 	window.
 *
 * 	-------------------------------
 *
 * 	The optimal solution is to remember the 0 and 1's in groups.
 * 	First of all, say we have string 000011. If we can know that it has 4 0's and 2 1's in this group, we know that
 * 	it can form 2 valid groups, of "01" and "0011".
 *
 * 	Therefore, using two pointers, we will be able to remember the start indices of two groups. Eg:
 * 		"11001100"
 *
 * 	Initially, right pointer is at index 0, indicating start of group of consecutive "1" is at index 0.
 * 	Once we hit "0" at index 2, which is different than character at right pointer, we swap pointers:
 * 		Left pointer = Right pointer		(The index for consecutive "1" is now stored)
 * 		Right pointer = current index		(To indicate group of consecutive "0" has started at current index)
 *
 * 	Once we hit index 4, we know a new group has started. Before recording start of current group, we shall evaluate
 * 	the previous recorded group before forgetting about it!
 * 		Number of "1"s is find by (right - left), 2 - 0 = 2. There are 2 '1'
 * 		Number of "0"s is find by (curr - right), 4 - 2 = 2. There are 2 '0'
 * 	Add whoever minimum to result, then continue the pointer swapping process.
 *
 * 	However, since there are no swap in the end of string, it is necessary to manually evaluate once more at the end of loop.
 */

class Solution {
public:
	//	Search for centers and expand solution
	int countBinarySubstrings(string s) {
		const int len = s.length();
		int res = 0;

		//	Search for possible centers to extend
		for (int i = 1; i < len; ++i) {
			if (s[i] != s[i-1]) {
				int l = i - 1, r = i;
				while (l >= 0 && r < len && s[l] == s[i-1] && s[r] == s[i]) {
					--l; ++r;
					++res;
				}
			}
		}
		return res;
	}


	//	Linear scan with two pointers (quite)
	int countBinarySubstrings2(string s) {
		const int len = s.length();
		int res = 0;
		int left = -1, right = 0;

		for (int i = 0; i < len; ++i) {
			if (s[right] != s[i]) {
				if (left != -1)
					res += min(right - left, i - right);
				left = right;
				right = i;
			}
		}

		//	Need to manually include the last one
		if (left != -1)
			res += min(len - right, right - left);
		return res;
	}
};