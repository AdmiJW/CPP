#include <vector>
#include <algorithm>
using namespace std;

//https://leetcode.com/problems/minimum-moves-to-equal-array-elements-ii/
/*
 * 	This is a Math problem.
 *
 * 	Turns out, finding the median and summing the distances between each element and median, is the optimal
 * 	solution. But how does it make sense?
 *
 * 	The idea is, by sorting the array, we can access the kth maximum and kth minimum element immediately.
 * 	Say the maximum and minimum is just at the tail and head of array after sorting. The second maximum and
 * 	second minimum is at the index 1 and N-2 respectively.
 *
 * 	Now, it shall be agreed on that given a maximum and minimum element of array, the final number that all elements
 * 	are reduced to, C, lies between [min, max].
 *
 * 	Therefore, to move min to C, steps required are (C - min)
 * 	Similarly, to move max to C, steps required are (max - C)
 * 	Thus the total steps are, (C - min) + (max - C) = (max - min)!
 *
 * 	And note this: we can pick any point in range [min,max], and it still have the same distance for both elements:
 * 	If I pick min as pivot, then operations needed = (max - min)
 * 	If I pick max as pivot, then operations needed is also abs(min-max) = (max - min)
 * 	Thus safely discard the max and min point because the point selected doesn't matter, and we're left with problem
 * 	of size N-2!
 * 	That, ladies and gentlemen, is how median works! Finding the middle value in sorted array
 *
 * 	Thus we can easily narrow down the array fairly quickly. In sorted array, keep picking up the nth maximum and minimum
 * 	pairs, and find their difference.
 *
 *
 * 	Note:
 * 	 minimized absolute differences => median;
 * 	 minimized squared differences => mean.
 */

class Solution {
public:
	//	Finding Median Solution
	int minMoves2(vector<int>& nums) {
		const int len = nums.size();
		//	Try to find the median. Median is great because it is not affected by outliers, like
		//	[1,1,1,1,1,1000]
		sort(nums.begin(), nums.end());
		//	A quick way to find median is via this way:
		//	If len is odd (2n+1), idx1 and idx2 are same
		//	If even otherwise, surely idx1 and idx2 will different, and so happens to be the middle value
		int idx1 = len / 2;
		int idx2 = (len - 1) / 2;
		int median = (nums[idx1] + nums[idx2]) / 2;

		int dist = 0;
		for (int n : nums)
			dist += abs(median - n);
		return dist;
	}


	//	Meeting point problem (Median in another form)
	//	Idea is at any two extreme points, the minimum step lies between them
	int minMoves2_2(vector<int>& nums) {
		int l = 0, r = nums.size() - 1;
		int dist = 0;
		sort(nums.begin(), nums.end());
		while (l < r) {
			dist += abs(nums[r] - nums[l]);
			++l;
			--r;
		}
		return dist;
	}
};