#include <vector>
using namespace std;

//https://leetcode.com/problems/search-insert-position/
/*
 * 	A simple binary search problem. At the end of the binary search we have to check if the index element is less than the target to insert.
 * 	If yes, then we have to insert it after the element, else, this element has to be "pushed" to the right, and the target is inserted in
 * 	this position
 */

class Solution {
public:

    int searchInsert(vector<int>& nums, int target) {
        int l = 0, r = nums.size() - 1;

        while (l < r) {
            int mid = l + (r - l) / 2;
            
            if (nums[mid] >= target) r = mid;
            else l = mid + 1;
        }

        return l + (nums[l] < target);
    }

};