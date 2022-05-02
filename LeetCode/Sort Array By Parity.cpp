#include <vector>
using namespace std;


//https://leetcode.com/problems/sort-array-by-parity/
/*
 * 	Two pointer approach. Note that the approach can start from the start, or each pointer at each ends
 */


class Solution {
public:
    vector<int> sortArrayByParity(vector<int>& nums) {
        int l = 0, r = nums.size() - 1;

        while (l < r) {
            if (nums[l] % 2) ++l;
            else swap(nums[l], nums[r--]);
        }
        return nums;
    }
};