#include <vector>
using namespace std;

//https://leetcode.com/problems/check-if-all-1s-are-at-least-length-k-places-away/
/*
 * 	Fairly simple problem.
 *
 * 	Either use a counter to count number of zeroes, and reset to 0 once it hits a 1
 * 	Or record the last index of 1, and once another 1 is hit, calculate distance
 *
 * 	Here implementation is count zeroes
 */


class Solution {
public:
	bool kLengthApart(vector<int>& nums, int k) {
		int count = INT32_MAX / 2;

		for (int i : nums) {
			if (i) {
				if (count < k) return false;
				count = 0;
			}
			else ++count;
		}
		return true;
	}
};