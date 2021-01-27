
//https://leetcode.com/problems/concatenation-of-consecutive-binary-numbers/
/*
 * 	This is mainly a bitwise manipulation problem.
 *
 * 	From 1 to N, we have to concatenate each binary string representation together, and get the final
 * 	value modulo 10^9 + 7
 *
 * 	How can we simulate the concatenation process without creating the actual string? By using bit shifting
 *
 * 	First, we have to know the length of a particular number to know how much places to shift. This can be
 * 	done via loops, or via logarithm.
 *
 * 	Then, once the space is cleared to be able to add the current number, add it, and remember to perform
 * 	modulo so it doesn't overflow!
 */


typedef long long int LONG;

class Solution {
public:
	int concatenatedBinary(int n) {
		const int modulo = 1000000007;
		LONG res = 0;

		for (int i = 0; i <= n; ++i) {
			for (int j = i; j > 0; j >>= 1)
				res <<= 1;
			res = (res + i) % modulo;
		}
		return static_cast<int>(res);
	}
};