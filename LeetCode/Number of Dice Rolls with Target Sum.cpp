#include <vector>
using namespace std;


//https://leetcode.com/problems/number-of-dice-rolls-with-target-sum/
/*
 * 	This is a DP problem.
 *
 * 	You are given n dices each having k faces for range [1, k]. You need to find out how many
 * 	ways to get sum of target using all n dices.
 *
 * 	By viewing it from DP perspective, we will have a 2D DP array:
 *
 *  	dp[i][n]
 *
 *  where dp[i][n] shows the total number of ways to achieve sum n using i dices.
 *
 *
 *  We will run a 3 level nested loop: For each nth dice, for each possible face rolled, for each possible sum that
 *  is achieved using that possible face rolled:
 *
 *  If let's say I am rolling the 2nd dice, and i rolled a 3. The possible sums that I can achieve is [3,4,5,6... target]
 *  We have to add the previous number of ways into current DP:
 *
 *  	dp[2][sum] = SUM( dp[1][sum-3] ) for all sum = [3,4,5,6...target]
 *
 */


class Solution {
public:

    const static int MODULO = 1000000007;

    int numRollsToTarget(int n, int k, int target) {
        vector<vector<int>> dp(n + 1, vector<int>(target + 1, 0));

        dp[0][0] = 1;

        for (int x = 1; x <= n; ++x) {
            for (int y = 1; y <= k; ++y) {
                for (int z = y; z <= target; ++z) {
                    dp[x][z] = (dp[x][z] + dp[x - 1][z - y]) % MODULO;
                }
            }
        }

        return dp[n][target];
    }
};