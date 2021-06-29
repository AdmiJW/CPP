#include <vector>
using namespace std;

//https://leetcode.com/problems/max-consecutive-ones-iii/
/*
 * This is a sliding window / Two pointers solution.
 *
 * We can flip k '0's to '1's. Given this ability with no downsides, of course we use up the k to create longest consecutive
 * ones possible!
 *
 * Using sliding window, it is very possible to solve this problem. Start from leftmost part of the array. Every iteration,
 * we'll try to include the rightmost (window's right) into our window. This is possible outcomes:
 * 		>	Latest bit is 1. No downsides. Just include and continue;
 * 		>	Latest bit is 0.
 * 				- k != 0. We can use one move to convert the newest 0 to 1. k--.
 * 				- k == 0. We had used up all the k! We have to retract the left window so that we free up one k to be used to
 * 				  convert the latest 0 to 1.
 *
 * 	Every iteration, check the window size and take the maximum. That's it
 */

class Solution {
public:
	int longestOnes(vector<int>& nums, int k) {
		const int len = nums.size();
		int res = 0;

		for (int l = 0, r = 0; r < len; ++r) {
			// Newest bit to include is 0
			if (nums[r] == 0) {
				//	Still have k left. Simply convert
				if (k > 0) k--;
				//	Otherwise, keep retracting left window until we free up one k
				else {
					while (nums[l] != 0) ++l;		//	While retraction is 1, keep going
					++l;							//	We reverted the bit 0. Thus we exclude it
				}
			}
			res = max(r - l + 1, res);
		}
		return res;
	}
};