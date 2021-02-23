#include <vector>
using namespace std;

//https://leetcode.com/problems/search-a-2d-matrix-ii/
/*
 * 	Once you see sorted property, binary search idea immediately comes to mind. However, binary searching in 2D
 * 	is not as easy.
 *
 * 	Let's think about binary searching a row first. If the target is indeed in a row, we would already found and
 * 	return true. If not, it would be in a position where everything to the left is smaller than target, and
 * 	everything to the right is larger than the target.
 *
 * 	Now. Recall another property. Down a column it is also sorted! Therefore, essentially after binary searching a
 * 	row, if the target is not found, the area is seperated into 4 areas:
 *
 *
 * 		  smaller than smaller 		|  smaller than larger
 *
 * 			<------SMALLER VALS-----X-------LARGER VALS---->
 *
 *		  larger than smaller  		|  larger than larger
 *
 *	Now ask yourself, where can target value be potentially found? Answer is:
 *		>	"Larger than smaller" area
 *		>	"Smaller than larger" area
 *
 *	Thus, now we have 2 subarea to find! A recursion is great at this!
 *
 *	Time Complexity:
 *	See the above area seperated into two. Essentially every search, the area is divided into half. So, the time complexity is
 *	estimated logarithm of the grid area
 *
 *	===============================================================================================
 *
 *	Now the ingenious idea is that, if we start from the rightmost upper corner, we can always eliminate one row or one column
 *	each time!
 *	If the value is larger, then the target could not be down the column!
 *	If the value is smaller, then the target could not be across the row!
 *
 *	Time complexity for this is then O(M+N). Worst case we go through all the rows/ cols once
 *
 */


class Solution {
public:
	bool searchMatrix(vector<vector<int>>& matrix, int target) {
		return recurse(matrix, 0, matrix.size() - 1, 0, matrix[0].size() - 1, target);
	}

	bool recurse(vector<vector<int>>& matrix, int rleft, int rright, int cleft, int cright, int target) {
		if (rleft >= matrix.size() || rright < 0 || cleft >= matrix[0].size() || cright < 0
			|| rleft > rright || cleft > cright) return false;
		int row = rleft + (rright - rleft) / 2;

		int l = cleft, r = cright;
		while (l < r) {
			int m = l + (r - l) / 2;
			if (matrix[row][m] < target) l = m + 1;
			else r = m;
		}

		if (matrix[row][l] == target) return true;
		else return recurse(matrix, rleft, row - 1, l, cright, target) || recurse(matrix, row + 1, rright, cleft, l, target);
	}





	bool searchMatrix2(vector<vector<int>>& matrix, int target) {
		const int row = matrix.size(), col = matrix[0].size();

		int r = 0, c = col - 1;

		while (r < row && c >= 0) {
			if (matrix[r][c] == target) return true;
			else if (matrix[r][c] > target) --c;
			else ++r;
		}
		return false;
	}

};
