#include <string>
#include <vector>
#include <cmath>
using namespace std;

//https://leetcode.com/problems/numbers-at-most-n-given-digit-set/

/*
 * 	At first glance, this looks like a backtracking and permutation generating problem. Attempt every digit,
 * 	if it fits, that's one permutation. If it doesn't satisfy < N, return immediately.
 *
 * 	This solution is workable, but takes the time and space complexity of
 * 		>	Time: O(N)					- If N = 10^9, then we have to iterate 10^9. Nope!
 * 		>	Space: O( log10(N) )		- Since every digit we go down one level
 *
 * 	-----------------------------------------------------------------------------------------------------
 *
 * 	Instead, let's come up with something mathematical, especially COUNTING METHODS
 *
 * 	Given non-0 digits, upper bound N and we want to find permutation of digits, say x, that are below N.
 * 	It can be seperated into 2 cases -
 * 		>	Number of digit of x is below number of digit of N
 * 		>	Number of digit of x is equal to number of digit of N
 *
 * 	In the first case, it is easy to determine. No matter what digit we choose, it will never exceed N itself.
 * 	Say we have different d digits available. Eg: [5,6,7], d = 3
 *
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
 *  		Eg: [1,2,3] n = 300. We see first digit 3, and available digits lesser are 1 and 2. Meaning we can
 *  		select 1 or 2 as first digit. The other positions we can put whatever digit, so is 2 x 3 x 3 = 18
 *
 *
 *  	>	Then, see if we can fix the first digit or not. In other words, see if we have the available digit same
 *  		as the first digit. If yes, fix the same digit, and it becomes essentially the same problem just with
 *  		smaller size: Determine number of digits lesser than second digit, generate permutations for it, and
 *  		try again to fix the second digit and proceed to third digit
 *
 *
 *  	>	When trying to fix the digit, if no same digit found, immediately break the loop
 */




class Solution {
public:

	// Recursive solution - Time limit exceeded
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



	// Mathematical approach
	int atMostNGivenDigitSet2(vector<string>& digits, int n) {
		string nstr = to_string(n);
		const int nDigit = nstr.length();
		int result = 0;

		// The array digits is of type String, I prefer it comparable, so convert to int
		vector<int> intdigits(digits.size());
		for (int i = 0; i < digits.size(); ++i)
			intdigits[i] = digits[i][0] - '0';

		// Case 1 - x is less number of digits than N.
		for (int i = 1; i < nDigit; ++i) {
			result += pow(digits.size(), i);
		}

		// Case 2 - x is equal digits with N
		for (int pos = 0; pos < nstr.length(); ++pos) {
			int i = nstr[pos] - '0';

			for (int d : intdigits) {
				if (d < i)
					result += pow(digits.size(), nstr.length() - pos - 1);
				else if (d == i) {
					// Special case - If currently is the last digit, then we can add 1 to results
					if (pos == nstr.length() - 1) ++result;
					break;
				}
				else return result;
			}
			// If even the last digit is less than current digit at pos, then we no need to proceed
			if (intdigits[intdigits.size() - 1] < i) return result;
		}

		return result;
	}
};