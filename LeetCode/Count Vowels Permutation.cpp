
typedef long long int LONG;

//https://leetcode.com/problems/count-vowels-permutation/
/*
 *  This is a pure Dynamic Programming problem.
 *
 *  If I know how many permutation of vowel strings are in N-1 length, then I
 *  surely will be able to calculate number of permutation of vowel strings for N length
 *  in O(1) time!
 *
 *  > To put a 'a', before it must be e/i/u
 *  > To put a 'e', before it must be a/i
 *  > To put a 'i', before it must be e/o
 *  > To put a 'o', before it must be i
 *  > To put a 'u', before it must be i/o
 *
 *  Using a 2D (Can be optimized to 1D to O(1) space), where rows indicate the length of vowel string starting
 *  from length 1 (Base case), and 5 columns representing latest vowel is 'a','e','i','o','u', we can
 *  easily solve the problem in O(N) time and O(N) space.
 */


class Solution {
public:
	int countVowelPermutation(int n) {
		if (n == 1) return 5;
		const int MOD = 1000000007;

		LONG dp[5] = { 1,1,1,1,1 };
		for (int i = 2; i <= n; ++i) {
            LONG newdp[5];
            // For a, before it must be e/i/u
            newdp[0] = (dp[1] + dp[2] + dp[4]) % MOD;
            // For e, before it must be a/i
            newdp[1] = (dp[0] + dp[2]) % MOD;
            // For i, before it must be e/o
            newdp[2] = (dp[1] + dp[3]) % MOD;
            // For o, before it must be i
            newdp[3] = dp[2];
            // For u, before it must be i/o
            newdp[4] = (dp[2] + dp[3]) % MOD;

            dp[0] = newdp[0]; dp[1] = newdp[1]; dp[2] = newdp[2];
            dp[3] = newdp[3]; dp[4] = newdp[4];
		}
        return (int)((dp[0] + dp[1] + dp[2] + dp[3] + dp[4]) % MOD);
	}
};