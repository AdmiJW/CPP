
#include <vector>
using namespace std;


//https://leetcode.com/problems/number-of-islands/
/*
 * This is mainly a DFS/BFS problem.
 *
 * The strategy is to iterate the grid. Once you encounter a '1' - an island, increment the island count,
 * and call the DFS/BFS method which will explore all lands of the island, and marking it as visited
 * (Maybe mark it as '2').
 *
 */

class Solution {

	const vector<vector<int>> DIRS = { {-1, 0}, {0, -1}, {1, 0}, {0, 1} };


public:
	int numIslands(vector<vector<char>>& grid) {
		int islands = 0;

		for (int i = 0; i < grid.size(); ++i) {
			for (int j = 0; j < grid[0].size(); ++j) {
				if (grid[i][j] == '1') {
					explore(grid, i, j);
					++islands;
				}
			}
		}
		return islands;
	}


	// Performs a dfs on provided grid and explores its adjacent neighbors
	// Marks the grid in-place to '2'
	void explore(vector<vector<char>>& grid, int r, int c) {
		grid[r][c] = '2';

		for (auto& DIR : DIRS) {
			int row = r + DIR[0];
			int col = c + DIR[1];
			if (row < 0 || row >= grid.size()) continue;
			if (col < 0 || col >= grid[0].size()) continue;
			if (grid[row][col] != '1') continue;
			explore(grid, row, col);
		}
	}
};
