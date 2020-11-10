
#include <vector>

//https://leetcode.com/problems/flipping-an-image/

/*
	A Array Iteration Problem

	Given 2D array of binaries, we have to reverse each row, and invert it.
	We don't actually have to carry out the operation itself. We can just reduce down the reversing and inverting
	process down.

	First, reversing a row of array usually takes O(N/2) time, which is considered O(N) as well. Use two pointers,
	one at end and one at start, flip them, and continue until to middle.
	Now, we don't really have to swap or invert them. Just observe:

	If both bits are not same, Eg 0 and 1, Once flipped they become 1, 0. If we inverse again, become 0, 1, the exactly
	same as before!
	Thus, if both bits are not same level, continue without doing anything

	If both bits are same, flipping them don't do any changes! Just we have to inverse them both.

	Now, the middle bit in a ODD-LENGTHED ARRAY may be ignored. Remember to reverse it!
*/


class Solution {
public:
	std::vector< std::vector<int> > flipAndInvertImage(std::vector< std::vector<int> >& A) {

		int width = A[0].size();

		for (std::vector<int>& row : A) {
			for (int i = 0; i < width / 2; i++) {
				if (row[i] == row[width - i - 1]) continue;
				row[i] ^= 1;
				row[width - i - 1] ^= 1;
			}
		}

		return A;
	}
};