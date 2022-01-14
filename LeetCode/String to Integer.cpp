#include <string>
#include <cctype>
using namespace std;

//https://leetcode.com/problems/string-to-integer-atoi/
/*
 * This is a String problem, requires you to simulate the algorithm
 *
 * My algorithm goes as follows:
 *
 * 	1. Iterate to consume all the leading white spaces.
 *  2. Consume the sign if contains.
 *  3. Iterate to consume all the digits
 *  	> Add the digit to result.
 *  	> If goes out of bound of Integer range, return the respective value
 *
 *  However, this problem can also be solved using Finite State Machines, but you'll need to design it and code it out
 */


class Solution {
public:
	int myAtoi(string s) {
		const int len = s.length();
		long long int res = 0;
		char sign = ' ';
		int i = 0;

		// Consume leading spaces
		while (i < len && s[i] == ' ') ++i;

		// Consume sign (if contains)
		if (i < len && (s[i] == '+' || s[i] == '-')) sign = s[i++];

		// Consume digits. Stop if encounter non digit
		while (i < len) {
			char c = s[i];
			if (!isdigit(c)) break;

			res = res * 10 + (c - '0');

			if (sign == '-' && -res <= INT32_MIN) return INT32_MIN;
			if (sign != '-' && res >= INT32_MAX) return INT32_MAX;

			++i;
		}

		if (sign == '-') res = -res;
		return (int)res;
	}
};