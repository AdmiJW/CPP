#include <vector>
using namespace std;

//https://leetcode.com/problems/max-area-of-island/
/*
 * 	This is a classical DFS problem (Flood fill).
 *
 * 	Iterate through each grid. If the grid is a land, perform DFS on it which check for
 * 	neighbors if it is land, but before doing that, ensure that the originating land is marked
 * 	as visited so we don't end up in infinite recursion loop.
 *
 * 	This can be modelled as a graph, where each node is connecting to its adjacent 4 sides in
 * 	the grid.
 */

class Solution {
public:
	int DIRS[4][2] = { {-1,0}, {1,0}, {0,-1}, {0,1} };

	int maxAreaOfIsland(vector<vector<int>>& grid) {
		int res = 0;
		for (int i = 0; i < grid.size(); ++i) {
			for (int j = 0; j < grid[0].size(); ++j)
				res = max(res, recurse(grid, i, j));
		}
		return res;
	}


	int recurse(vector<vector<int>>& grid, int r, int c) {
		if (r == -1 || r == grid.size() || c == -1 || c == grid[0].size() || !grid[r][c])
			return 0;

		int res = 1;		//	Since the grid is a land, start with 1
		grid[r][c] = 0;		//	Mark as visited. !Mutates the grid

		for (auto& d : DIRS)
			res += recurse(grid, r + d[0], c + d[1]);
		return res;
	}
};