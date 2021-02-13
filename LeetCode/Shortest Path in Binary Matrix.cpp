#include <vector>
#include <queue>
using namespace std;

//https://leetcode.com/problems/shortest-path-in-binary-matrix/
/*
 * 	This is a Breadth First Search problem, since BFS is good for searching shortest distance (Apart from more
 * 	complex algorithms like A* algorithm)
 *
 * 	Use a Queue data structure to perform BFS. The level of the bfs is important to know the distance of the bfs.
 *	Start from the left upper corner, begin breadth first search algorithm. For each grid, explore it's eight sides.
 *	If the adjacent neighbor is not occupied (0), then add that to the exploration queue.
 *	Also, we have to mark that the grid is pending to be explored, so that it don't get added to the queue twice.
 *	We can do this in place, by marking the grid to 1, or use extra space to enforce immutability.
 *
 *	Time complexity is O(N^2) if square matrix, and space is O(max(N,M) ), either edge is longer will take that much
 *	space in the queue. (Except if use visited set instead of in-place)
 */

class Solution {
public:
	int shortestPathBinaryMatrix(vector<vector<int>>& grid) {
		const int row = grid.size(), col = grid[0].size();
		if (grid[0][0] || grid[row - 1][col - 1]) return -1;

		const int dirs[][2] = { {-1,-1}, {-1,0}, {-1,1}, {0,-1}, {0,1}, {1,-1}, {1,0}, {1,1} };
		queue< pair<int, int> > bfs;
		int level = 0;
		bfs.emplace(make_pair(0, 0));
		grid[0][0] = 1;

		while (!bfs.empty()) {
			++level;
			int levelSize = bfs.size();

			while (levelSize--) {
				auto pos = bfs.front(); bfs.pop();
				if (pos.first == row - 1 && pos.second == col - 1) return level;

				for (auto dir : dirs) {
					int r = pos.first + dir[0], c = pos.second + dir[1];
					try {
						if (!(grid.at(r).at(c))) {
							bfs.emplace(make_pair(r, c));
							grid[r][c] = 1;
						}
					}
					catch (...) {}
				}
			}
		}
		return -1;
	}
};