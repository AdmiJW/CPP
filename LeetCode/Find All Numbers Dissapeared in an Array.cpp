#include <vector>
#include <algorithm>
using namespace std;

//https://leetcode.com/problems/find-all-numbers-disappeared-in-an-array/
/*
 * This is an array problem.
 *
 * Given the elements in the array can only be [1,n], we can exploit the indexing of an array itself to help us
 * solve the problem inplace with O(N) time and O(1) space
 *
 * The idea is simple: An element e should be positioned in index e-1 (Because of 0 based indexing). At the end,
 * the index i should contain element i+1. If the element is absent, then the number is dissapeared.
 *
 * Keep a pointer starting from index 0. For each element:
 * 	>	If the array element at index i already contains i+1, move pointer to i+1
 * 	>	If the array element at index arr[i]-1 already contains arr[i], also move pointer to i+1
 * 	>	Otherwise swap elements at index i and index arr[i] - 1
 *
 * Then in second pass, simply check if each index i is having i+1. If not, add i+1 to result
 */

class Solution {
public:

    // O(N) time, O(1) inplace solution
    vector<int> findDisappearedNumbers(vector<int>& nums) {
        vector<int> res;
        
        // First pass - Move nums to its position
        int pt = 0;
        while (pt != nums.size()) {
            // Continue if:
            //  - Element at ith place is value i
            //  - The element is i, but ith place already have i as its value.
            if (nums[pt] == pt + 1 || nums[nums[pt] - 1] == nums[pt]) ++pt;
            else swap(nums[pt], nums[nums[pt] - 1]);
        }

        // Second pass - If the element is not in the ith place, it is absent
        for (int i = 0; i < nums.size(); ++i) {
            if (nums[i] != i + 1)
                res.push_back(i + 1);
        }

        return res;
    }
};