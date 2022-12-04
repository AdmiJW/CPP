#include <vector>
using namespace std;

// https://leetcode.com/problems/minimum-average-difference
/*
 * This is an array prefix sum problem.
 * 
 * First, obtain the sum of all the array elements. Note that the sum may exceed the integer range, use long type.
 * Then, in the iteration, do a prefix sum, and the right hand side sum is the sum of all elements minus the prefix sum.
 */

class Solution {
public:
    int minimumAverageDifference(vector<int>& nums) {
        const int n = nums.size();
        
        // One pass to obtain the sum of all numbers
        long long int sum = 0;
        for (int num: nums) sum += num;

        // Another pass to find out the minimum average difference
        long long int minDiff = INT32_MAX;
        int minDiffIndex = -1;
        long long int runningSum = 0;

        for (int i = 0; i < n; i++) {
            runningSum += nums[i];
            long long int leftAvg = runningSum / (i + 1);
            long long int rightAvg = (i == n - 1)? 0: (sum - runningSum) / (n - i - 1);
            long long int diff = abs(leftAvg - rightAvg);

            if (diff < minDiff) {
                minDiff = diff;
                minDiffIndex = i;
            }
        }

        return minDiffIndex;
    }
};