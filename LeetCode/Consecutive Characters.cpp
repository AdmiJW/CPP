

//https://leetcode.com/problems/consecutive-characters/

/*
*	A Linear scan of string problem.
* 
*	Given a non empty string, the result must always be greater than or equal to 1. 1 is minimum because any character
*	already counts.
*	Starting from second character, scan until last character. If the previous character is same as current character,
*	add 1 to power. Otherwise, reset the power.
*	After updating the power in each iteration, compare the power to the result, so that result stores the maximum power
*	met.
*/

#include <string>

class Solution {
public:
	int maxPower(std::string s) {
		if (!s.length()) return 0;
		int res = 1;
		int curr = 1;
		for (int i = 1; i < s.length(); i++) {
			curr = s[i - 1] == s[i] ? curr + 1 : 1;
			res = std::max(curr, res);
		}
		return res;
	}
};