#include <vector>
using namespace std;

//https://leetcode.com/problems/game-of-life/
/*
 *  This is a matrix / 2D array problem
 *
 * 	For the checking part, we can perform a checking normally to see if a cell shall be converted to dead or alive
 *
 * 	However, the core of the problem is about updating the array. We have to realize we cannot directly convert
 * 	each value to 0 or 1, as
 * 		>	One generation goes to another SIMUlTANEOUSLY, meaning when we overwrite one value, the information
 * 			about previous value is lost, and other grids that are yet to be checked are dependent to it. If we
 * 			do like that, it will lead to logical error
 *
 * 	Thus, we have to somehow update the values, while keeping the information of the previous matrix state.
 *
 * 	-----------------------------------------------------------
 *
 * 	A direct solution is to create a brand new array just for recording the new values. After that, overwrite the values
 * 	back into the old array and return
 *
 * 	This takes O(MN) space, and will be expensive if the array is large.
 *
 * 	-------------------------------------------------------------
 *
 * 	This leads to two pass solution (Although the above is also two pass). Somehow, we have to keep the information
 * 	that this previous grid is 1 or 0, while having the information that this grid has to be updated or not.
 *
 * 	My idea is,
 * 		>	Negative value indicates previously, grid is DEAD
 * 		>	Positive value indicates previously, grid is ALIVE
 * 		>	The magnitude indicates how many neighbors are alive.
 *
 * 	With this, in second pass, i can first check for the sign, then check if the value can be converted to dead or alive,
 * 	without relying on neighbors (Since it is done in first pass!)
 *
 * 	A little problem with this is the ambiguous property of zero 0. Is it positive or negative?
 * 	To solve this, we can simply offset the number of neighbors by 1, so the numbers are never 0.
 *
 *
 * 	Also, it can be further decoded into
 * 		>	-1 indicates previously is DEAD, and shall NOT CHANGE
 * 		>	1 indicates previous is ALIVE, and shall NOT CHANGE
 * 		>	-2 indcates previous is DEAD, and next gen will ALIVE
 * 		>	2 indicates previous is ALIVE, and next gen will DEAD
 *	The idea is exactly same.
 *
 * ------------------------------------------
 *
 * 	Extra:
 * 		>	Instead of being limited by boundaries, the top can be connected to bottom, and left and be conected
 * 			to right. Use modulo for that
 *
 * 		>	Say if we have a infinite board (VERY LARGE board), it's more efficient to use a Set and keep the active
 * 			cells instead of traversing the matrix
 */

class Solution {
public:

	//	Normal, O(MN) space complexity solution
	void gameOfLife(vector<vector<int>>& board) {
		const int row = board.size();
		const int col = board[0].size();

		vector<vector<int>> res(row, vector<int>(col));

		for (int i = 0; i < row; ++i) {
			for (int j = 0; j < col; ++j) {
				int s = findSumNeighbor(board, i, j);
				if (board[i][j])
					res[i][j] = s == 2 || s == 3;
				else
					res[i][j] = s == 3;
			}
		}

		for (int i = 0; i < row; ++i) {
			for (int j = 0; j < col; ++j)
				board[i][j] = res[i][j];
		}
	}


	// Using two pass, O(1) in place solution
	void gameOfLife2(vector<vector<int>>& board) {
		const int row = board.size();
		const int col = board[0].size();

		for (int i = 0; i < row; ++i) {
			for (int j = 0; j < col; ++j) {
				int s = findSumNeighbor(board, i, j) + 1;
				board[i][j] = (board[i][j] ? 1 : -1) * s;
			}
		}

		for (int i = 0; i < row; ++i) {
			for (int j = 0; j < col; ++j) {
				if (board[i][j] < 0)
					board[i][j] = -board[i][j] - 1 == 3;
				else
					board[i][j] = board[i][j] - 1 == 2 || board[i][j] - 1 == 3;
			}
		}
	}



	int findSumNeighbor(vector<vector<int>>& board, int r, int c) {
		const int row = board.size();
		const int col = board[0].size();

		int s = r - 1 >= 0 && c - 1 >= 0 && board[r - 1][c - 1] > 0 ? 1 : 0;
		s += r - 1 >= 0 && board[r - 1][c] > 0 ? 1 : 0;
		s += r - 1 >= 0 && c + 1 < col && board[r - 1][c + 1] > 0 ? 1 : 0;
		s += c - 1 >= 0 && board[r][c - 1] > 0 ? 1 : 0;
		s += c + 1 < col && board[r][c + 1] > 0 ? 1 : 0;
		s += r + 1 < row && c - 1 >= 0 && board[r + 1][c - 1] > 0 ? 1 : 0;
		s += r + 1 < row && board[r + 1][c] > 0 ? 1 : 0;
		s += r + 1 < row && c + 1 < col && board[r + 1][c + 1] > 0 ? 1 : 0;

		return s;
	}

	//	Use this instead if you want the windows to be not bounded by array size (AKA the rightmost map loops back to left)
	int findSumNeighborUnbounded(vector<vector<int>>& board, int r, int c) {
		const int row = board.size();
		const int col = board[0].size();

		int s = board[(r - 1 >= 0) ? r - 1 : row - 1][(c - 1 > 0) ? c - 1 : col - 1] > 0 ? 1 : 0;
		s += board[(r - 1 >= 0) ? r - 1 : row - 1][c] > 0 ? 1 : 0;
		s += board[(r - 1 >= 0) ? r - 1 : row - 1][(c + 1) % col] > 0 ? 1 : 0;
		s += board[r][(c - 1 > 0) ? c - 1 : col - 1] > 0 ? 1 : 0;
		s += board[r][(c + 1) % col] > 0 ? 1 : 0;
		s += board[(r + 1) % row][(c - 1 > 0) ? c - 1 : col - 1] > 0 ? 1 : 0;
		s += board[(r + 1) % row][c] > 0 ? 1 : 0;
		s += board[(r + 1) % row][(c + 1) % col] > 0 ? 1 : 0;

		return s;
	}
};


