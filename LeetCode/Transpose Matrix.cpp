#include <vector>
using namespace std;


//https://leetcode.com/problems/transpose-matrix/
/*
 *	Simple array problem.
 *
 *	In a matrix transposition, Say the original matrix is of size MxN, then the result matrix will be size NxM
 *	Therefore, we cannot modify the array in place. Extra space of O(MN) is required.
 *
 *	Once we have the resulting matrix initialized, simply iterate through elements of original array, applying the
 *	formula:
 *
 *		Result[j][i] = Original[i][j]
 */

class Solution {
public:
    vector<vector<int>> transpose(vector<vector<int>>& matrix) {
		vector<vector<int>> result = vector<vector<int>>(matrix[0].size(), vector<int>(matrix.size(), 0));

		for (int i = 0; i < matrix.size(); ++i)
			for (int j = 0; j < matrix[0].size(); ++j)
				result[j][i] = matrix[i][j];

		return result;
    }
};