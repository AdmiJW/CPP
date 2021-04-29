#include <vector>
using namespace std;

//https://leetcode.com/problems/find-first-and-last-position-of-element-in-sorted-array/
/*
 * 	This is a binary search problem.
 *
 * 	When talking about sorted arrays, immediately the idea of binary search should come to mind. So efficient
 *
 * 	First and foremost, you can always perform linear scan. However it scales linearly with input size.
 * 	If size is 10000, you need 10000 iterations, whereas in binary search you can use less than 100 iterations
 *
 * 	For binary search, you can set the conditions so that the search is left biased or right biased. This helps us
 * 	in finding out the starting point of the group, and the ending point of the group easily.
 */

class Solution {
public:
	//	Linear Search solution
	vector<int> searchRange(vector<int>& nums, int target) {
		int left = INT32_MAX, right = INT32_MIN;
		for (int i = 0; i < nums.size(); ++i) {
			if (nums[i] == target) {
				left = min(left, i);
				right = max(right, i);
			}
		}

		if (left == INT32_MAX) return { -1,-1 };
		return { left, right };
	}


	//	Binary Search solution
	vector<int> searchRange2(vector<int>& nums, int target) {
		const int len = nums.size();
		if (!len || nums[0] > target || nums[len - 1] < target) return { -1,-1 };
		int left;

		//	Leftmost binary search: If mid >= target, right = mid, bias to left as possible
		int l = 0, r = len - 1;
		while (l < r) {
			int mid = l + (r - l) / 2;	//	Mid value bias to left
			if (nums[mid] >= target)
				r = mid;
			else l = mid + 1;
		}
		//	Check if val even exists in the array
		if (nums[l] != target) return {-1, -1};
		left = l;

		//	Rightmost binary search: If mid <= target, left = mid. Bias to right as possible
		//	Start searching where left starts at last search result.
		r = len - 1;
		while (l < r) {
			int mid = (l + (r - l) / 2) + 1;	//	Mid value bias to right
			if (nums[mid] <= target)
				l = mid;
			else r = mid - 1;
		}

		return { left,r };
	}
};