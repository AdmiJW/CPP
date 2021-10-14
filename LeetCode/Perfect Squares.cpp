#include <vector>
using namespace std;

//https://leetcode.com/problems/perfect-squares/

/*
 * 	The 2 main ways to solve this question is to use Dynamic programming or Breath First Search. Although it can be solved using mathematics,
 * 	(Lagrange's Four Square Theorem)
 *
 * 	For dynamic programming, We must first realize for any integer n, the only plausible perfect squares that can go into it are only in the
 * 	range 1 to sqrt(n). What happens to n if we choose each possible combinations of perfect squares from 1 to sqrt(n)?
 *
 * 	THerefore we could use bottom up approach for this. We know that for n = 0, the least number of perfsqr to add up is 0. For 1, it will
 * 	find out the ranges 1 to sqrt(n), which is 1 itself. After using the 1 as one of perfsqr, the remaining is 0. THerefore the solution
 * 	is 1 + perfsqr(0), which is 1. This continues until n and we'll get the answer.
 *
 * 	---------------------------------------------------
 *
 * 	For BFS approach, we start out with the root node as n itself. Then similarly, we find out the ranges from 1 to sqrt(n). We'll create
 * 	the next depth of nodes which is every possible subtraction of the n with the perfsqr. This continues until we have met the first subtraction
 * 	to 0, which we shall return the layer depth as the answer. Note the layer depth at root node is 0 (So if n = 0, returns 0)
 */


class Solution {
public:

    // DP solution O(Nsqrt(N) time, O(N) space
    int numSquares(int n) {
        vector<int> dp(n + 1, INT32_MAX);
        dp[0] = 0;

        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j * j <= i; ++j) {
                dp[i] = min(dp[i], dp[i - j * j] + 1);
            }
        }
        return dp[n];
    }

};