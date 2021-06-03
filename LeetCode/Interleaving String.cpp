#include <string>
#include <vector>
using namespace std;

//https://leetcode.com/problems/interleaving-string/
/*
 * 	This is a Dynamic Programming problem. I took a peek at the solution
 *
 * 	For brute force, we would generate all possible interweaved strings and check if it matches s3. The way we do this
 * 	is through recursion. Think of it as a tree of decisions.
 *
 * 	Every state, we have to face the choice of picking to use s1 or s2 as last character to match s3. In worst case
 * 	scenario, we will end up in decision tree taking time complexity of O(2^M+N)
 *
 * 	================================================================
 *
 * 	Instead we use DP to solve in O(MN) time. The subproblems are:
 *
 *		We will try out all possible lengths of substring of s1 and s2, and see if it can form the s3 string
 *		of length (ss1 + ss2).
 *
 * 	Eg: We have s1 = "abcde" and s2 = "fghij" and s3 = "abcdefghij".
 * 		One possible subproblem is ss1="abc" and ss2="fg". Since len(ss1+ss2) = 5, we try whether these two substrings
 * 		can be interweaved to form "abcde" in s3 (Length 5 only)
 *
 * 	At the end of such DP, we would have included entire s1, s2 and it shows whether we can form the string s3 in entirety
 * 	of length(s1+s2)!
 */


class Solution {
public:

	//	DP solution. Given substrings of s1 (ss1) and s2 (ss2) of various length, determine if s3 of len(ss1) + len(ss2)
	//	can be formed
	bool isInterleave(string s1, string s2, string s3) {
		const int len1 = s1.length(), len2 = s2.length(), len3 = s3.length();
		if (len1 + len2 != len3) return false;

		//	DP array - Across row is s1, across column is s2
		vector<vector<bool>> dp(len1 + 1, vector<bool>(len2 + 1));
		dp[0][0] = true;

		//	First row loop, where s1 doesn't even get included
		for (int i = 1; i <= len2; ++i)
			dp[0][i] = s2[i - 1] == s3[i - 1] && dp[0][i - 1];

		//	Subsequent loops
		for (int r = 1; r <= len1; ++r) {
			//	The end of substring s3, must be the (r-1)th character at s1 
			dp[r][0] = s1[r - 1] == s3[r - 1] && dp[r - 1][0];
			//	Subsequent indices
			for (int c = 1; c <= len2; ++c)
				dp[r][c] = (s1[r - 1] == s3[r + c - 1] && dp[r - 1][c]) ||
				(s2[c - 1] == s3[r + c - 1] && dp[r][c - 1]);
		}
		return dp[len1][len2];
	}


	//	Space Optimized 1D DP solution because DP only uses last row
	bool isInterleave2(string s1, string s2, string s3) {
		const int len1 = s1.length(), len2 = s2.length(), len3 = s3.length();
		if (len1 + len2 != len3) return false;

		vector<bool> dp(len2 + 1);
		dp[0] = true;

		//	First Iteration. Dependent on only s2
		for (int i = 1; i <= len2; ++i)
			dp[i] = s2[i - 1] == s3[i - 1] && dp[i - 1];
	
		//	Subsequent loops
		for (int r = 1; r <= len1; ++r) {
			//	The end of substring s3, must be the (r-1)th character at s1 
			dp[0] = s1[r - 1] == s3[r - 1] && dp[0];
			//	Subsequent indices
			for (int c = 1; c <= len2; ++c)
				dp[c] = (s1[r - 1] == s3[r + c - 1] && dp[c]) ||
				(s2[c - 1] == s3[r + c - 1] && dp[c - 1]);
		}
		return dp[len2];
	}

};