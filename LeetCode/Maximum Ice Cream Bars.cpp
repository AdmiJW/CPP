#include <vector>
#include <algorithm>
using namespace std;

// https://leetcode.com/problems/maximum-ice-cream-bars/
/*
 * An easy greedy problem. The problem asks to only maximize the number of ice creams that can be bought.
 * Therefore, we will greedily buy the cheapest ice cream first, and then the second cheapest, and so on.
 *
 * So, we sort the array of costs, and then greedily buy the cheapest ice cream first.
 * If we cannot buy the cheapest ice cream, we return the number of ice creams we have bought so far because
 * further ice creams will be more expensive.
 */


class Solution {
public:
    int maxIceCream(vector<int>& costs, int coins) {
        sort(costs.begin(), costs.end());

        for (int i = 0; i < costs.size(); i++) {
            if (coins < costs[i])
                return i;

            coins -= costs[i];
        }

        return costs.size();
    }
};