#include <vector>
using namespace std;

//https://leetcode.com/problems/jump-game-ii/
/*
 * 	This is a array, greedy problem.
 *
 * 	Initially, I thought of a DP similar solution, where I have dp array where each index i records the
 * 	number of jumps required to go from index i to last.
 * 	The base case is at len-1, which is 0.
 * 	For every index i, iterate thru all possible jumps and pick the minumum jump from dp array, +1.
 *
 * 	Solution takes O(N^2) time, yet O(N) space. Its not good.
 *
 * 	------------------------------------------------------
 *
 * 	Say [2,3,1,1,4]
 * 	The optimal solution is BFS concepted. Initially, start from index 0. We discover that we can jump from
 * 	index 0, to index range [1,2].
 * 	Therefore count that as one layer. Then, iterate nodes in index [1,2] and determine the furthest reach in the next layer.
 * 	In this case, [1,2] has the jump '3' in index 1, which reaches last index. Therefore the next reach is [3,4].
 *
 * 	At the end of one layer, set start to be end +1, and end to be whatever further reach is, if you havent reach len-1
 */

class Solution {
public:
	//	O(N^2) time solution, O(N) space. Not optimal solution
	int jump(vector<int>& nums) {
		const int len = nums.size();
		vector<int> dp(len, 0);
		for (int i = len - 2; i >= 0; --i) {
			dp[i] = INT32_MAX / 2;
			for (int j = 1; j <= nums[i] && i + j < len; ++j)
				dp[i] = min(dp[i], dp[i + j] + 1);
		}
		return dp[0];
	}


	//	Breadth First Search range based solution. O(N) time, O(1) space
	int jump2(vector<int>& nums) {
		const int len = nums.size();
		if (len == 1) return 0;
		int start = 0, end = 0, layer = 1;

		for (; start <= end; ++layer) {
			int nextreach = -1;
			while (start++ <= end)
				nextreach = max(nextreach, start + nums[start - 1] - 1);
			if (nextreach >= len - 1) return layer;
			--start; end = nextreach;
		}
		return -1;
	}
};