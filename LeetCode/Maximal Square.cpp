#include <vector>
using namespace std;



//https://leetcode.com/problems/maximal-square/
/*
 * This is a matrix dynamic programming problem
 *
 * Let us have a dp matrix dp[][], where dp[i][j] records the maximum square that can be formed if [i][j] serves as
 * the bottomright grid for the square.
 *
 *  Eg:
 *  	[1,1,1]						[1,1,1]
 *  	[1,1,1]		----DP--->		[1,2,2]
 *  	[1,1,1]						[1,2,3]
 *
 *  [1][1], [1][2], and [2][1] is 2 because a square of size 2 is formable if [i][j] is bottomright of the square.
 *  in [2][2], a square of size 3 is formable if [2][2] is bottomright of the square
 *
 *
 * At a particular grid at index [i][j], I can attempt to form a square to size N which bottom right corner at [i][j],
 * if and only if:
 * 		- matrix[i][j] is 1 and not 0
 * 		- dp[i-1][j] is at least N-1
 * 		- dp[i][j-1] is at least N-1
 * 		- dp[i-1][j-1] is at least N-1
 *
 * Therefore, now you should see the recurrance relation here. However, since we are using at most previous row, DP
 * can simply be optimized to space O(N). Time must be O(N^2) - size of matrix
 */


class Solution {
public:
	int maximalSquare(vector<vector<char>>& matrix) {
		const int row = matrix.size(), col = matrix[0].size();
		int res = 0;

		// Conceptually, we have 2D matrix same size as provided matrix
		// Each DP grid records the maximum square it can form, given that that grid is the bottomright grid
		vector<int> dp(col, 0);
		int prevdiag;

		for (auto& r : matrix) {
			prevdiag = dp[0];
			dp[0] = r[0] - '0';

			// For test case [[1,0]]. We need consider first element (size 1 square)
			res = max(res, dp[0]);

			for (int i = 1; i < col; ++i) {
				// If this grid wants to form until size N, dp[i-1][j-1], dp[i-1][j] and dp[i][j-1] must be N-1.
				int maxSquareCanForm = r[i] != '0'
					? min(dp[i], min(dp[i - 1], prevdiag)) + 1
					: 0;

				// Preserve previous diagonal dp[i-1][j-1] for next column
				prevdiag = dp[i];

				dp[i] = maxSquareCanForm;
				res = max(res, dp[i]);
			}
		}
		return res * res;		// Return area, not side length
	}

};
