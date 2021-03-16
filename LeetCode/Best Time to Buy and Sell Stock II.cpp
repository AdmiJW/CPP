#include <vector>
using namespace std;

//https://leetcode.com/problems/best-time-to-buy-and-sell-stock-ii/
/*
 * 	This, by the looks of it, can actually be solved using Dynamic Programming in O(N^2) time, by assuming each day
 * 	as the end of day and find out the best profit for it. However, DP will cause time limit exceeded here. Perhaps
 * 	there is a more optimal solution?
 *
 * 	Turns out this is a Greedy problem
 *
 * 	-----------------------------------------------------------------
 *
 * 	"Buy low, sell high". That's is what they said, and it turns out to be very true in this case!
 * 	If our transaction turns out to be profitable, then we would want to maximize the amount of transactions right?
 * 	Yes! but with a catch!
 *
 * 	If we were to perform a transaction, we would, of course, buy at lowest point and sell at the highest point - We
 * 	call them 'buy at valley, sell at peak'
 * 	Therefore for each valley -> peak pattern, we would perform a transaction. Consider 4,3,2,3,4,5,4,3,2. The maximum
 * 	profit for this, is buy at 2, and sell at 5.
 *
 * 	Recall what I said earlier - Maximize the amount of transactions, since every transaction is profitable. Does this
 * 	means that
 * 			1,2,3,4,5
 * 	we should break them down into 2 transactions instead of 1? Not quite.
 *
 * 	When I said maximize amount of transactions, it means to perform transaction whenever a valley -> peak pattern is
 * 	observed. See what happens when you break a valley -> peak pattern into 2 transactions:
 *
 * 		In a valley -> peak pattern, every price is increasing by a certain amount. If we break it into two or
 * 		more, we miss out one day worth of price in increment in our profit, resulting in less profit than
 * 		just performing one.
 *
	--------------------------------------------------------------------------

	Using the above intuition, we can make the code much cleaner:

	Turns out: If current element is greater than previous element, we can directly add the difference into the profit

	Why? See the example valley -> peak pattern:
			a, b, c, d

		Say b = a + x
			c = b + y
			d = c + z
		where x,y,z are positive integers

	Then, if I were to buy at a and sell at d, profit is:

		d - a
	=	(c + z) - a
	=	b + y + z - a
	=	a + x + y + z - a
	=	x + y + z

	Therefore, since a to b, diff is x, b to c, diff is y, c to d, diff is z. By just adding their differences, it does
	exactly what we done: Each valley -> peak pattern, we buy at lowest and sell at highest!

	-----------------------------------------------------------------------------------------

 *	Turns out, there is an elegant DP solution too!
 *
 *	Let's see the state diagrams:
 *
 *									Sell stock
 *				----		------------------------------>               -----|
 *	Hold stock	|	(Holding a Position)			(Not holding position)	   | Not buy any stock
 *				--->		<------------------------------				  <----
 *									Buy in Stock
 *
 *	Observe: To reach the state (Holding a position), it can be achieved via:
 *		>	Holding a stock
 *		>	Buy in a stock when not having a position
 *	To reach the state (Not holding position), it can be achieved via:
 *		>	Selling hold stock
 *		>	Not buying any stock when not holding stock
 *
 *
 *	To solve in DP, make 2 DP arrays representing both state. DP_Hold and DP_Sold
 *
 *	DP_Hold records the maximum profit available, and at the end of day, you are indeed holding a position, aka you
 *	have a stock available to sell later
 *	Initially, DP_Hold is -inf, so it will be updated by buying in stock on first day
 *
 *	DP_Sold records the maximum profit available, and at the end of day, you are NOT holding a position.
 *	Initially, DP_Sold is 0, because we start out without a stock and profit is 0.
 *
 *	Therefore, to update DP_Hold and DP_Sold, look at the state diagram and the following algorithm makes sense:
 *
 *		cur_hold = max( prev_hold, prev_sold - price )
 *		cur_sold = max( prev_sold, prev_hold + price )
 *
 *
 *	Since the DP updating algorithm only relies on previous DP result, it can be done by simply 2 variables!
 */

class Solution {
public:

	//	Look for peak and valley solution
	int maxProfit(vector<int>& prices) {
		const int len = prices.size();
		int profit = 0;
		int lowpoint = prices[0];

		for (int i = 0; i < len - 1; ++i) {
			//	The price will fall! Sell the stock with current price
			if (prices[i + 1] < prices[i]) {
				profit += max(0, prices[i] - lowpoint);
				lowpoint = prices[i + 1];
			}
		}

		//	If at the end, it is still rising pattern, take into account of it
		if (len >= 2 && prices[len - 1] >= prices[len - 2])
			profit += prices[len - 1] - lowpoint;

		return profit;
	}



	//	One pass clean code solution
	int maxProfit2(vector<int>& prices) {
		int profit = 0;
		for (int i = 1; i < prices.size(); ++i) {
			if (prices[i - 1] < prices[i])
				profit += prices[i] - prices[i - 1];
		}
		return profit;
	}


	//	DP solution 
	int maxProfit3(vector<int>& prices) {
		int prev_hold = INT32_MIN / 2, prev_sold = 0;

		for (int i : prices) {
			int curr_hold = max(prev_hold, prev_sold - i);
			int curr_sold = max(prev_sold, prev_hold + i);
			prev_hold = curr_hold;
			prev_sold = curr_sold;
		}
		return prev_sold;
	}
};