#include <vector>
using namespace std;


//https://leetcode.com/problems/minimum-value-to-get-positive-step-by-step-sum/
/*
 * The idea is simple:
 * Keep a running sum (prefix sum) for each element in the array nums.
 * We have to pay attention to the prefix sum when it becomes negative, since if the prefix sum is -n, then the initial value
 * must be n+1 to prevent the sum going less than 1.
 * Find the minimum prefix sum, and we can derive the minimum initial value.
 */

class Solution {
public:
	int minStartValue(vector<int>& nums) {
		int res = 1;
		int runningSum = 0;

		for (int n : nums) {
			runningSum += n;
			res = max(res, 1 - runningSum);
		}
		return res;
	}
};