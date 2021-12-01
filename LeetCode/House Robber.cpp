#include <vector>
using namespace std;

//https://leetcode.com/problems/house-robber/
/*
*   This is a Dynamic Programming problem.
* 
*   Every day, you can be in one of two states: Able to rob again (Previous 1+ houses are not robbed), or unable to rob again (Previous house is
*   robbed). Therefore we need 2 DP arrays for this.
* 
*   Every day, we determine each transition:
*       - If we rob today, the result is (previous day's no rob max profit) + house value
*       - If we don't rob today, the result is max( (previous day's no rob max profit), (previous day's rob max profit) )
*/

class Solution {
public:

    int rob(vector<int>& nums) {
        int prevRob = 0, prevNoRob = 0;

        for (int i: nums) {
            int todayRob = prevNoRob + i;
            int todayNoRob = max(prevRob, prevNoRob);

            prevRob = todayRob;
            prevNoRob = todayNoRob;
        }
        return max(prevNoRob, prevRob);
    }

};