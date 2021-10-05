using namespace std;

//https://leetcode.com/problems/climbing-stairs/
/*
 * This is a classical DP problem, which can also be good for introduction to recursion.
 *
 * To solve number of ways to climb stairs up to step n, think: To reach step n, we could come here from 2 ways:
 * 	>	From step n-1, make 1 step forward to n
 * 	> 	From step n-2, make 2 step forward to n
 *
 * Therefore the number of ways to reach step n, depends on previous 2 steps' answer. This introduces recurrence relation.
 * And due to recurrence relation, we could use DP here.
 * This DP is actually just fibonacci sequence, where next number depends on sum of previous 2 numbers, so for space complexity
 * we could simply use O(1) to store 2 variables.
 */


class Solution {
public:
    int climbStairs(int n) {
        if (n < 2) return 1;
        int prev[2] = { 1, 1 };

        for (int i = 2; i <= n; ++i) {
            int curr = prev[0] + prev[1];
            prev[0] = prev[1];
            prev[1] = curr;
        }
        return prev[1];
    }
};