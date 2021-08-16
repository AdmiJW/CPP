#include <vector>
using namespace std;

//https://leetcode.com/problems/range-sum-query-immutable/
/*
 * 	A simply prefix sum problem.
 *
 * 	To query the sumRange in O(1) time, say we have a prefix sum array which at index i, records the sum of elements
 * 	in original array from nums[0] to nums[i], then we can easily find out the sum from nums[a] to nums[b]. See:
 *
 * 		   a              b
 * 	[ ][ ][ ][ ][ ][ ][ ][ ][ ]
 * 	|----||----------------|
 * 	 EXC    INC
 *
 * 	To find out the sum from a to b inclusive, we have to just find out sum of elements up until b (EXC+INC), then substracting
 * 	the sum of elements up to but excluding a (EXC).
 */

class NumArray {
public:
    vector<int> prefixSum;

    // PrefixSum[] of sized len+1. in prefixSum[i] means sum from nums[0] to nums[i-1] (prefixSum[0] == 0)
    NumArray(vector<int>& nums) : prefixSum(vector<int>(nums.size() + 1, 0)) {
        for (int i = 0; i < nums.size(); ++i)
            prefixSum[i + 1] = prefixSum[i] + nums[i];
    }

    int sumRange(int left, int right) {
        return this->prefixSum[right + 1] - this->prefixSum[left];
    }
};