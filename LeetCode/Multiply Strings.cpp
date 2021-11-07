#include <string>
#include <vector>
#include <algorithm>
using namespace std;

//https://leetcode.com/problems/multiply-strings/
/*
 * This is a String, simulation problem.
 *
 * In my solution, I implemented a stringAdd and stringMult function, which does two things:
 * 	stringAdd - Add two strings representing an integer together. Additionally, offset can be provided to pad zeroes
 * 				to num2.
 *
 * 				Eg: num1 = 123, num2 = 456, offset = 2
 * 				=> 123 + 45600
 * 				=> 45723
 *
 * 	stringMult - Multiplies num1 with provided digit. Only 0 <= digit <= 9
 * 				Eg: num = 123, digit = 3
 * 				=>	369
 *
 * 	Using these two functions, I can very well perform multiplications. Additionally, since given a fixed num1, I can
 * 	only have 10 ways of calling stringMult, so I can cache the result of stringMult immediately from the start.
 *
 * 	Time complexity is O(M*N), because stringAdd is going to be called N times, each require to process at most M digits
 *
 *
 *  However, my solution is not the best. See leetcode's discussion panel for most shortest solution you ever seen
 */

class Solution {
public:
	string multiply(string num1, string num2) {
		if (num1 == "0" || num2 == "0") return "0";

		// 1 - Generate all possible multiplications of num1 with a single digit
		string mult[10];
		for (int i = 0; i < 10; ++i)
			mult[i] = stringMult(num1, i);

		// 2 - For each digit in num2, obtain the multiplication value and add to result
		string res = "0";
		for (int i = 0; i < num2.length(); ++i) {
			res = stringAdd(res, mult[num2[num2.length() - i - 1] - '0'], i);
		}

		return res;
	}


	// Multiplies string a with a single digit represented by digit
	string stringMult(string a, int digit) {
		if (digit == 0) return "0";

		string sb = "";
		int carry = 0;

		for (int i = a.length() - 1; i >= 0; --i) {
			int res = (a[i] - '0') * digit + carry;
			carry = res / 10;
			res %= 10;
			sb += (char)(res + '0');
		}

		if (carry != 0) sb += (char)(carry + '0');

		reverse(sb.begin(), sb.end());
		return sb;
	}


	// Adds string a and b together, where b is offsetted by offset amount from right, padded with zeroes.
	string stringAdd(string a, string b, int offset) {
		string sb = "";

		// 1 - Initialize sb with b, but with offset included
		for (int i = 0; i < b.length(); ++i)
			sb += b[i];
		for (int i = 0; i < offset; ++i)
			sb += '0';

		b = sb;
		sb = "";


		// 2 - Add the two numbers together
		int carry = 0;
		for (int i = 0; i < max(a.length(), b.length()) || carry != 0; ++i) {
			int sum = (
				(i < a.length() ? (a[a.length() - 1 - i] - '0') : 0) +
				(i < b.length() ? (b[b.length() - 1 - i] - '0') : 0) +
				carry
				);

			carry = sum / 10;
			sum %= 10;
			sb += (char)(sum + '0');
		}

		reverse(sb.begin(), sb.end());
		return sb;
	}
};