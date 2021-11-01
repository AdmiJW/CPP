#include <vector>
using namespace std;

//https://leetcode.com/problems/surrounded-regions/

/*
 * 	This is a DFS/BFS problem.
 *
 * 	Any 'O' that is not at the boundary itself, and does not connect to any 'O' located at boundary, will be converted to 'X'
 * 	at the end.
 * 	Therefore, the objective is to identify for every 'O' in the board, is it connected to any 'O' at boundary (or it is at
 * 	boundary itself?)
 *
 * 	We can approach this in 2 ways:
 *	1.	Once found a 'O' in the matrix, we perform dfs/bfs to locate all 'O' connected to it, then determine if it is connected
 *		to 'O' at boundary. If it does, ignore the group. If it does not, then convert all of them into 'X'
 *
 *	2. 	Instead of finding out a group is connected to 'O' at boundary or not, we actively ELIMINATE those groups that are
 *		indeed connected to 'O' at boundary.
 *
 *
 *	Method 2 is much more easier and readable to implement:
 *		- Iterate through first column, first row, last column and last row.
 *		- If it contains a 'O':
 *			- Mark it as some arbitrary character, like '!' to indicate that this 'O' is connected to boundary (Not convertable)
 *			- DFS/BFS on its 4 sides to look for more 'O' to eliminate.
 *
 *		- Once finished, the board will have 'X', 'O' and '!'.
 *			'!' is the original 'O' but is connected to boundary
 *			'O' is the ones that are not connected to any 'O' at boundary
 *			'X'
 *
 *		- Run a final iteration through the whole board:
 *			- Convert '!' to 'O'
 *			- Convert 'O' to 'X'
 */

class Solution {
public:

    void solve(vector<vector<char>>& board) {
        const int r = board.size(), c = board[0].size();
        vector<vector<bool>> visited(r, vector<bool>(c, 0));

        // First column
        for (int i = 0; i < r; ++i) markAsNotConvertable(board, i, 0);
        // Last column
        for (int i = 0; i < r; ++i) markAsNotConvertable(board, i, c-1);
        // First row
        for (int i = 0; i < c; ++i) markAsNotConvertable(board, 0, i);
        // Last row
        for (int i = 0; i < c; ++i) markAsNotConvertable(board, r-1, i);

        // All '!' need to convert back into 'O'. All 'O' will become 'X'
        for (int i = 0; i < r; ++i) {
            for (int j = 0; j < c; ++j) {
                if (board[i][j] == '!') board[i][j] = 'O';
                else if (board[i][j] == 'O') board[i][j] = 'X';
            }
        }
    }


    void markAsNotConvertable(vector<vector<char>>& board, int r, int c) {
        // Out of bounds
        if (r == -1 || r == board.size() || c == -1 || c == board[0].size()) return;
        // Not 'O'
        if (board[r][c] != 'O') return;

        board[r][c] = '!';

        markAsNotConvertable(board, r - 1, c);
        markAsNotConvertable(board, r + 1, c);
        markAsNotConvertable(board, r, c - 1);
        markAsNotConvertable(board, r, c + 1);
    }

};