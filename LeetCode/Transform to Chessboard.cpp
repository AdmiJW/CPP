#include <vector>
using namespace std;

//https://leetcode.com/problems/transform-to-chessboard/
/*
 * This is a HARD matrix problem (Optional - Bit manipulation).
 * This problem takes great observation skills to come up with the solution.
 *
 * First of all, we can check the board if it is valid or not. The way to find out how to check is by observation:
 * Take a valid board, randomly swap the rows and columns and observe the pattern:
 *
 * 	- In a valid board, all the rows must either be same as row 1, or inverse of it.
 * 	  Eg: If row 1 is '1001', then all other rows must either be '1001' or '0110' only.
 * 	  We only need to check row, since this is auto implied to columns
 *
 * 	- The number of 0 and 1 in the first row must differ at most by 1 only. Due to rule 1, we no need to check other
 *    rows, but we do need to check first column as well. Due to this example testcase:
 *
 *    '1010'
 *    '0101'
 *    '0101'	<- Satisties Rule 1 but does not satisfy rule 2. We can detect by checking first column
 *    '0101'
 *
 * Then to detect number of swaps, we have to check the first column and row.
 *
 * 	- Start by assume the first element is '0'. Then we expect the row to be '010101...'.
 *  - Count the differences. At the end if N, the number of difference is odd, it means assumption is wrong. The first
 *    element is '1'. Retrys. Otherwise, number of swaps to make the row valid is N/2
 *  - At the end, the number of total swaps required is (Ncol + Nrow) / 2
 */

class Solution {
public:
    int movesToChessboard(vector<vector<int>>& board) {
		int n = board.size();

		// Check 1 - Each row must be inverse / same with first row
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				int sameOrDiff = board[0][0] ^ board[i][0];
				int bitIsSame = board[0][j] ^ board[i][j];
				if ((sameOrDiff ^ bitIsSame) == 1) return -1;
			}
		}
		// Check 2 - Differ by 1 in frequency of 0 and 1
		int rowOneFreq = 0, colOneFreq = 0;
		int rowOneDiff = 0, colOneDiff = 0;
		for (int i = 0; i < n; ++i) {
			rowOneFreq += board[0][i];
			colOneFreq += board[i][0];

			// We assume the first element of row/col is '0'.
			rowOneDiff += board[0][i] ^ (i % 2);
			colOneDiff += board[i][0] ^ (i % 2);
		}
		// If freq of 0 and 1 is inbalanced, then invalid board
		if ( abs(rowOneFreq - (n - rowOneFreq)) > 1) return -1;
		if ( abs(colOneFreq - (n - colOneFreq)) > 1) return -1;

		// Remember: There can only be 2 valid diffs: diff and N-diff - due to Rule 2
		// If (Diff is odd || (N even and smaller swap if first element is '1')
		rowOneDiff = (rowOneDiff % 2 != 0 || n % 2 == 0 && n - rowOneDiff < rowOneDiff) ? n - rowOneDiff : rowOneDiff;
		colOneDiff = (colOneDiff % 2 != 0 || n % 2 == 0 && n - colOneDiff < colOneDiff) ? n - colOneDiff : colOneDiff;
		return (rowOneDiff + colOneDiff) / 2;
    }
};