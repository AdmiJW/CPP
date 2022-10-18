#include <string>
using namespace std;

//https://leetcode.com/problems/count-and-say/
/*
 * 	This is a recursion problem.
 *
 * 	First, to parse a digit string into (count + digit) form, simply run a linear scan and keep
 * 	track of the count of the current running digit. Once the digit changes, append the (count + digit)
 * 	into the result string and reset the counter.
 *
 * 	For a function call to countAndSay(n), we have to get the string first from countAndSay(n-1), which
 * 	base case is when n=1
 *
 * 	Of course, recursion is entirely optional as you can simply use a loop and start from n=1 to n
 */


class Solution {
public:
	string countAndSay(int n) {
		if (n == 1) return "1";

		string str = countAndSay(n - 1);
		return getString(str);
	}


	string getString(string& s) {
		int curr = s[0] - '0';
		int count = 0;
		string sb = "";

		for (char c : s) {
			int d = c - '0';

			if (d != curr) {
				sb += to_string(count);
				sb += to_string(curr);
				curr = d;
				count = 1;
			}
			else ++count;
		}
		sb += to_string(count);
		sb += to_string(curr);
		return sb;
	}
};