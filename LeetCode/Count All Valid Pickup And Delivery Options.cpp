#include <vector>
using namespace std;


//https://leetcode.com/problems/count-all-valid-pickup-and-delivery-options/
/*
 * This is a Dynamic Programming problem (Also can be solved via pure mathematics)
 *
 * Define the states first. It is stated that a delivery cannot be done before pickup of a particular order i.
 * Therefore, each state can be defined as (pickupLeft, deliveryLeft), which if not obvious, you can see example:
 *
 * If n = 5, we are initially at state (5, 0) - We have 5 pickups to do, and 0 delivery to be done.
 * We can select one out of 5 available pickups - Then we transition to state (4, 1).
 * Now, its a bit different - We can have 2 transitions:
 * 		>	Do another pickup and transition to (3, 2)
 * 		>	Do the delivery and transition to (4, 0)
 *
 * Now you can clearly see the states defintion and transitions. Let's see the DP:
 *
 * --------------------------------
 *
 * Let DP[i][j] indicates the total valid pickup and delivery options (that is, the number of permutations).
 * where i = pickupLeft, j = deliveryLeft.
 *
 * Which, if n = 5, the answer to the problem would be at DP[5][0]
 *
 * As a bottom-up DP approach, we would calculate each cell accordingly -
 *
 * 1) Do pickup - Decrease 1 pickupLeft, but increase 1 deliveryLeft. We can choose from (pickupLeft) pickups
 * 				  Therefore DP[pickupLeft-1][deliveryLeft+1] * pickupLeft
 *
 * 2) Do delivery - pickupLeft same, but decrease 1 deliveryLeft. We can choose from (deliveryLeft) deliveries.
 * 					Therefore DP[pickupLeft][deliveryLeft-1] * deliveryLeft
 *
 *	Therefore, i = pickupLeft, j = deliveryLeft
 *
 * 	DP[i][j] =
 * 		( DP[i-1][j+1] * i ) +
 * 		( DP[i][j-1] * j )
 *
 * 	From bottom-up DP, we should complete the row 0 first - 0 pickups, but up to N deliveries. The value is simply
 * 	N factorial - N!.
 * 	-----------------------------------
 *
 * 	Of course, since the DP only access the last row, simply optimized so the extra space complexity is reduced to
 *	O(N) instead of O(N^2).
 */



class Solution {
public:
    typedef long long int LONG;

    int countOrders(int n) {
        const LONG MOD = 1000000007;
        vector<LONG> dp(n + 1, 0);
        dp[1] = 1;

        // Handle first row - pickup = 0, deliver = N. Simply formula is N!
        for (int i = 2; i <= n; ++i) dp[i] = (dp[i - 1] * i) % MOD;

        // General DP case
        for (int pickupLeft = 1; pickupLeft <= n; ++pickupLeft) {
            for (int deliveryLeft = 0; deliveryLeft + pickupLeft <= n; ++deliveryLeft) {
                // Option 1 - choose to pickup one order
                dp[deliveryLeft] = (dp[deliveryLeft + 1] * pickupLeft) % MOD;

                // Option 2 - choose to deliver one order
                if (deliveryLeft != 0)
                    dp[deliveryLeft] = dp[deliveryLeft] + (dp[deliveryLeft - 1] * deliveryLeft) % MOD;
            }
        }

        // Return
        return (int)dp[0];
    }
};