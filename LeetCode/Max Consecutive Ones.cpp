
#include <vector>
using namespace std;

//https://leetcode.com/problems/max-consecutive-ones/
/*
 * This is a Array problem
 *
 * The idea is simple: Count 1s in groups. Take the maximum group length as result and return.
 * If met 0, reset the counter.
 * Else, add 1 to the counter, also update the result.
 */


class Solution {
public:
    int findMaxConsecutiveOnes(vector<int>& nums) {
        int res = 0;
        int curr = 0;

        for (int n : nums) {
            if (n == 0) curr = 0;
            else {
                ++curr;
                res = max(res, curr);
            }
        }
        return res;
    }
};