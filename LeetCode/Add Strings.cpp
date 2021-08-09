#include <string>
using namespace std;


//https://leetcode.com/problems/add-strings/
/*
 *	This is a string problem.
 *
 *	We simulate the addition: From behind, we add the digits, and take only the last digit (if >= 10). The carry need to be
 *	evaluated for the next iteration, based on condition (sum >= 10).
 *
 *	Don't forget after the iteration, that if carry is true, add the last '1'.
 *
 *	Reverse the result because we add digits left to right.
 */

class Solution {
public:
	string addStrings(string num1, string num2) {
		const int l1 = num1.length();
		const int l2 = num2.length();
		string res = "";
		bool carry = false;

		for (int i1 = l1 - 1, i2 = l2 - 1; (i1 >= 0 || i2 >= 0); --i1, --i2) {
			char c1 = (i1 >= 0) ? num1[i1] : '0';
			char c2 = (i2 >= 0) ? num2[i2] : '0';

			int digit = c1 + c2 - '0' - '0' + (carry ? 1 : 0);
			carry = digit >= 10;
			res += (digit % 10) + '0';
		}

		// Don't forget if there is last carry, like '5' + '5'
		if (carry) res += '1';
		reverse(res.begin(), res.end());
		return res;
	}
};