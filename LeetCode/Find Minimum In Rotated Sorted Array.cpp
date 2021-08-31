#include <vector>
using namespace std;

//https://leetcode.com/problems/find-minimum-in-rotated-sorted-array/
/*
 * 	This is a binary search problem. We basically has to search for the head of the sorted array, which has the smallest value.
 *
 * 	-	If the array is not rotated, then the highest value will be at the end, and the lowest value will be at the start.
 *
 *  Every iteration while l < r, obtain the middle value. There can be two cases:
 * 
 *      - If nums[mid] < nums[r], that means from mid to r, everything is in order. mid could potentially be the smallest element, but not anything
 *        between mid+1 to r. Narrow the search range to [l, mid]
 * 
 *      - If nums[mid] > nums[r], that means somewhere from mid to r contians the smallest element that causes this out of order. Therefore narrow
 *        the search range to [mid+1, r]
 * 
 */


class Solution {
public:
    int findMin(vector<int>& nums) {
        int l = 0, r = nums.size() - 1;

        // Not rotated, or simply rotated back to original sorted form
        if (nums[l] < nums[r]) return nums[l];

        // Binary search for the start of sorted array
        while (l < r) {
            int mid = l + (r - l) / 2;
            if (nums[mid] < nums[r])
                r = mid;
            else
                l = mid + 1;
        }
        return nums[l];
    }
};