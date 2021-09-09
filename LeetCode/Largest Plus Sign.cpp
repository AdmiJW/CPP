#include <vector>
#include <unordered_set>
#include <queue>
using namespace std;

//https://leetcode.com/problems/largest-plus-sign/
/*
 * 	This is a Dynamic Programming problem.
 *
 * 	My initial thought is: If I know a plus sign exists at center (x,y) of size N, I can check whether it
 * 	forms a plus sign of size N+1 by attempting to expand its 4 sides.
 * 	This involves BFS, storing the center position of every valid plus sign of size N (layer), then checking
 * 	if it also can be expanded to size N+1 (next layer).
 *
 * 	However, this algorithm runs N^4 in time, and is inefficient.
 *
 * 	------------------------------
 *
 * 	The dynamic programming solution involves first knowing at (x,y), what is the maximum reach in each
 * 	direction (top, left, bottom, right).
 * 	Then, if (x,y) is also '1', the max plus sign formed would be minimum of max reach in (left, top, bottom, right).
 *
 * 	We could use 4 dp arrays to store that information. Once optimized, can be done in 1 DP array only.
 */


class Solution {
public:

	// BFS solution - Time limit exceeded. O(N^4)
	int orderOfLargestPlusSign(int n, vector<vector<int>>& mines) {
		unordered_set<int> zeroes;
		queue< vector<int> > pluses;

		// Record the positions of the zeroes
		for (auto& m : mines)
			zeroes.insert(encode(m[0], m[1], n));

		// Order of 1 appending
		for (int i = 0; i < n; ++i)
			for (int j = 0; j < n; ++j)
				if (!zeroes.count(encode(i, j, n)))
					pluses.push({i, j});

		// Now, search for next order plus signs
		int res = 0;
		for (int order = 1; !pluses.empty(); ++order) {
			res = order;
			int size = pluses.size();

			while (size-- > 0) {
				auto pos = pluses.front();
				pluses.pop();
				// Offset left
				if (pos[0] - order < 0 || zeroes.count(encode(pos[0] - order, pos[1], n))) continue;
				// Offset right
				if (pos[0] + order >= n || zeroes.count(encode(pos[0] + order, pos[1], n))) continue;
				// Offset above
				if (pos[1] - order < 0 || zeroes.count(encode(pos[0], pos[1] - order, n))) continue;
				// Offset below
				if (pos[1] + order >= n || zeroes.count(encode(pos[0], pos[1] + order, n))) continue;
				// Test passed. Append.
				pluses.push(pos);
			}
		}
		return res;

	}

	// Encodes 2D space into an integer
	int encode(int r, int c, int n) {
		return r * n + c;
	}



	// Dynamic Programming solution
	int orderOfLargestPlusSign2(int n, vector<vector<int>>& mines) {
		// false means 1, true means 0
		vector<vector<bool>> grid(n, vector<bool>(n, 0));
		for (auto& m : mines)
			grid[m[0]][m[1]] = true;

		// DP[i] indicates how many 1s maximum reach in the direction
		vector<vector<int>> top(n, vector<int>(n, 0));
		vector<vector<int>> bottom(n, vector<int>(n, 0));
		vector<vector<int>> left(n, vector<int>(n, 0));
		vector<vector<int>> right(n, vector<int>(n, 0));

		// Fill top and left first
		for (int i = 0; i < n; ++i)
			for (int j = 0; j < n; ++j) {
				if (i - 1 != -1) top[i][j] = !grid[i - 1][j] ? top[i - 1][j] + 1 : 0;
				if (j - 1 != -1) left[i][j] = !grid[i][j - 1] ? left[i][j - 1] + 1 : 0;
			}

		// Fill bottom and right
		for (int i = n - 1; i >= 0; --i)
			for (int j = n - 1; j >= 0; --j) {
				if (i + 1 != n) bottom[i][j] = !grid[i + 1][j] ? bottom[i + 1][j] + 1 : 0;
				if (j + 1 != n) right[i][j] = !grid[i][j + 1] ? right[i][j + 1] + 1 : 0;
			}

		int res = 0;
		// Find max
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				if (grid[i][j]) continue;
				int order = 1 + min(left[i][j], min(right[i][j], min(top[i][j], bottom[i][j])));
				res = max(res, order);
			}
		}
		return res;
	}

	// Space optimized DP solution - One N2 array, but 4 passes
	int orderOfLargestPlusSign3(int n, vector<vector<int>>& mines) {
		unordered_set<int> zero;
		vector<vector<int>> dp(n, vector<int>(n, 0));

		for (auto& mine : mines)
			zero.insert(mine[0] * n + mine[1]);
		int ans = 0, combo;

		// Sweep across each row, left to right then right to left
		for (int r = 0; r < n; ++r) {
			combo = 0;
			for (int c = 0; c < n; ++c) {
				combo = zero.count(r * n + c) ? 0 : combo + 1;
				dp[r][c] = combo;
			}

			combo = 0;
			for (int c = n - 1; c >= 0; --c) {
				combo = zero.count(r * n + c) ? 0 : combo + 1;
				dp[r][c] = min(dp[r][c], combo);
			}
		}

		for (int c = 0; c < n; ++c) {
			combo = 0;
			for (int r = 0; r < n; ++r) {
				combo = zero.count(r * n + c) ? 0 : combo + 1;
				dp[r][c] = min(dp[r][c], combo);
			}

			combo = 0;
			for (int r = n - 1; r >= 0; --r) {
				combo = zero.count(r * n + c) ? 0 : combo + 1;
				dp[r][c] = min(dp[r][c], combo);
				ans = max(ans, dp[r][c]);
			}
		}

		return ans;
	}
};