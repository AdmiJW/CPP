#include <vector>
using namespace std;

//https://leetcode.com/problems/valid-sudoku/
/*
 *  This is a simple HashMap problem.
 *
 *  (One can simply do brute force, which for every number, it checks for its row, column, and block, and it is valid of course)
 *
 *  We simply need to ensure that the same number does not occur in
 *  	> Same row
 *  	> Same column
 *  	> Same "block"
 *
 *  All of those can be recorded using a boolean matrix of size 9x9, same size as the sudoku itself.
 *  Say row[0][3] records whether the digit '4' (Due to 0-indexing) exists in row 1
 *  	row[8][0] records whether the digit '1' exists in row 9
 *
 *  The formula to obtain the block number given the row and column number (0-indexed) is:
 *  		3 * (r / 3) + (c / 3)
 *  where r is row index and c is column index
 */

class Solution {
public:
	bool isValidSudoku(vector<vector<char>>& board) {
		bool rows[9][9] = { {} };
		bool cols[9][9] = { {} };
		bool blocks[9][9] = { {} };

		for (int i = 0; i < 9; ++i) {
			for (int j = 0; j < 9; ++j) {
				if (board[i][j] == '.') continue;

				int n = board[i][j] - '1';
				int blockNo = 3 * (i / 3) + j / 3;

				//Validation
				if (rows[i][n] || cols[j][n] || blocks[blockNo][n]) return false;

				//Record presence
				rows[i][n] = true;
				cols[j][n] = true;
				blocks[blockNo][n] = true;
			}
		}
		return true;
	}
};
