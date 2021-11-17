#include <vector>
using namespace std;

//https://leetcode.com/problems/unique-paths/
/*
 * 	A Dynamic Programming Question (Although can possibly be solved using mathematics)
 *
 *	By having a 2D grid of DP array representing the board itself, each grid can record the following information:
 *		- Assuming this grid is the destination (bottom right grid), how many unique paths are there to arrive at the current
 *		  grid?
 *
 *	The transition function is that, to reach the current grid, there is only two possibilities:
 *		>	Coming from grid above
 *		>	Coming from grid to the left
 *	Since these two grids are precomputed due to DP, we can lookup and sum these two DP grid and get the answer to the current
 *	DP grid.
 *
 *	At the end, the answer would be at the bottom right grid of DP.
 *
 *	-------------------------
 *
 *	Since the transition function only uses the row above and the grid to the left, we can optimize the solution to be O(N) space
 *	only.
 */


class Solution {
public:
    int uniquePaths(int m, int n) {
        vector<int> dp(m, 1);
        for (int i = 1; i < m; ++i) {
            for (int j = 1; j < n; ++j)
                dp[j] += dp[j - 1];
        }
        return dp[n - 1];
    }
};