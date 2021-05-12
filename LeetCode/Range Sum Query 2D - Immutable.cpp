#include <vector>
using namespace std;

//https://leetcode.com/problems/range-sum-query-2d-immutable/
/*
 * 	This is a matrix problem, with dynamic programming element in it.
 * 	The purpose of stating querying many times, is to design a efficient querying algorithm,
 * 	which can be done in O(1) time by trading in space in this problem.
 *
 * 	The solution is to cache a prefixSum matrix, which the cell on grid r,c gives us the sum of elements
 * 	enclosing the area from (0,0) to (r,c).
 * 	How do we find the area from (r1,c1) to (r2,c2) then? One could just attempt to draw on blank paper,
 * 	to derive that the formula was:
 *
 * 		AREA(r2,c2) - AREA(r1-1,c2) - AREA(r2,c1-1) + AREA(r1-1,c1-1)
 */

class NumMatrix {
public:
    vector<vector<int>> prefixSum;

    NumMatrix(vector<vector<int>>& matrix) {
        const int row = matrix.size(), col = matrix[0].size();
        prefixSum = vector<vector<int>>(row, vector<int>(col,0));

        //	Construct prefixSum across each row first
        for (int r = 0; r < row; ++r) {
            prefixSum[r][0] = matrix[r][0];
            for (int c = 1; c < col; ++c)
                prefixSum[r][c] = prefixSum[r][c - 1] + matrix[r][c];
        }

        //	Then convert into query of area origin from (0,0)
        for (int r = 1; r < row; ++r) {
            for (int c = 0; c < col; ++c)
                prefixSum[r][c] += prefixSum[r - 1][c];
        }
    }

    //	Return sum of area from (0,0) to (r,c)
    int sumRegion(int r, int c) {
        if (r < 0 || c < 0) return 0;
        return prefixSum[r][c];
    }

    int sumRegion(int row1, int col1, int row2, int col2) {
        return sumRegion(row2, col2) - sumRegion(row1 - 1, col2) - sumRegion(row2, col1 - 1) + sumRegion(row1 - 1, col1 - 1);
    }
};