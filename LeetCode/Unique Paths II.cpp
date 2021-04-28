#include <vector>
using namespace std;

//https://leetcode.com/problems/unique-paths-ii/
/*
 * Similar concept as the unique path I question. Except for this one, if there is any obstacle in the deepest row or rightmost column, then any grid to the left
 * or above, will end up as 0 ways.
 *
 * As for intermediate grids, if we see an obstacle, we will simply mark this path as 0 instead of sum of right + below. Therefore when the grid sees the obstacle,
 * it knows there are 0 ways if he choose to move to the obstacle
 *
 * 	This one we can make a 2D array, or better 1D array to solve as in unique path I solution. However, since the obstacleGrid itself is passed into the function,
 * 	we can just use that 2D grid passed in and resulting in O(1) space complexity solution
 */

class Solution {
public:

    //  Dynamic programming solution with tabulation
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        const int row = obstacleGrid.size(), col = obstacleGrid[0].size();
        vector<vector<int>> dp(row+1, vector<int>(col+1, 0));
        dp[0][1] = 1;
        dp[1][0] = 1;

        for (int i = 0; i < row; ++i) {
            for (int c = 0; c < col; ++c) {
                if (obstacleGrid[i][c]) continue;
                dp[i][c] = dp[i - 1][c] + dp[i][c - 1];
            }
        }
        return dp[row][col];
    }


    //  Space optimized DP solution
    int uniquePathsWithObstacles2(vector<vector<int>>& obstacleGrid) {
        const int row = obstacleGrid.size(), col = obstacleGrid[0].size();
        vector<int> dp(col + 1, 0);
        dp[0] = 1;

        for (int i = 0; i < row; ++i) {
            for (int c = 0; c < col; ++c) {
                if (obstacleGrid[i][c]) dp[c+1] = 0;
                else dp[c + 1] = dp[c] + dp[c + 1];
            }
            dp[0] = 0;
        }

        return dp[col];
    }
};