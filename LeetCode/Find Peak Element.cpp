#include <vector>
using namespace std;

//https://leetcode.com/problems/find-peak-element/
/*
 * 	This is a binary search problem.
 *
 * 	Given a middle element from possible range [l, r], say at index m.
 *  We check whether it is a peak element or not. If not, there are several possible cases:
 *  	>	HI X HI
 *  	>	HI X LO
 *  	>	LO X HI
 *
 *  In this cases, we will always narrow the range to search towards the side with higher element. This is valid because
 *  by following the trend of going higher, we will eventually reach the peak.
 */

class Solution {
public:
	int findPeakElement(vector<int>& nums) {
		const int len = nums.size();
		int l = 0, r = len - 1;
		while (l < r) {
			int mid = l + (r - l) / 2;

			if (nums[mid] > nums[mid + 1])	// Current element is larger. Next element is smaller
				r = mid;
			else
				l = mid + 1;
		}
		return l;
	}
};