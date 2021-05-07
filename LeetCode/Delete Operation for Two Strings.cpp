#include <string>
#include <vector>
using namespace std;

//https://leetcode.com/problems/delete-operation-for-two-strings/
/*
 * 	This is a Dynamic Programming - Longest Increasing Subsequence (LIS) problem
 *
 * 	Given two strings, you only need to find THE MINIMUM AMOUNT OF CHARACTER TO DELETE TO MAKE THEM EQUAL.
 * 	If you think carefully, before deletion, you will naturally find out the best strategy to delete, which
 * 	is to keep the LONGEST INCREASING SUBSEQUENCE OF THEM!
 *
 * 	Eg: 'abcdefgh' and 'acegz'.
 * 	In this case, 'aceg' turns out to be the LIS of both strings.
 *
 * 	I won't explain LIS here, for reference, you can go to Topics > Algorithms > Largest Common Subsequence
 *
 * 	Once found, do some math:
 * 		>	At the end, both string's length are the result from LIS. In example case above, it's 4.
 * 		>	Therefore, how many characters you have to delete to reduce to both strings be length 4?
 *
 * 			len1 + len2 - 2 * LISresult
 *
 * 	-------------------------------------------------
 *
 * 	However, a solution without LIS also exists, although it does not run from DP.
 * 	The idea is that the dp grids store the minimum deletions required to reduce both strings to be same instead.
 */

class Solution {
public:
	//	Longest Increasing Subsequence tabulation method (no optimization)
	int minDistance(string word1, string word2) {
		const int len1 = word1.size(), len2 = word2.size();
		vector<vector<int>> dp(len1 + 1, vector<int>(len2 + 1, 0));
		int maximum = 0;

		for (int i = 0; i < len1; ++i) {
			char c = word1[i];
			for (int j = 0; j < len2; ++j) {
				if (c == word2[j]) {
					dp[i + 1][j + 1] = dp[i][j] + 1;
					maximum = max(maximum, dp[i + 1][j + 1]);
				}
				else
					dp[i + 1][j + 1] = max(dp[i][j + 1], dp[i + 1][j]);
			}
		}
		return len1 + len2 - maximum * 2;
	}


	//	Space optimized LIS O(N) space
	int minDistance2(string word1, string word2) {
		const int len1 = word1.size(), len2 = word2.size();
		vector<int> dp(len2 + 1, 0);
		int maximum = 0;

		for (int i = 0; i < len1; ++i) {
			char c = word1[i];
			int prevdiag = 0;
			for (int j = 0; j < len2; ++j) {
				int diag = dp[j + 1];
				if (c == word2[j]) {
					dp[j + 1] = prevdiag + 1;
					maximum = max(maximum, dp[j+1]);
				}
				else dp[j+1] = max(dp[j + 1], dp[j]);
				prevdiag = diag;
			}
		}
		return len1 + len2 - maximum * 2;
	}
};