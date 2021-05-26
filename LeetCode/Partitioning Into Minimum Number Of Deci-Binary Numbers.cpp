#include <string>
using namespace std;

//https://leetcode.com/problems/partitioning-into-minimum-number-of-deci-binary-numbers/
/*
 * This is said to be a greedy problem, but I say it is a logic and proof question.
 *
 * 	We can only add 1 to a place number each time. Eg: 1001 will definitely add 1 at the thousandth place and oneth place.
 * 	Therefore, the solution is to actually find out how many times I actually had to add to a number place. Like:
 * 	800192. We are forced to add 9 Deci Binary numbers, because at tenths place, I am required to add 1 by 9 times!
 *
 * You might argue for the case that adding carry may affect the result, but that is a relatively easy proof:
 *
 * 	Say to reach 9, the quickest way is to add 1 by 9 times. So far, our algorithm would take maximum result of 9.
 * 	To achieve a carry, one must add for 9+1 = 10, which takes 10 times! Not optimal. Thus proven that our greedy method
 * 	works perfectly
 */

class Solution {
public:
    int minPartitions(string n) {
        int res = 0;
        for (char c : n)
            res = max(c - '0', res);
        return res;
    }
};