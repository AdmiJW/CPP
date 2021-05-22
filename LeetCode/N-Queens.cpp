#include <vector>
#include <string>
using namespace std;

//https://leetcode.com/problems/n-queens/
/*
 * 	Of course. N-Queens is a classical problem to practice for backtracking, which is a particular topic in recursion.
 * 	There are various slightly different approaches to solve it, but the core algorithm stays: Backtracking.
 *
 * 	The brute force solution would generate all possible placements of queens, even invalid ones, and leave until all queens
 * 	exhausted only to check if board is valid.
 * 	In this approach, we have N^2 choices to put first queen, then N^2 - 1 choices to put second one and so on...
 * 	This leads to complexity of N^2N which is too slow
 *
 * 	A better way is thru backtracking, eliminating many possibilities of invalid states
 *
 * 	====================================================================================
 *
 * 	In my approach, I use a 2D array of grid to represent the board states.
 * 	If element is -1, it represents presence of queen.
 * 	Otherwise, it represents number of queens blocking that grid. If 0, means empty grid and available to place queen there.
 *
 * 	Every recursion call will have a counter. If counter hits 0, means all queen is exhausted, an unique solution is produced
 * 	so add to result.
 * 	Also, if the recursion call is on the cell that is out of bounds (row exceeded), return
 *
 * 	Start from topleft corner. Every recursion call, I have two choices: to place queen or not to place.
 * 	If I were to place it:
 * 		For the grid, block every cell that is horizontal, vertical, diagonal and anti-diagonal to the queen by adding 1 to the cells
 * 		Then, place queen to the grid by setting -1
 * 		Recurse into the next grid.
 * 		Once returned, undo the changes above. Set grid to 0, and -1 to all the blocked cells.
 *
 * 	If I were not to place it, simply recurse into next grid without doing anything
 *
 * 	-------------------------------------------------------------------------------------------------------------
 *
 * 	The approach above have certain optimizations to be done:
 * 	>	Instead of blocking cells horizontally, I could simply choose to directly recurse into beginning of next row.
 *
 * 	>	There is a property of 'diagonal sum'. For diagonal \, the difference of their i and j index is always same.
 * 		The same goes for anti diagonal /, except it is sum of their i and j index.
 * 		Using this property, we could eliminate the loop needed for blocking cells. Use 3 SEPARATE (Do not combine!)
 * 		Sets (or boolean array) to indicate whether a queen is already blocking that index.
 *
 * 		For column, it is as direct as it is. col[1] = true means column 1 is blocked
 *		For diagonal, diag[1] = true means any grid where i-j = 1 is already blocked
 *		For antidiagonal, antidiag[1] = true means any grid where i+j = 1 is already blocked.
 *
 *	------------------------------------------------------------------------------------------------------------
 *
 *	Time complexity is O(N!) because for the first row, we have N choices to put queen, then into next row, is N-1 choices,
 *	then N-2 choices... until 1. Thus it is O(N!)
 *
 *	Space complexity is O(N^2). The board I used is O(N^2) in size. The depth recursion call goes up to O(N) only since
 *	when a queen is placed, it goes to next row. Number of rows is only N.
 */

class Solution {
public:
	vector<vector<string>> solveNQueens(int n) {
		vector<vector<string>> res;
		vector<vector<int>> grid(n, vector<int>(n, 0));
		backtrack(0, 0, n, grid, res);
		return res;
	}

	void backtrack(int row, int col, int n, vector<vector<int>>& grid, vector<vector<string>>& res) {
		const int len = grid.size();
		//	All queens has been placed. Add the board to result and return
		if (n == 0) {
			vector<string> board;
			for (auto& r : grid) {
				string s = "";
				for (int e : r) s += (e == -1) ? 'Q' : '.';
				board.push_back(s);
			}
			res.emplace_back(board);
			return;
		}
		//	Out of bound. Return immediately.
		if (row >= len) return;

		//	Otherwise, we can either choose to place queen here (if available), or not to.
		//	Either way, we proceed to next grid (or next row if is last column)
		int nextCol = (col + 1 < len) ? col + 1 : 0;
		int nextRow = row + (col + 1) / len;

		//	If able to place queen, let's do it. Remember to close out all queen's attack range:
		//	Significant blocking we need to do is:
		//	To right ->, To below V, diagonally both \ and /
		if (grid[row][col] == 0) {
			grid[row][col] = -1;
			//	No need to block horizontally since I directly jump to next row
			//	Block vertically
			for (int i = row + 1; i < len; ++i) grid[i][col] += 1;
			//	Block diagonally
			for (int i = row + 1, j = col + 1; i < len && j < len; ++i, ++j) grid[i][j] += 1;
			for (int i = row + 1, j = col - 1; i < len && j >= 0; ++i, --j) grid[i][j] += 1;
			//	Recurse. Small optimization is to directly jump to beginning of next row.
			backtrack(row + 1, 0, n - 1, grid, res);
			//	Backtrack. Retract the blockages
			for (int i = row + 1; i < len; ++i) grid[i][col] -= 1;
			for (int i = row + 1, j = col + 1; i < len && j < len; ++i, ++j) grid[i][j] -= 1;
			for (int i = row + 1, j = col - 1; i < len && j >= 0; ++i, --j) grid[i][j] -= 1;
			grid[row][col] = 0;
		}

		//	Proceed without placing queens
		backtrack(nextRow, nextCol, n, grid, res);
	}
};