#include <vector>
using namespace std;

//https://leetcode.com/problems/longest-increasing-path-in-a-matrix/
/*
 * 	This is a graph DFS traversal with Dynamic Programming - Memoization problem.
 *
 * 	Every grid in the matrix is a node in graph. The node is connected to another node if the other node has value strictly
 * 	greater than current node.
 * 	Due to the nature of going from lower value to higher value, the graph is directed graph, and there shall not exist any
 * 	cycle in the graph.
 *
 * 	If we were to perform brute force, we iterate through each node. For each of the nodes, we simply perform dfs on it and
 * 	see how many maximum layer it can span.
 * 	At the end, simply return the maximum layer of one source node as answer.
 * 	Say the matrix is NxN in size, then the time complexity will be about O(N^4), not efficient at all.
 *
 * 	------------------------------------------------------------------------------------------
 *
 * 	Some of the nodes may have been visited before! Say i have matrix of 1 row: [5,4,3,2]. Now include the newest column
 * 	[5,4,3,2,1]. On node (1), I have to iterate through 5,4,3,2 once more, although it has been previously determined,
 * 	that (2) can span to level 4!
 *
 * 	Therefore simply use a dp array to store the results of DP.
 *
 * 	Say we are exploring a node. If we found out its neighbour haven't been visited yet, we perform the very same DP on it,
 * 	so that DP value of neighbor will be defined and we are able to evaluate the value of neighbor.
 *
 * 	Time is thereby reduced to O(N^2), as each node is never reexplored, all is stored in DP array
 */

class Solution {
public:

	static const int dirs[4][2];

	int longestIncreasingPath(vector<vector<int>>& matrix) {
		int row = matrix.size(), col = matrix[0].size();
		vector<vector<int>> dp(row, vector<int>(col, 0));
		int res = 1;

		for (int i = 0; i < row; ++i) {
			for (int j = 0; j < col; ++j) {
				if (!dp[i][j]) dfs(i, j, matrix, dp);
				res = max(res, dp[i][j]);
			}
		}
		return res;
	}

private:
	void dfs(int i, int j, vector<vector<int>>& matrix, vector<vector<int>>& dp) {
		int res = 1;
		for (const auto& d : dirs) {
			int i2 = i + d[0], j2 = j + d[1];

			if (i2 < 0 || j2 < 0 || i2 >= matrix.size() || j2 >= matrix[0].size()) continue;
			if (matrix[i][j] >= matrix[i2][j2]) continue;
			if (!dp[i2][j2]) dfs(i2, j2, matrix, dp);
			res = max(res, dp[i2][j2] + 1);
		}
		dp[i][j] = res;
	}
};


const int Solution::dirs[4][2] = { {1,0}, {0,1}, {-1,0}, {0,-1} };