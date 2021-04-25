#include <vector>
using namespace std;

//https://leetcode.com/problems/rotate-image/
/*
 * 	This is an array trick problem
 *
 * 	Try to rotate the matrix layer by layer, like an onion.
 * 	The offset indicates which layer we are trying to rotating. Offset = 0 means the outermost layer
 *
 * 	In each layer, since we have to do it inplace, each element rotating must make a full cycle to ensure
 * 	no inforamtion is lost.
 * 	Eg if I have matrix of size 2, then to rotate, start at (0,0), then (0,1), then (1,1), then (1,0). No information
 * 	is lost
 *
 * 	The elements that has to be rotated in that layer is the ones in column less than (length - offset - 1)
 * 	Eg: Square matrix of size 3x3. Then in outermost layer, element at col 0 and col 1 must be rotated. the rest will
 * 	automatically be rotated due to rotation at previous element.
 *
 * 	From a position (r,c), we map to the new position via (r,c)->(c, l - r - 1) where l is length of matrix
 *
 * 	Once done, recurse (or iterate) into deeper 1 level. The layer cannot exceed or equal (length / 2)
 *
 * 	-----------------------------------
 *
 * 	In reality however, rotation is more likely to done via transformation matrix of rotation. Since each images are simply
 * 	a point (x,y), it is simply a matrix multiplication with row 2.
 *
 * 	----------------------------------
 * A more elegant yet hard to observe idea, is to perform transpose, then reverse rows
 * The reason why this works, is because from earlier formula,
 * 			(r,c)-> (c, l - r - 1)
 *
 * 	First, transposing flips r and c. So position becomes (c,r)
 * 	Now, reversing the row will cause the second element to become l - e - 1. Hey! That's what we talking about!
 * 			(c, l - r - 1)
 */

class Solution {
public:
	void rotate(vector<vector<int>>& matrix) {
		rotate(matrix, 0);
	}

	void rotate(vector<vector<int>>& matrix, int offset) {
		if (offset >= matrix.size() / 2) return;
		for (int i = offset; i < matrix.size() - offset - 1; ++i) {
			int temp = 0, r = offset, c = i;
			for (int j = 0; j <= 4; ++j) {
				int val = matrix[r][c];
				matrix[r][c] = temp;
				temp = val;

				int oldr = r;
				r = c;
				c = matrix.size() - oldr - 1;
			}
		}
		rotate(matrix, offset + 1);
	}


	void rotate2(vector<vector<int>>& matrix) {
		//	Transposing
		for (int i = 0; i < matrix.size(); ++i) {
			for (int j = 0; j < i; ++j) {
				int temp = matrix[i][j];
				matrix[i][j] = matrix[j][i];
				matrix[j][i] = temp;
			}
		}

		//	Reversing row
		for (int i = 0; i < matrix.size(); ++i) {
			for (int j = 0; j < matrix.size() / 2; ++j) {
				int temp = matrix[i][j];
				matrix[i][j] = matrix[i][matrix.size() - j - 1];
				matrix[i][matrix.size() - j - 1] = temp;
			}
		}
	}
};