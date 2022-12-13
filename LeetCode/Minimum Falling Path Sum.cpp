#include <vector>
using namespace std;

// https://leetcode.com/problems/minimum-falling-path-sum/
/*
 * This is a DP problem.
 *
 * Starting from the last row, the minimum falling path sum of each element is itself. Then we move upwards, and for each
 * element, we find the minimum sum of the three elements below it, and add it to itself. This is done in a bottom-up manner.
 */

class Solution {
public:
    int minFallingPathSum(vector<vector<int>>& matrix) {
        const int r = matrix.size(), c = matrix[0].size();
        vector<int> dp(c, 0);

        for (int i = 0; i < c; ++i) dp[i] = matrix[r-1][i];

        for (int i = r - 2; i >= 0; --i) {
            vector<int> temp(c, 0);

            for (int j = 0; j < c; ++j) {
                int m = dp[j];
                if (j > 0) m = min(m, dp[j-1]);
                if (j < c - 1) m = min(m, dp[j+1]);
                temp[j] = m + matrix[i][j];
            }

            dp = temp;
        }

        int m = dp[0];
        for (int i = 1; i < c; ++i) m = min(m, dp[i]);
        return m;
    }
};
