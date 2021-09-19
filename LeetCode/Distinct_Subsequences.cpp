#include <string>
#include <vector>
using namespace std;

//https://leetcode.com/problems/distinct-subsequences/
/*
 * 	This is a string Dynamic Programming problem.
 *	If you never see this b4, look at DP subsequence topic.
 *
 * 	In this problem, we have to check how many ways to form string t given a longer string s by using subsequences.
 * 	Let's approach this from DP's bottom up:
 * 		If t is "rabbit", we start off by looking at ways to form "r", "ra", "rab"... until full "rabbit"
 *
 *  In each of these cases, say "rab", we would iterate through the longer string s looking for matches of the last character.
 *  In this case, we are looking for character 'b'.
 *
 *  Once we found a match at index i, we have 2 choices here:
 *  	- Use this matched character as the last character in the subproblem string "rab". If we use this 'b' at index i
 *  		as last character in "rab", then we would see HOW MANY SUBSEQUENCES CAN BE FORMED BY "ra" with string s
 *  		up to but not including this index i. Aka check upper left diagonal in DP matrix.
 *  	- Don't use this matched character at all. Then we would simply see previous number of subsequences.
 *  		(Look at left in DP matrix).
 *
 *  If the characters does not match, then our only choice would be to only see previous number (Left in DP matrix).
 *
 *
 *  Ideally, the DP matrix is of size slen+1 x tlen+1. Rows indicate string t, and cols indicate string s.
 *  dp[0] is the row where the subsequence we want to form is empty string. Then, no matter what is string s, we would
 *  have 1 way to form it. (In other words, dp[0] should be all element 1).
 *  dp[i][0] is the column where the string s supplied is empty string, therefore ways to form subsequence is always 0.
 *
 *  We don't need to actually use 2D matrix, we could optimize it to O(slen) space because we only check for diagonal
 * 	of last row and the dp element to the left.
 */

class Solution {
public:
    // 2D matrix DP solution
    int numDistinct(string s, string t) {
		const int slen = s.length();
		const int tlen = t.length();

		vector<vector<unsigned int>> dp(tlen + 1, vector<unsigned int>(slen + 1, 1));

		//DP. i is the index of string t. (Row)
		for (int i = 0; i < tlen; ++i) {
			dp[i + 1][0] = 0;
			// j is the index of string s. (Col)
			for (int j = 0; j < slen; ++j) {
				dp[i + 1][j + 1] = dp[i + 1][j];
				if (s[j] == t[i])
					dp[i + 1][j + 1] += dp[i][j];
			}
		}
		return dp[tlen][slen];
    }

	int numDistinct2(string s, string t) {
		const int slen = s.length();
		const int tlen = t.length();

		vector<unsigned int> dp(slen+1, 1);
		int diag;

		for (char c: t) {
			diag = dp[0];
			dp[0] = 0;

			for (int i = 0; i < slen; ++i) {
				int currdiag = dp[i + 1];
				dp[i + 1] = dp[i];
				if (c == s[i]) dp[i + 1] += diag;
				diag = currdiag;
			}
		}

		return dp[slen];
	}
};