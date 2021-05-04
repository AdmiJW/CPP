#include <vector>
using namespace std;

//https://leetcode.com/problems/non-decreasing-array/
/*
 * 	This is a Array problem.
 *
 * 	We can only change one element to make the array non decreasing (NOT STRICTLY INCREASING! [1,1,1] returns true!)
 * 	Therefore we iterate the array. At index i, check also the next element, i+1.
 * 	If we checked element at i is greater than i+1 and haven't been previously changed any element, we know we had some
 * 	work to do.
 *
 * 	We have 2 choices - To lower the element at i, so element i becomes smaller than i+1, or
 * 					  - Raise element at i+1, so element i+1 becomes larger than i
 *
 * 	In both choices, we prefer choice 1 first, because it poses smaller risk. If we pick choice 2, what normally is a valid
 * 	non decreasing array might become invalid, like:
 * 			[3,1,2,2]		->	[3,3,2,2]
 * 	which is valid if [1,1,2,2]
 *
 * 	So, if we were to lower ith element, we want it as low as possible, means to lower it to equal i-1!
 * 	If unable to lower the ith element, we are forced to raise the i+1 element, but as low as possible, to ith element
 * 	of course!
 */

class Solution {
public:
	bool checkPossibility(vector<int>& nums) {
		bool isUsed = false;
		const int len = nums.size();
		int last = INT32_MIN;

		for (int i = 0; i < len - 1; ++i) {
			//Downfall
			if (nums[i] > nums[i + 1]) {
				//	Already manipulated previously
				if (isUsed) return false;

				//	First, try to lower current number if possible
				//	Only possible when previous number is smaller or equal to next number (small, mid, large) -> (small, small, large)
				if (nums[i + 1] >= last) nums[i] = last;
				//	Otherwise we have no choice but to raise the next number
				//	to be current element (mid, large, small) -> (mid, large, large)
				else nums[i + 1] = nums[i];
				isUsed = true;
			}
			last = nums[i];
		}
		return true;
	}
};