#include <vector>
using namespace std;

//https://leetcode.com/problems/set-matrix-zeroes/
/*
 * 	This is a matrix problem.
 *
 * 	The easiest solution is to create a copy of the matrix, and whenever we encounter a 0, put 0 to all the row and column.
 * 	This cannot be done in place because when we encounter a 0, how do we know this 0 is the one originally in place or
 * 	the one that is set due to other 0 in same row or column?
 *
 * 	To save space, we could use only 2 array of length ROW and COL repsectively, to indicate whether the row and column should
 * 	be set to 0 or not.
 *
 * 	------------------------------
 *
 * 	To use only O(1) space, we could use the first element of each row and column as indicator of which the row and column
 * 	should be set to all 0 or not. However, we must be careful to not mix up.
 * 		>	Say we need to indicate the entire column 0 must be set to 0. We shall not set matrix[0][0] = 0, because
 * 			that would cause the entire row 0 to be set to 0 too.
 * 		>	Instead for this special case, we would use special variable for that, and we check column 0 outside of normal loop
 */

class Solution {
public:
	// O(M+N) extra space solution. O(MN) time
	void setZeroes(vector<vector<int>>& matrix) {
		const int m = matrix.size(), n = matrix[0].size();
		vector<bool> isRowZero(m, 0);
		vector<bool> isColZero(n, 0);

		for (int i = 0; i < m; ++i) {
			for (int j = 0; j < n; ++j) {
				if (matrix[i][j] == 0) {
					isRowZero[i] = true;
					isColZero[j] = true;
				}
			}
		}

		// Fill row zeroes
		for (int i = 0; i < m; ++i) {
			if (!isRowZero[i]) continue;

			for (int j = 0; j < n; ++j) matrix[i][j] = 0;
		}

		// Fill col zeroes
		for (int j = 0; j < n; ++j) {
			if (!isColZero[j]) continue;

			for (int i = 0; i < m; ++i) matrix[i][j] = 0;
		}
	}

	// O(1) extra space solution. O(MN) time.
	// Using first cell of each row and column as marker. 0 is the value
	void setZeroes2(vector<vector<int>>& matrix) {
		const int m = matrix.size(), n = matrix[0].size();
		bool isColumn0Zero = false;

		for (int i = 0; i < m; ++i) {
			// At the end, whole column 0 need to be zero
			if (matrix[i][0] == 0) isColumn0Zero = true;

			for (int j = 1; j < n; ++j) {
				if (matrix[i][j] == 0) {
					matrix[i][0] = 0;
					matrix[0][j] = 0;
				}
			}
		}

		// Use first element of both row and column to check if need to put zero
		for (int i = 1; i < m; ++i) {
			for (int j = 1; j < n; ++j) {
				if (matrix[i][0] == 0 || matrix[0][j] == 0) matrix[i][j] = 0;
			}
		}

		// If first element at row 0 is 0, whole row is 0
		if (matrix[0][0] == 0)
			for (int j = 0; j < n; ++j) matrix[0][j] = 0;

		if (isColumn0Zero)
			for (int i = 0; i < m; ++i) matrix[i][0] = 0;
	}
};