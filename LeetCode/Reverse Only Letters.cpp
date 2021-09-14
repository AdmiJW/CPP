#include <string>
using namespace std;

//https://leetcode.com/problems/reverse-only-letters/
/*
 * This is a String, Two pointer problem.
 *
 * Reversing a string is like swapping the characters at the front & back. Once a swap is done, we move forward
 * the left pointer and move backward the right pointer and repeat.
 *
 * Now, if we have non-alphabetic characters, we will simply proceed the said pointer without swapping.
 */

class Solution {
public:
	string reverseOnlyLetters(string s) {
		string res = s;
		int l = 0, r = s.length() - 1;
		while (l < r) {
			if (!isAlphabetic(res[l])) ++l;
			else if (!isAlphabetic(res[r])) --r;
			else {
				char t = res[l];
				res[l] = res[r];
				res[r] = t;
				++l; --r;
			}
		}
		return res;
	}

	bool isAlphabetic(char c) {
		return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
	}
};