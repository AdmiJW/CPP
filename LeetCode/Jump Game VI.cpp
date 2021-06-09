
#include <deque>
#include <vector>
using namespace std;

//https://leetcode.com/problems/jump-game-vi/
/*
 * 	This is a DP, Deque problem.
 *
 * 	Looking at this question if you are a experienced with Dynamic Programming, you immediately know
 * 	to approach the problem bottom up (from back of array), such that we may have recorded dp[i]
 *  which shows the maximum score to reach end starting from index i
 *
 *  The problem is the jump range of size k. If k is large, it means in each iteration, I have to check
 *  dp array ranging up to size k, thus time complexity of O(NK)
 *
 *  If you've heard of monotonic dequeue before, it is perfect time to use it here. Each DP result will be
 *  stored in the queue, but we apply a algorithm where the queue will be always strictly decreasing.
 *  In other words, the front of the queue is largest in the queue, and the tail is smallest.
 *
 *  This is done when we apply the following algorithm to the queue pushing:
 *
 *  	>	While the element to push is greater than the tail of queue, pop the tail of queue
 *  	>	End of loop, the queue is either empty or the element in it is greater than the element to push.
 *  		Push the element to the tail of queue
 *
 *  This way, everytime we peek at the front of queue, it is always the maximum DP element!
 *
 *  One little thing is to check if the element is out of range. This can be done by recording the index as well
 *  and perform checking at each iteration.
 */

class Solution {
public:
	int maxResult(vector<int>& nums, int k) {
		const int len = nums.size();

		deque<pair<int, int>> deque;
		deque.emplace_back(make_pair<>(nums[len - 1], len - 1));
	
		for (int i = len - 2; i >= 0; --i) {
			//	Remove out of range DP result
			if (!deque.empty() && deque.front().second > i + k)
				deque.pop_front();

			int localBest = nums[i] + deque.front().first;

			//	Pop out redundant smaller element, and push current DP result
			while (!deque.empty() && deque.back().first <= localBest)
				deque.pop_back();
			deque.emplace_back(make_pair<>(localBest, i));
		}

		while (!deque.empty()) {
			auto& dp = deque.front();
			deque.pop_front();
			if (!dp.second) return dp.first;
		}
		return -1;
	}
};