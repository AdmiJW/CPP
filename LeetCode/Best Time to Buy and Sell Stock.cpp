#include <vector>
using namespace std;

//https://leetcode.com/problems/best-time-to-buy-and-sell-stock/
/*
 * 	This is a Array problem, with a little element of DP inside.
 *
 * 	We want to find out the minimum and maximum element in the prices array, with the catch that the maximum
 * 	element must be after the minimum element. In other words, min cannot be after max.
 *
 * 	We can keep a global result of profit, which represents the maximum profit so far, which will be returned
 * 	at the end of the problem. Initially, the value is set to 0 because at start we have no profit whatsoever
 *
 * 	Also, keep a min variable. It will keep track of the minimum element met so far. It is initialized to INF
 * 	so it will be updated in the first iteration
 *
 *
 * 	Now, run a single iteration through the prices array. If current element is smaller than min, update the min.
 * 	Then, update the profit whether if I select this day to sell the 'min' stock, will yield higher profit
 */

class Solution {
public:
	int maxProfit(vector<int>& prices) {
		int profit = 0;
		int smallest = INT32_MAX;

		for (int i : prices) {
			smallest = min(smallest, i);
			profit = max(profit, i - smallest);
		}
		return profit;
	}
};