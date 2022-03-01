#include <vector>
using namespace std;


//https://leetcode.com/problems/counting-bits/
/*
*   This is a Dynamic Programming / bit manipulation problem
* 
*   If you list out the solutions, you may observe a pattern in it:
* 
*   (0) (1) (1 2) (1 2 2 3) (1 2 2 3 2 3 3 4)
* 
*   In each of the groups, it actually is the copy of the previous array + 1. For example, (1 2 2 3) is simply all (0 1 1 2) added by
*   1!
*   The size of these groups are actually determined by power of 2: 1 -> 2 -> 4 -> 8.
* 
*   Using this property, we can utilize DP knowledge to obtain the answer. Even better, you can avoid arithmetic and
*   use bit manipulation if you like: Theres tons of solution on leetcode itself
*/


class Solution {
public:
    vector<int> countBits(int n) {
        vector<int> res(n + 1, 0);
        int shift = 1;

        for (int i = 1; i <= n; ++i) {
            if (i / 2 == shift) shift *= 2;     // Use division instead of multiplication to avoid overflow
            res[i] = res[i - shift] + 1;
        }
        return res;
    }
};