#include <vector>
#include <algorithm>
using namespace std;

//https://leetcode.com/problems/partition-to-k-equal-sum-subsets/
/*
 * 	This is (supposed to be HARD) Backtracking OR DP problem.
 *
 * 	First, you need to realize that for a valid subsets of equal sum to exist, each subset must be of sum = sum(nums) / k
 * 	In other words, sum(nums) must be divisible by k. Let target = target sum for each subset = sum(nums) / k
 *
 *  ================================================================================
 *
 * 	Now from intuition, each element in array can be sent to any of the k subsets. At the end, we check if each of subsets
 * 	are actually sum = target. This is a backtracking algorithm. However even with input size of 16, it results in
 * 	time limit exceeded. We could optimize it to greatly reduce the recursion tree.
 *
 * 	Sort the array. Since in each recursion we will only recurse if the subsetSum + elem is not > target, we would
 * 	iterate in descending order, and ignore the previously iterated elements if we are not going to a new subset.
 * 	Repeating iteration with seen elements is going to easily eat up a lot of time and result in TLE.
 *
 * 	================================================================================
 *
 * 	We could use DP to represent the states. Each state is represented by bits of length nums.length, where each bit
 * 	at index i represent whether the element at i index is used up or not.
 *
 *  Inside the dp array, we store the subset sum. We set -inf to indicate that a state is unreachable and thus we ignore
 *  that. Otherwise, it is a reachable state. We consider adding another element to open up new possibilities of state:
 *
 *  For each bit, if it is not 1 (used):
 *  	Check if adding this element will result in subsetSum overflow (> target). If it does, we cannot add this element.
 *  	Otherwise, set the next state to be subsetSum + currElem % target (Because if sum == target, then we open up a
 *  	new subset)
 *
 *  At the end, check if dp[1111111...111] == 0 or not.
 */

class Solution {
public:
    // To have good partition, the sum(nums) must be divisible by k.
    bool canPartitionKSubsets(vector<int>& nums, int k) {
        // Divisibility check
        int sum = 0;
        for (int i : nums) sum += i;
        if (sum % k != 0) return false;

        // Sort reverse order. To minimize recursion, we fill large elements first
        sort(nums.begin(), nums.end());

        // Backtracking
        vector<bool> visited(nums.size(), false);
        return backtrack(0, k, nums.size() - 1, visited, nums, sum / k);
    }

    // Returns true if there is a case found.
    bool backtrack(int setSum, int setLeft, int rightBound, vector<bool>& visited, vector<int>& nums, int target) {
        // Base case - Already reached target! return true
        if (setLeft == 0) return true;

        // Set fulfilled. Proceed to next set
        if (setSum == target)
            return backtrack(0, setLeft - 1, nums.size() - 1, visited, nums, target);

        // Otherwise, we could attempt to insert number to current set.
        for (int i = rightBound; i >= 0; --i) {
            if (!visited[i] && setSum + nums[i] <= target) {
                visited[i] = true;
                if (backtrack(setSum + nums[i], setLeft, i - 1, visited, nums, target)) return true;
                visited[i] = false;
            }
        }

        // No solution found. Return false
        return false;
    }



    // Optimal DP solution - O(2^N * N) time and O(2^N) space
    bool canPartitionKSubsets2(vector<int>& nums, int k) {
        const int len = nums.size();
        // Divisibility check
        int sum = 0;
        for (int i : nums) sum += i;
        if (sum % k != 0) return false;

        // Intiialize DP array, using bitmasks to represent all the states.
        vector<int> dp(1 << len, INT32_MIN);
        dp[0] = 0;								// Nothing selected is a valid state

        int target = sum / k;

        // Iterate through all possible states
        for (int state = 0; state < (1 << len); ++state) {
            // Invalid state - Not achievable
            if (dp[state] == INT32_MIN) continue;

            // Valid state - Now choose among unselected elements.
            for (int i = 0; i < len; i++) {
                // If the number is not yet selected, and including the number into this set does not exceed target
                if ((state & (1 << i)) == 0 && dp[state] + nums[i] <= target)
                    dp[state | (1 << i)] = (dp[state] + nums[i]) % target;
            }
        }
        return dp[(1 << len) - 1] == 0;
    }
};