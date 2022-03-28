#include <vector>
using namespace std;

//https://leetcode.com/problems/search-in-rotated-sorted-array-ii/
/*
 * 	This is a follow up binary search problem.
 *
 * 	Given a sorted array with duplicated but rotated, find if element exists in the array in O(log N) time.
 *
 * 	Every middle element that we choose, it can be either of follows:
 * 		>	Middle element is larger than left element. That means array from the left...mid is sorted
 * 			-	If the target element is in [left, mid), narrow range to [left, mid)
 * 			-	Otherwise target element must only be in (mid, right]
 *
 * 		>	Middle element is smaller than left element. This means array from left...mid is NOT sorted, pivot point
 * 			is there somewhere. The complement: mid...right is true
 * 			-	If the target element is in (mid, right], narrow range to (mid, right]
 * 			-	Otherwise target element msut only be in [left, mid)
 *
 * 		>	Middle element is same as left element. We really can't determine if which part of the array is sorted now.
 * 			Eg: 3,3,3,3,3,1 - Right side is not sorted
 * 				3,1,3,3,3,3 - Left side is not sorted
 * 			What we can do is know that since the same element is grouped in the very same in original array
 * 			Eg: (1,3,3,3,3,3), eliminating one of them isn't going to hurt. Thus shift left pointer by 1 to narrow
 * 			search space by 1.
 *
 * 	This decision however causes the worst case time complexity to O(N), which then a linear search is much better
 */

class Solution {
public:
    bool search(vector<int>& nums, int target) {
		const int len = nums.size();
		int left = 0, right = len - 1;

		while (left < right) {
			int mid = left + (right - left) / 2;

			//	If target is found
			if (nums[mid] == target) return true;

			//	Middle element larger than left element. [Left, Mid] is sorted
			if (nums[mid] > nums[left]) {
				//	If the target element is indeed in the [Left, Mid]
				if (nums[left] <= target && nums[mid] > target) right = mid - 1;
				else left = mid + 1;
			}
			//	Middle element is smaller than left element. [Mid, Right] is sorted
			else if (nums[mid] < nums[left]) {
				//	If the target element is indeed in the [Mid, Right]
				if (nums[mid] < target && nums[right] >= target) left = mid + 1;
				else right = mid - 1;
			}
			//	Else the middle element is same as start. Unable to detect
			else left++;
		}

		//	The element is never found. Return false
		return nums[left] == target;
    }
};