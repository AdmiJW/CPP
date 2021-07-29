#include <vector>
using namespace std;

//https://leetcode.com/problems/01-matrix/
/*
 * 	This is a Breadth First Search / Dynamic Programming problem
 *
 * 	In Brute force, for each of the grid that are '1', we perform a linear search on the matrix to find closest '0'
 * 	That is time consuming as it takes O(M^2 N^2) time.
 *
 * 	In a better brute force, we use BFS. For each of the '1', we perform a BFS to search the closest '0'. However it
 * 	is still time consuming when the case is filled with a lot of '1's.
 * 	We could turn the tables, so that when we found a '0', we use BFS to update all the '1' grids.
 *
 *  ===========================================================
 *
 *  The best solution is to use DP. The intuition is:
 *  	>	If the grid itself is '0', the closest distance must be 0
 *  	>	Otherwise, if I already know the neighbor's closest distance to 0, then surely I can take the minimum+1 of it.
 *
 * 	The problem is that, say we are starting out at position (0,0). We have no way of knowing beforehand the closest distance
 * 	to 0 of the (0,1) and (1,0)!
 *
 * 	Therefore, we split the problem into 2 DP:
 * 		>	DP finds the closest distance to 0, considering ONLY TOP AND LEFT grids
 * 		>	DP finds the closest distance to 0, considering BELOW AND RIGHT grids
 *
 * 	At the end, surely by combining the result of DP, will achieve the result of the original problem statement
 */

class Solution {
public:

	// DP solution
	vector<vector<int>> updateMatrix(vector<vector<int>>& mat) {
		const int r = mat.size();
		const int c = mat[0].size();
		vector<vector<int>> res(r, vector<int>(c, 0));

		// Check above and left side for DP
		for (int i = 0; i < r; ++i) {
			for (int j = 0; j < c; ++j) {
				if (mat[i][j] == 0)
					res[i][j] = 0;
				else {
					res[i][j] = INT32_MAX / 2;
					if (i > 0) res[i][j] = min(res[i][j], res[i - 1][j] + 1);	// Check above
					if (j > 0) res[i][j] = min(res[i][j], res[i][j - 1] + 1);	// Check left
				}
			}
		}

		// Check right and below side for DP
		for (int i = r - 1; i >= 0; --i) {
			for (int j = c - 1; j >= 0; --j) {
				if (i + 1 < r) res[i][j] = min(res[i][j], res[i + 1][j] + 1);	// Check below
				if (j + 1 < c) res[i][j] = min(res[i][j], res[i][j + 1] + 1);	// Check right
			}
		}

		return res;
	}
};