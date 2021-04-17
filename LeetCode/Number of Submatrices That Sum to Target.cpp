#include <vector>
using namespace std;

//https://leetcode.com/problems/number-of-submatrices-that-sum-to-target/
/*
 * 	This is a matrix, Dynamic Programming problem with possible sliding window approach
 *
 * 	First of all, when faced with the problem you can't run from generating prefix sum matrix,
 * 	which is a dynamic programming approach.
 * 	Essentially, what a prefix sum array allows us to do is to query the sum in a matrix in
 * 	O(1) time.
 * 	However, there are 2 general approaches in this problem:
 * 		>	Prefix sum apply to each row only
 * 		>	Prefix sum apply to matrix
 *
 * 	Let's see each one in detail. Approaches are always time complexity O(MN^2)
 *
 * 	----------------------------------------
 * 	Approach 1: Prefix sum in each row
 *
 * 	Eg:
 * 	1, 1, 1		-->		1, 2, 3
 * 	2, 2, 2		-->		2, 4, 6
 *
 * 	Once the prefix sum like this is generated, select each row to become our origin row. Then, Loop thru all the possible
 * 	column combinations (c1, c2). Then, extend downwards to cover all submatrix of width (c2 - c1), starting from origin row.
 *
 * 	This is done by running a sliding window. Say above example matrix of 1's and 2's. To cover 2x2 submatrix from c0 to c1,
 * 	Say we are currently at row 0 as origin row, c0 and c1, So far the sum is 2 (Indicating 1,1 in first row). To cover and
 * 	become
 * 			[1,1]
 * 			[2,2],
 * 	simply extend downwards and add the '4' into our sum so far.
 *
 * 	-------------------------------------------
 *
 * 	Approach 2: Prefix sum of array.
 *
 * 	On our dp array ij, indicates the sum of elements in matrix up until ij. Say:
 * 	1,1,1
 * 	2,2,2
 * 	3,3,3
 *
 * 	Then dp(0,0) is 1, dp(1,1) is 6 since (1+1+2+2), dp(2,2) is essentially sum of whole array, dp(0,2) is 3 (1+1+1)
 *
 * 	To get the sum of every submatrix, simply loop thru each possible origins (x,y), and loop thru possible endpoint (w,h)
 * 	such that x <= w, y <= h.
 *	I encourage you to draw the grids and observe how to get the submatrix sum, which is by eliminating the blocks above and
 *	to the left of the origin point, and adding the overlapping part back into the sum.
 */

class Solution {
public:
	int numSubmatrixSumTarget(vector<vector<int>>& matrix, int target) {
		const int row = matrix.size(), col = matrix[0].size();
		vector<vector<int>> dp(row + 1, vector<int>(col + 1, 0));

		//	Create 2D Prefix Sum Array. Note the DP array has extra row and column for ease of use
		for (int r = 0; r < row; ++r) {
			for (int c = 0; c < col; ++c) {
				dp[r + 1][c + 1] = matrix[r][c] + dp[r][c + 1] + dp[r + 1][c] - dp[r][c];
			}
		}

		int res = 0;
		//	For each origin point, for each height and width, find out the sum O(N^4) estimate (or O(MN^2)
		for (int r = 0; r < row; ++r) {
			for (int c = 0; c < col; ++c) {
				for (int w = r; w < row; ++w) {
					for (int h = c; h < col; ++h) {
						int sum = dp[w + 1][h + 1] - dp[r][h + 1] - dp[w + 1][c] + dp[r][c];
						if (sum == target) ++res;
					}
				}
			}
		}

		return res;
	}
};