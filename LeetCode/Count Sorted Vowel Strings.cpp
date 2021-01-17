//https://leetcode.com/problems/count-sorted-vowel-strings/
/*
 *	This is a Backtracking / Dynamic Programming Problem
 *
 * 	We want to build out a lexicographically sorted string consisting of only vowels.
 * 	Initially, we could choose a,e,i,o,u. The choice that we make will limit our next
 *	character's choice.
 *
 *	Therefore since the problem involves selecting between choices, it can be solved via
 *	backtracking,
 *
 *	Every state, attempt to select one character, recurse deeper, then when the result
 *	is obtained, attempt the next character. The return value of each choice indicates the
 *	number of ways to form the said vowel string if we choose the character.
 *
 *	Again, the base case is when the string exceeds size n. This means a vowel string is formed,
 *	therefore we could return 1 - Indicating 1 vowel string is formed.
 *
 *	--------------------------------------------------------------
 *
 *	There are many repeated computations when using the backtracking method. Say,
 *
 *	If we select 'a' as first character, at some point we will need to find out the number of
 *	strings that can be formed by selecting 'i' as second character.
 *	If we select 'e' as first characer, we also have to find out the number of strings that can
 *	be formed by selecting 'i' as second character! Repeated!
 *
 *	If we have recorded the number of ways, that calculation can be retrieved in O(1) time!
 *
 *	So we can have a 2D array recording the number of ways where a string can be formed.
 *		>	The row indicates the length of string
 *		>	The col indicates the choice of character. Col (1) - 'u', col (2) - 'o', col(3) - 'i'...
 *			col 0 is preserved to make the algorithm more generalized, and should only have value 0
 *
 *	Each grid of the DP array should show the ways to form string of length n, given that the first character
 *	is fixed, or can be below.
 *	Say, since col 4 represents 'e' and col 5 represents 'a', the value in col 5 shall store the ways if i
 *	select 'a', or 'e', 'i', 'o' and 'u' as the character.
 *
 *	Thus the DP will start from length 1 until length N, and each grid, we will need to find:
 *		>	If I select the character STRICTLY less than current col representation, then I find out by
 *			visiting the same row, but previous column
 *		>	If I STRICTLY select the same character as current col representation, then I find out by visiting
 *			the previous row, same column
 *
 *	----------------------------------------------------------
 *
 *	Remember your discrete mathematics class?
 *
 *	{ a, e, i, o, u }
 *
 *	From 5, choose 2 characters. Combinations with repeatitions allowed. ::
 *	{ aa, ae, ai, ao, au, ee, ei, eo, eu, ii, io, iu, oo, ou, uu }
 *	You can see, the possible combinations are selected in such a way that they are all lexicographically sorted!
 *
 *	Therefore apply the combinations with repititons formula and we are done!
 *
 *	The combinations formula can be simplified to follows:
 *
 *		(4+n)(3+n)(2+n)(1+n) / 4!
 */

class Solution {
public:
	
	//	Recursive solution of backtracking
	//	Instead of building actual string, I use an integer to encode state
	//	1 - 'a'
	//	2 - 'e'...
	int countVowelStrings(int n) {
		return recurse(1, n);
	}
	int recurse(int state, int n) {
		if (!n) return 1;

		int sum = 0;
		for (int i = state, i <= 5; ++i)
			sum += recurse(i, n - 1);

		return sum;
	}


	//	Dynamic Programming using 2D DP array
	int countVowelStrings2(int n) {
		int** dp = new int* [n + 1];
		dp[0] = new int[6]{ 0,1,1,1,1,1 };

		for (int i = 1; i <= n; ++i) {
			dp[i] = new int[6]{ 0 };
			for (int j = 1; j <= 5; ++j) {
				dp[i][j] = dp[i][j - 1] + dp[i - 1][j];
			}
		}

		int res = dp[n][5];
		for (int i = 0; i <= n; ++i) delete[] dp[i];
		delete[] dp;
		return res;
	}



	//	Since in 2D DP, only previous row and current row is used, it can be reduced to only 1D array!
	//	Dynamic Programming using 1D array of constant size. O(6)
	int countVowelStrings3(int n) {
		int* dp = new int[6]{ 0,1,1,1,1,1 };

		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= 5; ++j) {
				dp[j] = dp[j] + dp[j - 1];
			}
		}

		int res = dp[5];
		delete[] dp;
		return res;
	}
};