#include <vector>
using namespace std;

//https://leetcode.com/problems/best-time-to-buy-and-sell-stock-with-transaction-fee/
/*
 * 	This is a Dynamic Programming Problem, very, very similar to problem "Best Time to Buy and Sell Stock II".
 *
 * 	Again, this problem is best represented with state diagram. The very same algorithm is used in the problem stated
 * 	above, except now it introduced the transaction fee.
 * 	However, don't let that scare you. LITERALLY THE VERY SAME ALGORITHM WORKS, just take into account the transaction
 * 	fee, and you are done with this problem.
 */

class Solution {
public:
	int maxProfit(vector<int> prices, int fee) {
		int prev_sold = 0, prev_hold = INT32_MIN / 2;

		for (int p : prices) {
			int curr_sold = max(prev_sold, prev_hold + p - fee);
			int curr_hold = max(prev_hold, prev_sold - p);
			prev_sold = curr_sold;
			prev_hold = curr_hold;
		}
		return prev_sold;
	}
};