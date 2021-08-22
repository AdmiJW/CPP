#include <vector>
using namespace std;

//https://leetcode.com/problems/sudoku-solver/
/*
 *  Solving sudoku has been a classical backtracking problem, where we attempt to put a number in a grid
 *  and see how it goes.
 *
 *  Instead of checking the row, column and group whether we can place down a number or not, use 3 9x9 boolean
 *  arrays to instead check whether a number is already present in the said row, column or group or not.
 *
 *  For each grid:
 *  	>	If we reached row index 9 (row 10), that means we already filled all grid. Return true
 *  	>	If the grid is already pre-occupied with number, proceed backtracking in next grid
 *
 * 		>	Else, attempt all number:
 * 			>	If already in row, col or group, then this number cannot be used. Next iteration
 * 			>	Try placing this number
 * 				- set boolean array
 * 				- if recursion returns true, then return true
 * 				- else, revoke action and proceed next iteration
 * 		>	The loop ended and no possible number can be placed. Return false.
 */

class Solution {
public:
    // Use 3 boolean arrays to record whether some number exist in some row or column
    // isInRow[0][1] records whether row 1 have '2' in it already or not
    vector<vector<bool>> isInRow = vector<vector<bool>>(9, vector<bool>(9, 0));
    vector<vector<bool>> isInCol = vector<vector<bool>>(9, vector<bool>(9, 0));
    vector<vector<bool>> isInGrp = vector<vector<bool>>(9, vector<bool>(9, 0));

    // Get grp number. 
    // | 0 | 1 | 2 |
    // | 3 | 4 | 5 |
    // | 6 | 7 | 8 |
    static int getGrpNo(int i, int j) {
        return (i / 3) * 3 + (j / 3);
    }

    void solveSudoku(vector<vector<char>>& board) {
        // Scan through the 9x9 sudoku board to record presence first
        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 9; ++j) {
                char c = board[i][j];

                if (c != '.') {
                    isInRow[i][c - '1'] = true;
                    isInCol[j][c - '1'] = true;
                    isInGrp[getGrpNo(i, j)][c - '1'] = true;
                }
            }
        }

        // Now do the backtracking
        backtrack(board, 0, 0);
    }

    bool backtrack(vector<vector<char>>& board, int i, int j) {
        // Once row number exceed bound, it means the board is complete
        if (i >= 9) return true;

        // Already pre-occupied. Continue to next grid
        if (board[i][j] != '.')
            return backtrack(board, i + (j + 1) / 9, (j + 1) % 9);

        // Attempt all numbers and see if it is plausible
        for (int n = 0; n < 9; ++n) {
            if (isInRow[i][n] || isInCol[j][n] || isInGrp[getGrpNo(i, j)][n])
                continue;

            isInRow[i][n] = isInCol[j][n] = isInGrp[getGrpNo(i, j)][n] = true;
            board[i][j] = (char)(n + '1');

            if (backtrack(board, i + (j + 1) / 9, (j + 1) % 9))
                return true;

            isInRow[i][n] = isInCol[j][n] = isInGrp[getGrpNo(i, j)][n] = false;
            board[i][j] = '.';
        }
        return false;
    }


};