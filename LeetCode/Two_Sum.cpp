#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

//https://leetcode.com/problems/two-sum/
/*
*   When we fix an element in the array, say x, we would want to know immediately if another element y, that sums up to target
*   exists in the array or not.
* 
*   Therefore, use extra space using HashMap to record the values that maps to index. However, what do we do if there's multiple
*   duplicate values?
* 
*   Since we will fix the first value x from left to right, in case of duplicate values we could take the rightmost index.
*/


class Solution {
public:

    // Two Sum using HashMap (value -> latest index)
    vector<int> twoSum(vector<int>& nums, int target) {
        const int len = nums.size();
        unordered_map<int, int> map;

        // Fill the map with the numbers
        for (int i = 0; i < len; ++i)
            map[nums[i]] = i;

        // Now for each of the elements, find its pair
        for (int i = 0; i < len; ++i) {
            int other = target - nums[i];

            if ( map.count(other) && (other != nums[i] || map[other] != i ) )
                return { i, map[other] };
        }
        return {};
    }
};