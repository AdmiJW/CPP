#include <string>
using namespace std;

//https://leetcode.com/problems/remove-all-adjacent-duplicates-in-string/
/*
 *  This is a String - Stack problem.
 *
 *  We remove identical characters in pairs. Once removed, we need to know the
 *  top character in the string after removal. Thus, Stack data structure is best fit
 *  for this situation
 */

class Solution {
public:
	string removeDuplicates(string s) {
		string res = "";

		for (char c : s) {
			if (!res.length() || res.back() != c)
				res += c;
			else
				res.pop_back();
		}
		return res;
	}
};