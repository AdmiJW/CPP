#include <vector>
using namespace std;

//https://leetcode.com/problems/best-time-to-buy-and-sell-stock-with-cooldown/
/*
 * 	This is a DP problem which requires usage of State Machine.
 *
 * 	We could have a DP array that records the maximum profit at every index i. Then, every day, we could have the following
 * 	actions:
 * 		> Do Nothing/Cooldown - Then we'll just take previous day's maximum profit.
 * 		> Sell stock at this day - Then we need to determine which stock we bought in in previous days. Iterate backwards
 * 								   to find the day to buy stock which gives optimal profit.
 *
 * 									The formula will then be:
 * 										price[currday] - price[prevday] + maxProfit[closestDayAfterCooldown]
 *
 * 	The problem is on the maxProfit[closestDayAfterCooldown]. We don't know whether the day at dp[i], we are doing
 * 	nothing/cooldown or sold stock at that day!
 *
 * 	We essentially can be on 2 states on particular day:
 * 	1. Just sold stock on current day.
 * 	2. Do nothing on current day.
 *
 * 	Therefore we make 2 DP arrays, each representing diff state:
 * 	1. cooldownDP -> Maximum profit given that at day i, I must be doing nothing (Not selling)
 * 	2. sellDP -> Maximum profit given that at day i, I must sell one of the stocks from previous day.
 *
 * 	Then, the transition function is essentially:
 * 		cooldownDP[i] = max( cooldownDP[i-1], sellDP[i-1] )
 *
 * 		for each previous days j:
 * 			sellDP[i] = price[i] - price[j] + cooldownDP[j-1]
 *
 * 	==============================================================
 *
 * 	After looking at solution:
 *
 *  Instead of having 2 states: cooldown and sell, we could take a step further and make our states be:
 *  1. Holding - At index i holds maximum profit, with holding a stock bought
 *  2. Empty - At index i holds maximum profit, with no stock in hand.
 *
 *  Then since the buy[i] guarantees that I have a stock in hand, I can eliminate the need to iterate backwards to
 *  find the day to buy in the stock. Then, the time complexity suddenly reduces to O(N) only.
 *
 *  (Of course, you could further reduce to O(1) space because we no need to iterate backwards anymore)
 */

class Solution {
public:

    int maxProfit(vector<int>& prices) {
		const int len = prices.size();
		vector<int> sellDP(len + 1, 0);
		vector<int> readyDP(len + 1, 0);

		// Every day, you can either:
		// - Sell stock bought from previous days (Requires backward iteration)
		// - Cooldown - Max price is previous day's sellDP
		for (int i = 0; i < len; ++i) {
			// Cooldown
			readyDP[i + 1] = max(readyDP[i], sellDP[i]);
			// Must sell stock at current day
			for (int j = i - 1; j >= 0; --j) {
				sellDP[i + 1] = max(
					sellDP[i + 1],
					prices[i] - prices[j] + readyDP[j]
				);
			}
		}
		return max(readyDP[len], sellDP[len]);
    }


	int maxProfit2(vector<int>& prices) {
		const int len = prices.size();
		vector<int> holdDP(len + 1, 0);
		vector<int> emptyDP(len + 1, 0);

		// Since we must hold a stock in holdDP[1], buy in at first day.
		holdDP[1] = -prices[0];

		for (int i = 1; i < len; ++i) {
			// Either buy in at current day or inherit from previous day
			holdDP[i + 1] = max(holdDP[i], emptyDP[i - 1] - prices[i]);
			// For empty, we sell at current day or inherit from previous day
			emptyDP[i + 1] = max(emptyDP[i], holdDP[i] + prices[i]);
		}
		return emptyDP[len];
	}




};