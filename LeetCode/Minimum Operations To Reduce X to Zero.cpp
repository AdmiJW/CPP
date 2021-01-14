#include <vector>
using namespace std;

//https://leetcode.com/problems/minimum-operations-to-reduce-x-to-zero/
/*
 * 	This is a Binary Search | Two pointers greedy sliding window problem.
 *
 * 	For Brute force approach, we would try summing up elements from left to right. On each element added,
 * 	start an iteration from the right to find out if there is also a sum which makes up to x.
 *
 * 	Time complexity is O(N^2) with constant space. Can we do better?
 *
 * 	-------------------------------
 *
 * 	It is obvious we need extra information to solve the problem. Say, if we already have the prefix sum array
 * 	beforehand.
 * 	Then it means now when we summing up the elements from right to left (More convenient), we
 * 	can retrieve the other side's sum using binary search.
 *
 * 	This way time complexity is reduced to O(N log N), but uses extra space O(N)
 *
 * 	----------------------------------
 *
 * 	The optimized solution comes with the idea of this:
 *
 * 	First sum up every elements from left to right. Along the way if there is matching x, record it.
 *
 * 	Then, We will start the iteration from right. While the left part's sum is greater than required value from the
 * 	right, start retracting the sum by moving back to the left. Repeat while the left sum is greater than the
 * 	required value.
 *
 * 	The idea is:	From right to left, value is always increasing (Since it is summing).
 * 					That means value required by right will always be decreasing.
 * 					Therefore it is no problem to be retracing the left window.
 */

class Solution {
public:
	int minOperations(vector<int>& nums, int x) {
		const int len = nums.size();
		int cumulative = 0;

		//	Creation of Prefix Sum Array
		vector<int> prefixSum(len + 1, 0);
		for (int i = 0; i < len; ++i)
			prefixSum[i + 1] = nums[i] + prefixSum[i];

		//	If we only pop from left side.
		int res = binarySearch(prefixSum, x);

		//	Start summing from the right side
		for (int i = 1; i <= len; ++i) {
			cumulative += nums[len - i];

			int search = binarySearch(prefixSum, x - cumulative);
			//	Invalid when: 1. Not found 2. Required range overlap with right subarray
			if (search == INT32_MAX || search > len - i) continue;
			//	Otherwise a valid value! Record
			res = min(res, i + search);
		}

		return res == INT32_MAX ? -1 : res;
	}

	int binarySearch(vector<int>& prefixSum, int val) {
		int left = 0, right = prefixSum.size() - 1;

		while (left < right) {
			int mid = left + (right - left) / 2;
			if (prefixSum[mid] < val)
				left = mid + 1;
			else
				right = mid;
		}

		return prefixSum[left] == val ? left : INT32_MAX;
	}



	//	Two pointers, sliding window method
	int minOperations2(vector<int>& nums, int x) {
		const int len = nums.size();
		int res = INT32_MAX;
		int lSum = 0, lPt = len - 1;

		//	Fill up to the right first
		for (int i = 0; i < len; ++i) {
			lSum += nums[i];
			if (lSum == x) res = i + 1;
		}

		int rSum = 0;
		//	Filling up to the left, while attempting to search left cumulative.
		for (int i = len - 1; i >= 0; --i) {
			rSum += nums[i];

			//	If left pointer overlaps, or left sum is greater than required value
			while (lPt == i || (lPt >= 0 && lSum > x - rSum)) {
				lSum -= nums[lPt];
				--lPt;
			}

			//	Check leftSum
			if (lSum == x - rSum)
				res = min(res, lPt + 1 + len - i);
		}

		return res == INT32_MAX ? -1 : res;
	}
};