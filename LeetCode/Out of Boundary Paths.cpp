#include <vector>
using namespace std;

//https://leetcode.com/problems/out-of-boundary-paths/
/*
 * 	This is a Dynamic Programming Problem
 *
 * 	Given maximum moves, we want to know how many ways to kick the ball out of boundary.
 *
 * 	Let's start up small. Say we only given 1 moves, then the only way is when the ball is at some boundary
 * 	itself. Check the 4 directions, and see if it goes out of bound. If it does, add 1 to the ways
 *
 * 	Now, move up to 2 moves. Of course, we will still check for adjacent boundaries. However, we can also kick
 * 	it to adjacent grid that are not out of bounds! In that case, once the ball is kicked onto the selected grid,
 * 	I will be left with N-1 moves, right?
 * 	If I know the number of ways to kick the ball out of boundary with N-1 moves on that grid beforehand, I would
 * 	easily obtain the ways!
 *
 * 	That introduces the Dynamic Programming solution, where we use 2D grid for tabulation! Every move, we simply
 * 	tabulate the number of ways to kick ball out of boundary based on previous tabulated data.
 */

class Solution {
public:

	//	Dynamic Programming Solution
	int findPaths(int m, int n, int maxMove, int startRow, int startColumn) {
		const int DIRS[][2] = { {-1,0}, {1,0}, {0,-1}, {0,1} };
	
		vector<vector<int>> v1(m, vector<int>(n, 0));
		vector<vector<int>> v2(m, vector<int>(n, 0));
		auto& prev = v1;
		auto& curr = v2;

		while (maxMove--) {
			for (int i = 0; i < m; ++i) {
				for (int j = 0; j < n; ++j) {
					curr[i][j] = 0;

					for (auto& d : DIRS) {
						int x = i + d[0], y = j + d[1];
						if (x < 0 || x >= m || y < 0 || y >= n) curr[i][j] += 1;
						else curr[i][j] = (curr[i][j] + prev[x][y]) % 1000000007;
					}
				}
			}
			auto& temp = prev;
			prev = curr;
			curr = prev;
		}
		return prev[startRow][startColumn];
	}
};