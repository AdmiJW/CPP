#include <vector>
using namespace std;

//https://leetcode.com/problems/range-addition-ii/
/*
 * This is an array problem.
 *
 * Given operation in the form of [lenx, leny], the grid where topleft = (0,0) until bottom right (lenx, leny)
 * will be updated by incrementing 1.
 *
 * This means, whatever operation is done, the final matrix where the maximum elements are, must stick to
 * the top left corner. We just need to determine how large the square of maximum elements are.
 *
 * And this is done easily by finding the minimum span in the x direction and y direction.
 * At the end, you know the dimension of each axis, find the number of elements in that maximum element rectangle
 * by multiplying them
 */

class Solution {
public:
	int maxCount(int m, int n, vector<vector<int>>& ops) {
		int spanx = m;
		int spany = n;

		for (auto& op : ops) {
			if (!op[0] || !op[1]) continue;
			spanx = min(op[0], spanx);
			spany = min(op[1], spany);
		}

		return spanx * spany;
	}
};