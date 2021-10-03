#include <vector>
using namespace std;

//https://leetcode.com/problems/jump-game/
/*
 * 	This is a Dynamic Programming problem.
 *
 * 	We use the DP approach to solve this problem: Determine whether we can reach the all the grids starting from index i = 0, 1, 2...
 * 	When we reach subproblem of i = nums.length-1, we have obtained the solution.
 *
 * 	Whether we can reach current grid or not, we must record a data that tells us the maximum reach that is achievable from previous
 * 	jumps. For example if we are at index 0 and nums[0] = 5, then our maximum reach is grid i = 5.
 * 	For each grid, check maxReach if we can actually reach this grid or not. If not, then return false immediately. If we successfully
 * 	reach the end of array, then return true.
 */

class Solution {
public:
	bool canJump(vector<int>& nums) {
		int maxReach = 0;
		for (int i = 0; i < nums.size(); ++i) {
			if (maxReach < i) return false;
			maxReach = max(maxReach, i + nums[i]);
		}
		return true;
	}
};