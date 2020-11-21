#include <string>
#include <vector>
#include <cmath>

//https://leetcode.com/problems/numbers-at-most-n-given-digit-set/

/*
 * 	At first glance, this looks like a backtracking and permutation generating problem. Attempt every digit,
 * 	if it fits, that's one permutation. If it doesn't satisfy < n, return immediately.
 *
 * 	This solution is workable, but takes the time and space complexity of
 * 		>	Time: O(N)
 * 		>	Space: O( log10(N) )		- Since every digit we go down one level
 *
 * 	-----------------------------------------------------------------------------------------------------
 *
 * 	Instead, let's come up with something mathematical, especially COUNTING METHODS
 *
 * 	Given non-0 digits, number n and we want to find permutation of digits, say x, that are below n.
 * 	It can be seperated into 2 cases -
 * 		>	Number of digit of x is below number of digit of n
 * 		>	Number of digit of x is equal to number of digit of n
 *
 * 	In the first case, it is easy to determine. No matter what digit we choose, it will never exceed n itself.
 * 	Say we have different d digits available. Eg: [5,6,7], d = 3
 * 	Then permutations to form number of size 1: 3
 * 		 permutations to form number of size 2: 3 x 3 = 9
 * 		 permutations to form number of size 3: 3 x 3 x 3 = 27
 *
 *  Do this for every possible size from 1 to number of digit of n-1.
 *
 *
 *  Then deal with second case. We can think of it like this:
 *  	>	For the first digit, determine the number of available digits that are lesser than the first digit.
 *  		Select those lesser digits, then the rest of digit can be any of the available digits
 *
 *  		Eg: [1,2,3] n = 300.	We see first digit 3, and available digits lesser are 1 and 2. Meaning we can
 *  		select 1 or 2 as first digit. The other positions we can put whatever digit, so is 2 x 3 x 3 = 18
 *
 *  	>	Then, see if we can fix the first digit or not. In other words, see if we have the available digit same
 *  		as the first digit. If yes, fix the same digit, and it becomes essentially the same problem just with
 *  		smaller size: Determine number of digits lesser than second digit, generate permutations for it, and
 *  		try again to fix the second digit and proceed to third digit
 *
 *  	>	When trying to fix the digit, if no same digit found, immediately break the loop
 */

class Solution {
public:

	static int atMostNGivenDigitSet(std::vector<std::string>& digits, int n) {
		long v = 0l;
		int res = recurse(digits, v, n);
		return res - 1;
	}
	static int recurse(std::vector<std::string>& digits, long& val, int& n) {
		if (val > n) return 0;

		int res = 1;
		for (std::string s : digits) {
			val = val * 10l + (s[0] - '0');
			res += recurse(digits, val, n);
			val = val / 10;
		}
		return res;
	}



	static int atMostNGivenDigitSet2(std::vector<std::string> digits, int n) {
		int res = 0;
		std::string nStr = std::to_string(n);
		int* table = findCounts(digits);
		const int nDigit = nStr.length();

		for (int i = 1; i < nDigit; i++) {
			res += std::pow( digits.size(), i);
		}

		res += findEqualLengthPermutations(nStr, table);

		delete[] table;
		return res;
	}

	static int* findCounts(std::vector<std::string>& digits) {
		int* table = new int[10];
		std::fill(table, table + 10, 0);
		for (std::string s : digits) {
			table[ s[0] - '0' ] ++;
		}
		for (int i = 0; i <= 9; i++) {
			table[i] += table[i - 1];
		}
		return table;
	}
	static int findEqualLengthPermutations( std::string& nstr, int* table) {
		const int len = nstr.length();
		int res = 0;

		for (int i = 1; i <= len; i++) {
			int digit = nstr[i - 1] - '0';
			int digitOneLess = std::max(digit - 1, 0);

			res += table[digitOneLess] * std::pow(table[9], len - i);

			if (table[digit] - table[digitOneLess] == 0) break;
			if (len == i) res++;	//	The last digit is also just fit well. So add 1 to result
		}
		return res;
	}
};