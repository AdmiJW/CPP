#include <vector>
using namespace std;

//https://leetcode.com/problems/n-th-tribonacci-number/
/*
 *  Fibonacci always had been a good problem for beginners to practice recursion and dynamic programming
 *
 *  Use a dp array of length n+1 (Including T_0).
 *  T_0 = 0, T_1 = T_2 = 1
 *
 *  Then for other n, simply take previous 3 elements in the array and add them up together.
 *  At the end, answer is at last element of array.
 *
 *  You could also do this with recursion and memoization, another form of DP
 *
 *  -------------------------
 *
 *  Note that you only always need to use the last 3 elements in the array! Now you can actually optimize the space
 *  to become O(1)!
 */

class Solution {
public:
	int tribonacci(int n) {
		if (n == 0) return 0;
		if (n <= 2) return 1;
		vector<int> dp(n+1, 0);
		dp[0] = 0;
		dp[1] = dp[2] = 1;

		for (int i = 3; i <= n; ++i)
			dp[i] = dp[i - 1] + dp[i - 2] + dp[i - 3];
		return dp[n];
	}

	int tribonacci2(int n) {
		vector<int> dp = { 0,1,1 };
		if (n <= 2) return dp[n];

		for (int i = 3; i <= n; ++i) {
			int num = dp[0] + dp[1] + dp[2];
			dp[0] = dp[1];
			dp[1] = dp[2];
			dp[2] = num;
		}
		return dp[2];
	}
};