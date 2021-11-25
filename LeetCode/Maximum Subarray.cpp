#include <vector>
using namespace std;

//https://leetcode.com/problems/maximum-subarray/
/*
 * This is a Dynamic Programming problem.
 * 
 * For each element e in the array, we can determine the maximum subarray that ends with e, and that is done by considering the two
 * possible cases:
 *  
 *  1. e is the lone element in the new subarray. --> [-1,-2, 4]. In this case, (4) is better by itself rather than joining prev elements
 *  2. e joins with previous maximum subarray --> [1,2,4]. In this case, (4) joins [1,2] to produce greater subarray sum.
 * 
 * For each element e, consider the answer for both answers above, and from that, keep track of a global maximum to return as result.
 * 
 */


class Solution {
public:

    // O(N) dynamic programming solution
    int maxSubArray(vector<int>& nums) {
        int prev = 0;
        int res = nums[0];
        for (int i : nums) {
            prev = max(i, prev + i);
            res = max(res, prev);
        }
        return res;
    }
};