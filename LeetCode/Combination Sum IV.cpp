#include <vector>
#include <algorithm>
using namespace std;

//https://leetcode.com/problems/combination-sum-iv/
/*
 * This is a Dynamic Programming Problem, with initial idea of depth first search
 *
 * To reach target, we can choose a number each time. So in each recursive layer, loop through the number array,
 * and perform recursion call with (target - n) where n is the current number selected. Perform sum of returned result
 * since the call will going to return number of permutations generated
 *
 * The base case for recursion is when target == 0, which means we reached target, return 1.
 * If you do not want to do negative checking in the iteration, add another base case where when target < 0, return 0.
 *
 * However, this solution easily times out, due to the fact that same target may be computed multiple times.
 *
 * ----------------------------------------------------------------------------------------------------------------
 *
 * Therefore, simply store the computation result using DP. Even further, we compute using bottom up approach.
 * Base case is target = 0, where there is no of permutations = 1.
 * Then compute target = 1, 2, 3..., where we iterate thru the array nums, and check out dp[target - n]
 *
 * ---------------------------------------------------------------------------------------------------------------
 *
 * Based on follow up question, if there are negative numbers, there may exist possibility for inifinte paths. Say
 * we want target = 0, and arr = [1,-1], it can be (), (1,-1), (1,1,-1,-1)...
 *
 * Thus unless we restrict the permutation length, it will be infinite solution.
 */

class Solution {
public:
	//	Simple Depth First Search solution, easily time limit exceeded
	int combinationSum4(vector<int>& nums, int target) {
		if (target < 0) return 0;
		if (!target) return 1;

		int soln = 0; 
		for (int n : nums) {
			soln += combinationSum4(nums, target - n);
		}
		return soln;
	}


	//	Due to repeated operations, Dynamic Programming is used.
	//  Optimization to sort the array first, so we can break early
	int combinationSum4_2(vector<int>& nums, int target) {
		sort(nums.begin(), nums.end());
		vector<unsigned int> dp(target + 1, 0);
		dp[0] = 1;

		for (int i = 1; i <= target; ++i) {
			for (int n : nums) {
				if (i - n < 0) break;
				dp[i] += dp[i - n];
			}
		}
		return dp[target];
	}
};