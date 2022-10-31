#include <vector>
using namespace std;

// https://leetcode.com/problems/toeplitz-matrix/
/*
 * This is a matrix problem.
 *
 * If the elements that run across the diagonal must be same, we could easily run iterations
 * on diagonals one by one, but is there a property to be observed?
 *
 * One good property to observe is: If the matrix is indeed toeplitz, then all previous diagonal
 * elements [i-1][j-1] must match the one at [i][j], unless out of bounds.
 *
 * This way of solving the problem is much more elegant
 */



class Solution {
public:
    bool isToeplitzMatrix(vector<vector<int>>& matrix) {
		for (int i = 1; i < matrix.size(); ++i) {
			for (int j = 1; j < matrix[0].size(); ++j) {
				if (matrix[i][j] != matrix[i - 1][j - 1]) return false;
			}
		}
		return true;
    }
};