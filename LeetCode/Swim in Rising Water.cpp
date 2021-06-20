#include <queue>
#include <vector>
using namespace std;

//https://leetcode.com/problems/swim-in-rising-water/
/*
 * 	Turns out, this is a shortest path / binary search and BFS problem.
 *
 * 	From the question, what we are actually looking for is to find a path connecting node (0,0) to node (n-1,n-1),
 * 	with the largest element along the path minimized.
 *
 * 	If we have a strong memory, recall what dijkstra algorithm does (If not familiar, look into Algorithms > Dijkstra Algorithm)
 * 	Dijkstra algorithm performs BFS, but does it greedily by always picking the next move with minimum cost. This is exactly
 * 	what we should do! If we are finding a path from upperleft to lowerright, do it greedily using Dijkstra algorithm
 * 	works perfectly fine!
 *
 * 	Heap uses log(N) time, and potentially we need to explore all the grid, thus O(N log N). Space complexity is O(N) for
 * 	the heap and also visited array.
 *
 * 	=========================================================================
 *
 * 	Another way would be to perform binary search on the solution itself. See:
 *
 * 	The solution is always enclosed in range [1,N*N-1] according to the problem (Although impossible to be 1).
 * 	Thus, we can always make a guess on the solution, and check if it is true or not via BFS.
 *
 *  In other words, once we make a guess, we try to check if it's possible to travel from upperleft to lowerright
 *  with all elements in path smaller than or equal to our guesses.
 *
 *  If it is possible, we could be greedy and check whether smaller guesses is also possible. If not possible, then
 *  make a larger guess. That is for binary search.
 */


class Solution {
public:

	//	Dijkstra algorithm solution
	int swimInWater(vector<vector<int>>& grid) {
		auto comparator = [grid](pair<int, int>& l, pair<int, int>& r) {
			return grid[l.first][l.second] > grid[r.first][r.second];
		};
		
		const int len = grid.size();
		const int DIRS[][2] = { {-1,0}, {1,0}, {0,-1}, {0,1} };
		vector<vector<bool>> visited(len, vector<bool>(len, 0));

		int res = 0;
		priority_queue<pair<int, int>, vector<pair<int,int>>, decltype(comparator)> heap(comparator);

		heap.push({0, 0});
		visited[0][0] = true;

		while (!heap.empty()) {
			auto next = heap.top(); heap.pop();
			int i = next.first;
			int j = next.second;

			//	Update res
			res = max(grid[i][j], res);

			//	If reached end, return
			if (i == len - 1 && j == len - 1) return res;

			//	Else explore. Remember do not create cycle
			for (auto& dir : DIRS) {
				int i2 = i + dir[0], j2 = j + dir[1];
				if (i2 < 0 || i2 >= len || j2 < 0 || j2 >= len
					|| visited[i2][j2])
					continue;

				visited[i + dir[0]][j + dir[1]] = true;
				heap.push({ i + dir[0], j + dir[1] });
			}
		}
		return -1;
	}



	//	Binary search on limit solution
	int swimInWater2(vector<vector<int>>& grid) {
		const int len = grid.size();

		int leftlimit = 0, rightlimit = len*len-1;

		while (leftlimit < rightlimit) {
			int target = leftlimit + (rightlimit - leftlimit) / 2;

			//	Performs BFS to find out whether the target is possible or not
			if (bfs(grid, target)) rightlimit = target;
			else leftlimit = target + 1;
		}
		return leftlimit;
	}

	bool bfs(vector<vector<int>>& grid, int limit) {
		if (grid[0][0] > limit) return false;

		const int len = grid.size();
		const int DIRS[][2] = { {-1,0}, {1,0}, {0,-1}, {0,1} };

		vector<vector<bool>> visited(len, vector<bool>(len, 0));
		queue<pair<int, int>> queue;

		queue.push({0, 0});
		visited[0][0] = true;

		while (!queue.empty()) {
			auto pos = queue.front(); queue.pop();
			if (pos.first == len - 1 && pos.second == len - 1) return true;

			for (auto& dir : DIRS) {
				int i2 = pos.first + dir[0], j2 = pos.second + dir[1];
				if (i2 < 0 || i2 >= len || j2 < 0 || j2 >= len
					|| visited[i2][j2] || grid[i2][j2] > limit)
					continue;
				visited[i2][j2] = true;
				queue.push({ i2,j2 });
			}
		}
		return false;
	}
};