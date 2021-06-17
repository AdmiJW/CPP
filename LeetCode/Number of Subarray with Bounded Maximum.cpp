#include <vector>
using namespace std;

//https://leetcode.com/problems/number-of-subarrays-with-bounded-maximum/
/*
 * 	This is a two pointers, array problem, which involves more on logical thinking and idea on DP itself
 *
 * 	Say we uses two pointers, left pointer l, and right pointer r.
 * 	First of all, the problem could be reduced. Think of it this way, if we can know for a fact that
 * 	the range of array in indices [l, r] is always <= right, then the problem is reduced
 * 	to finding subarrays that has max element >= left!
 *
 * 	A bit of idea here: If we encountered an element which is greater than right, then surely it cannot
 * 	form any subarray, and since it is large in magnitude, it will be considered as maximum element if
 * 	included in any subarray and thus always result in invalid subarray
 *
 * 	Now established that elements in range [l,r] is always <= right, let's see what cases we'll encounter:
 * 	Here we'll use
 *  	>	If the element is >= left, then it can form subarrays easily! In DP, we will form subarrays that
 *  		MUST end with this element.
 *  		Number of subarrays that can be formed, is ( r - l + 1 ), since i can form length 1, length 2 up to
 *  		length N subarray that includes this last element
 *
 *  	>	If the element is < left, then it must be connected to the closest IN RANGE element in the range
 *  		[l,r].
 *  		For example, 3 <= x <= 5 and our progress is currently [1,3,5,2,1,1] <-- (We are at last '1')
 *
 *  		To form subarray using the last '1', it must include the CLOSEST in range element, which is '5'.
 *  		Thus, if we know the index of latest in range element, say i, such that l <= i <= r, then
 *  		the number of subarray that can be formed is of course,
 *
 *  			i - l + 1
 *
 *		>	If we encounter an element that is > right, simply reset our range such that l = r + 1, and latest
 *			in range element to be r (Because if next element is < left, it will be i - l + 1 which is 0)
 */

class Solution {
public:
	int numSubarrayBoundedMax(vector<int>& nums, int left, int right) {
		int latestInRange = -1, res = 0;
		for (int l = 0, r = 0; r < nums.size(); ++r) {
			if (nums[r] > right) {
				l = r + 1;
				latestInRange = r;
			}
			else if (nums[r] < left) {
				res += latestInRange - l + 1;
			}
			else {
				latestInRange = r;
				res += r - l + 1;
			}
		}
		return res;
	}
};