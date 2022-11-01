#include <vector>
using namespace std;

// https://leetcode.com/problems/where-will-the-ball-fall/
/*
 * This is a DFS problem.
 *
 * What we really have to do, is to simulate each ball's movement in the grid.
 * Since the ball moves from grid to grid, we can view this problem as DFS, as each grid is a node.
 *
 * At each node, check if the ball is stuck or not.
 * 		> If the ball is in [/] grid, check if its left is a wall, or a [\] grid.
 * 		  If it is, then the ball is stuck
 *
 * 		> If the ball is in [\] grid, check if its right is a wall, or a [/] grid.
 * 		  If it is, then the ball is stuck
 *
 * Otherwise, the ball can safely move to the next depth. Continue until the ball is stuck, or had
 * reached the bottom of the grid.
 */



class Solution {
public:
	vector<int> findBall(vector<vector<int>>& grid) {
		vector<int> res(grid[0].size());

		for (int i = 0; i < grid[0].size(); ++i)
			res[i] = dfs(i, grid);

		return res;
	}



	int dfs(int column, vector<vector<int>>& grid) {
		int depth = 0;

		while (depth < grid.size()) {
			if (
				// Ball goes to the left, but is blocked
				(
					grid[depth][column] == -1 &&
					(column == 0 || grid[depth][column - 1] == 1)
					) ||
				// Ball goes to the right, but is blocked
				(
					grid[depth][column] == 1 &&
					(column == grid[0].size() - 1 || grid[depth][column + 1] == -1)
					)
				) return -1;

			column += grid[depth][column];
			++depth;
		}

		return column;
	}
};