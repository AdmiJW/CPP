#include <vector>
#include <algorithm>
using namespace std;

//https://leetcode.com/problems/triangle/
/*
 * 	This is a Dynamic Programming Problem.
 *
 * 	We want to find out the minimum path sum. So what we could do is to perform depth first search from the
 * 	tip of triangle as the root.
 * 	The problem with this is, if we were to visualize the tree formed, there were overlapping subproblems:
 * 	a node may be visited twice from the parent. Therefore, we shall eliminate this computational cost via
 * 	utilizing the space: DP
 *
 * 	DP uses bottom up approach. So initialize a 2D DP array which each grid actually maps to a node in triangle itself.
 * 	The base case is that at the bottom of triangle, the minimum is always the node value itself.
 *
 * 	For each non-bottom node, it can explore bottom left and bottom right, therefore the formulae is
 * 			node val + MIN( dp[i+1][j], dp[i+1][j+1] )
 * 	At the end, return the dp array's tip of the triangle, consisting of minimum path from top to bottom of triangle
 *
 * 	------------------------
 *
 * 	Notice how the DP only uses the next row in dp array, this opens up possibility to save space by using only 1D array.
 *
 */

class Solution {
public:
	int minimumTotal(vector<vector<int>>& triangle) {
		const int len = triangle.size();
		vector<vector<int>> dp(len, vector<int>(len, 0));

		//	Initialize last row
		copy(triangle[len - 1].begin(), triangle[len - 1].end(), dp[len - 1].begin());

		for (int i = len - 2; i >= 0; --i) {
			for (int j = 0; j <= i; ++j)
				dp[i][j] = triangle[i][j] + min(dp[i + 1][j], dp[i + 1][j + 1]);
		}

		return dp[0][0];
	}


	//	Optimized to use only one row
	int minimumTotal2(vector<vector<int>>& triangle) {
		const int len = triangle.size();
		vector<int> dp(triangle[len - 1].begin(), triangle[len - 1].end());

		for (int i = len - 2; i >= 0; --i) {
			for (int j = 0; j <= i; ++j)
				dp[j] = triangle[i][j] + min(dp[j], dp[j + 1]);
		}

		return dp[0];
	}
};