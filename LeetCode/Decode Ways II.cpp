#include <vector>
#include <string>
using namespace std;

typedef long long int LONG;

//https://leetcode.com/problems/decode-ways-ii/
/*
 * This is a Dynamic Programming problem.
 *
 * Prepare a DP array where dp[i] records the number of ways available to decode from string s until ith index.
 *
 * Every digit can be decoded alone, or perhaps it can pair with the previous digit together to be decoded.
 * Let's see:
 *
 * 	If current is '0'
 * 	>	It must be paired with '1' or '2'. The number of decodes are now dp[i-2]
 * 	>	It can be paired with '*'. The number of decodes are dp[i-2] * 2, since * can be '1' or '2'
 *
 * 	If current is '1' to '6'
 * 	> 	It can be decoded alone. it gives dp[i-1] possibilities.
 *  >	It can be paired with '1' or '2'. It gives dp[i-2] possibilities
 *  >	It can be paired with '*'. It gives dp[i-2] * 2 possibilities
 *
 *  If current is '7' to '9'
 *  >	It can be decoded alone. It gives dp[i-1] possibilities
 *  >	It can be paired with '1' or '*'. Giving dp[i-2] possibilities
 *
 *  If current is '*',
 *  >	It can be decoded alone, giving dp[i-1] * 9 possibilities
 *  >	It can be paired with '1', giving dp[i-2] * 9 possibilities
 *  >	It can be paired with '2', giving dp[i-2] * 6 possibilities
 *  >	It can be paired with '*', giving dp[i-2] * 15 possibilities (11,12,13,14...19,21,22...26)
 *
 *  Of course, since you can see it always use dp[i-1] and dp[i-2] only, we can optimize to use only O(1) extra space
 */

class Solution {
public:
	int numDecodings(string s) {
		const int MOD = 1000000007;
		const int len = s.length();
		vector<LONG> dp(len + 1, 0);
		dp[0] = 1;
		char prev = ' ';

		for (int i = 0; i < len; ++i) {
			char c = s[i];
			//	If 0, it cannot form by itself, must use preceding '1' or '2' or '*'
			if (c == '0') {
				// Invalid string
				if (prev != '1' && prev != '2' && prev != '*')
					return 0;
				dp[i + 1] = prev == '*' ? dp[i - 1] * 2 % MOD : dp[i - 1];	// Only one way to decode '10' or '20' (Unless *0). Remains same 			   
			}
			// From '1' to '6', it can form by itself, or prefix by '1' or '2' or '*'
			else if ('1' <= c && c <= '6') {
				long res = dp[i];	// Form by itself
				if (prev == '1' || prev == '2' || prev == '*')
					res += prev == '*' ? dp[i - 1] * 2 % MOD : dp[i - 1];		//Form by pairing with '1' or '2' or '*'
				dp[i + 1] = res;
			}
			// From '7' to '9', it can form by itself or prefix by '1' or '*' only
			else if ('7' <= c && c <= '9') {
				long res = dp[i];	// Form by itself
				if (prev == '1' || prev == '*')
					res += dp[i - 1];		// Form by pairing with '1' or '*'
				dp[i + 1] = res % MOD;
			}
			// Else, a '*' can form by itself (9 ways), or prefix with '1' (9 ways), '2' (6 ways) or even '*' (15 ways)
			else {
				long res = dp[i] * 9;		// Form by itself
				if (prev == '1')
					res += dp[i - 1] * 9;
				else if (prev == '2')
					res += dp[i - 1] * 6;
				else if (prev == '*')
					res += dp[i - 1] * 15;
				dp[i + 1] = res % MOD;
			}

			prev = c;
		}

		return (int)dp[len];
	}
};