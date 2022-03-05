#include <vector>
#include <unordered_map>
using namespace std;

//https://leetcode.com/problems/delete-and-earn/
/*
 * This is a dynamic programming problem.
 *
 * First of all, what matters more in this problem is the element itself, not the index in the array.
 * Therefore, we convert the array into a frequency table - { element - count }
 *
 * While obtaining the frequency table, we should also obtain the maximum element which can go up to 10000 only.
 * The maximum element will be useful in DP part later.
 *
 * ----------------------------------
 *
 * For DP, we will imagine we have a dp array up until {max} size only. DP[i] will indicate the maximum points
 * that we can possibly earn from considered deleting elements from (0,i].
 *
 * Therefore, since we will have to remove e-1 and e+1 when we try to earn points from element e, the transition
 * function shall be clearer:
 *
 * 		dp[i] = max(
 * 			dp[i-1],						// <- If we do not earn from element i
 * 			dp[i-2] + (count of i) * i		// <- If we earn from element i. We cannot get points from element i-1
 * 		)
 *
 * Using this, Dynamic programming approach shall be clear. Note that since we only use elements from i-1 and i-2,
 * we can space optimize to use only O(1) extra space.
 */


class Solution {
public:
    int deleteAndEarn(vector<int>& nums) {
		// Step 1 - convert array into frequency table (Also record maximum element)
		int maxElem = 0;
		unordered_map<int, int> freq;

		for (int i : nums) {
			maxElem = max(maxElem, i);
			++freq[i];
		}

		// Step 2 - Using DP to compute the maximum points, where DP[i] means maximum point earned if i covered up to
		// element i.
		vector<int> dp(maxElem + 1, 0);
		dp[1] = freq[1];

		for (int i = 2; i <= maxElem; ++i) {
			dp[i] = dp[i - 1];
			if (freq.count(i)) dp[i] = max(dp[i], dp[i - 2] + freq[i] * i);
		}

		return dp[maxElem];
    }
};