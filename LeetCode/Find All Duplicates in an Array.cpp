#include <vector>
using namespace std;

//https://leetcode.com/problems/find-all-duplicates-in-an-array/

/*
 * 	Since the problem restricts the value to be 1 to n only, then we can exploit the property of indexing of the array itself.
 *
 * 	If we found a number, we will first check if the number at that position num - 1 is already itself. If not, then just safely swap
 * 	it with the current number.
 * 	Otherwise if the number is already there, then we know this is a duplicate. Add that to hashset or something, which takes O(N) space
 *
 * 	If don't want to use hashset, use two pass method, where first pass is just placing to respective places, ignoring swapping
 *  if the number is already in its respective place
 *
 *  ------------------------------------------------------------------------------------------------
 *
 *  Another method is using negation of the value. Since all numbers are ensured to be positive, every time we found a number,
 *  we can just replace the value at index num - 1 to its negative value. This way we know that the number at this index occurred before.
 *
 */

class Solution {
public:
    vector<int> findDuplicates(vector<int>& nums) {
        vector<int> res;

        int i = 0;
        while (i < nums.size()) {
            int n = abs(nums[i]);
            int supposedIndex = n - 1;

            if (supposedIndex == i || nums[supposedIndex] == -n) ++i;
            else if (nums[supposedIndex] == n) {
                nums[supposedIndex] *= -1;
                res.push_back(n);
                ++i;
            }
            else {
                // int temp = nums[i];
                nums[i] = nums[ supposedIndex ];
                nums[ supposedIndex ] = n;
            }
        }
        return res;
    }

    // No swapping - Only negation method
    vector<int> findDuplicates(vector<int>& nums) {
        vector<int> res;
        for (int i = 0; i < nums.size(); ++i) {
            int index = abs(nums[i]) - 1;
            if (nums[index] < 0)
                res.push_back(index + 1);
            else
                nums[index] *= -1;
        }
        return res;
    }
};