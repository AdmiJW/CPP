#include <vector>
#include <queue>
using namespace std;

//https://leetcode.com/problems/shortest-path-in-a-grid-with-obstacles-elimination/
/*
 *	Can you believe this problem can be solved without any DP? Just pure BFS?
 *	This is a BFS, matrix problem.
 *
 *	Let's see some edge cases: If grid is 1x1, the distance is 0. If given k is larger than the row and column length,
 *	we can immediately take the shortest path by going along the edges in L shape.
 *
 *	At a particular grid, we know we can come from above, below, left and right (The problem would have become DP if
 *	we are only allowed to move right/down). Therefore, some grids would take shorter distance to reach if we previously
 *	chose to destroy some obstacles using our moves. How do we record that?
 *
 *	Let's approach the problem first from BFS point of view. Using BFS, we can perform level order traversal which we
 *	know what 'distance' we are currently on. We will have a Queue of 'moves' that we had explored previously to
 *	continue exploring in the current turn.
 *
 *	Since we are using BFS, whenever we had reached the bottom right, it must be the shortest path so we can immediately
 *	return the current 'level' of BFS we are in.
 *	However in this problem, we would possibly had reached a grid at different number of k left (Available obstacle eliminations).
 *	Therefore apart from recording visited grid at (x,y), we would extend its dimensionality to record also the k left.
 *
 *	visited[x][y][z] = true 	means that grid[x][y] is visited previously with z available obstacle eliminations left.
 *
 *	This would mean time complexity of O( M * N * K), which in this case suffices. Space complexity is the same.
 */

class Solution {
public:
    int shortestPath(vector<vector<int>>& grid, int k) {
		const vector<vector<int>> DIRS = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };
		const int rows = grid.size();
		const int cols = grid[0].size();
		if (rows == 1 && cols == 1) return 0;
		if (k >= rows + cols - 2) return rows + cols - 2;

		vector<vector<vector<bool>>> visited(rows, vector<vector<bool>>(cols, vector<bool>(k+1, 0)));
		// Stores steps in { row, col, kLeft }
		queue<vector<int>> queue;

		// Start at (0,0) with k eliminations left
		queue.push({0, 0, k});
		visited[0][0][k] = true;

		// BFS
		for (int layer = 0; !queue.empty(); ++layer) {
			int size = queue.size();
			while (size-- > 0) {
				auto step = queue.front();
				queue.pop();
				int r = step[0], c = step[1], e = step[2];

				// 4 directions.
				// Conditions to NOT explore a grid
				// 1. Invalid, out of bounds grid
				// 2. Involves elimination of obstacle with 0 moves left
				// 3. A more inexpensive path already existed

				for (auto& d : DIRS) {
					int nr = r + d[0], nc = c + d[1];
					if (nr < 0 || nr >= rows || nc < 0 || nc >= cols) continue;
					int elimLeftIfMove = grid[nr][nc] == 1 ? e - 1 : e;
					if (elimLeftIfMove == -1 || visited[nr][nc][elimLeftIfMove]) continue;

					if (nr == rows - 1 && nc == cols - 1)
						return layer + 1;

					visited[nr][nc][elimLeftIfMove] = true;
					queue.push({nr, nc, elimLeftIfMove});
				}
			}
		}
		return -1;
    }
};