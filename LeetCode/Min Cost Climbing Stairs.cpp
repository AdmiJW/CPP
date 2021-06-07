#include <vector>
using namespace std;

//https://leetcode.com/problems/min-cost-climbing-stairs/
/*
 * 	This is a classical Dynamic Programming Question.
 *
 * 	At a particular step, I can choose to go to step i+1, or step i+2
 *
 * 	Either case, if I know in advance the cost for step i+1 and step i+2 (subproblems)
 * 	to reach the end, then the problem can be solved in O(N) time, because surely, the
 * 	min cost to reach the end from current step is:
 *
 * 		cost[i] + min( dp[i+1], dp[i+2] )
 */

class Solution {
public:
	//	DP solution, manipulating array in place
	int minCostClimbingStairs(vector<int>& cost) {
		for (int i = cost.size() - 3; i >= 0; --i)
			cost[i] = min(cost[i] + cost[i + 1], cost[i] + cost[i + 2]);
		return min(cost[0], cost[1]);
	}


	//	DP solution, but only keep track of latest 2 results.
	int minCostClimbingStairs2(vector<int>& cost) {
		int latest1 = cost[cost.size() - 1], latest2 = cost[cost.size() - 2];
		for (int i = cost.size() - 3; i >= 0; --i) {
			int curr = cost[i] + min(latest1, latest2);
			latest1 = latest2;
			latest2 = curr;
		}
		return min(latest1, latest2);
	}
};