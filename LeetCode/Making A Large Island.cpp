#include <unordered_set>
#include <vector>
using namespace std;

//https://leetcode.com/problems/making-a-large-island/
/*
 * 	This is a Union Find inspired, BFS / DFS matrix problem.
 *
 * 	If you still do not know how to solve finding the maximum area of island (without switching 0 to 1), I suggest go see that
 * 	problem first.
 *
 * 	We can change one single 0 to 1 and result in multiple islands finally connected. See case:
 *
 * 			1
 * 			1
 * 		1 1 0 1 1
 * 			1
 * 			1
 *
 * 	How do we know which '0' to switch to '1'? One way is to brute force. For each '0', switch it to 1, and dfs on surrounding
 * 	islands and get their area. However this has a worst time complexity of O(N^4)
 *
 * 	=======================================
 *
 * 	The optimal solution idea comes from DP / Union Find. First, we should preprocess the matrix so that when we want to query
 * 	the area of a island, it can be done in almost O(1) time (DP). Then, the queried island shall be identified uniquely so that
 * 	we do not overcalculate. See:
 * 		1 1 1
 * 		1 0 1		<<- Exactly the same island!
 * 		1 1 1
 *
 * 	In my solution, I used a Island object to keep track of a mutable Island with a area in it. However, one can simply use a ID
 * 	to assign to each island.
 *
 * 	Then once the island are preprocessed, simply go through each '0' and see what is the area formed by switching it to '1'.
 * 	Do not add area of islands that has the same ID already.
 */


class Solution {
public:

	class Island {
	public:
		int v = 0;
	};
	const vector<vector<int>> DIRS = { {1,0}, {0,1}, {-1,0}, {0,-1} };

	// DP inspired / Union Find solution
	int largestIsland(vector<vector<int>>& grid) {
		const int len = grid.size();
		vector<vector<Island*>> dp(len, vector<Island*>(len, 0));
		int res = 1;

		// Perform regular area BFS/DFS without worry about the switching '0' to '1'
		for (int i = 0; i < len; ++i) {
			for (int j = 0; j < len; ++j) {
				if (grid[i][j] == 1)
					res = max(res, dfs(new Island, grid, dp, i, j));
			}
		}

		// Now that DP array is filled, try to 'brute force' all '0' to '1' and see what happens
		for (int i = 0; i < len; ++i) {
			for (int j = 0; j < len; ++j) {
				if (grid[i][j] == 1) continue;

				// Now that the grid is a '0', we switch it to 1. We'll see if we have island around it to connect?
				unordered_set<Island*> surrounding;
				for (auto& d : DIRS) {
					if (i + d[0] >= 0 && i + d[0] < len && j + d[1] >= 0 && j + d[1] < len && dp[i + d[0]][j + d[1]])
						surrounding.insert(dp[i + d[0]][j + d[1]]);
				}
				int local = 0;
				for (auto is : surrounding)
					local += is->v;
				res = max(local + 1, res);
			}
		}
		return res;
	}


	// DFS to assign grids to particular Island object
	int dfs(Island* island, vector<vector<int>>& grid, vector<vector<Island*>>& dp, int i, int j) {
		const int len = grid.size();

		if (i >= 0 && i < len && j >= 0 && j < len && grid[i][j] == 1 && !dp[i][j]) {
			dp[i][j] = island;
			++island->v;

			for (auto& d : DIRS)
				dfs(island, grid, dp, i + d[0], j + d[1]);
		}
		return island->v;
	}

};