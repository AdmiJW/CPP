#include <vector>
#include <algorithm>
using namespace std;

// https://leetcode.com/problems/sequential-digits/
/*
 * 	This is a "brute-force" problem, or you could say simulation at least?
 *
 * 	Start out with digits from 1 to 9. We will attempt to append sequenatial digits at the end of the numbers.
 * 	Once they fit inside the [low, high] boundary, add it to the result set.
 *
 * 	Discard the number as soon as it become higher than upper boundary.
 */


class Solution {
public:
    vector<int> sequentialDigits(int low, int high) {
        vector<int> res;
        for (int i = 1; i < 9; ++i) recurse(res, i, low, high);
        sort(res.begin(), res.end());
        return res;
    }



    void recurse(vector<int>& res, int n, int low, int high) {
        if (n > high) return;
        if (low <= n) res.push_back(n);

        if (n % 10 == 9) return;
        recurse(res, n * 10 + (n % 10 + 1), low, high);
    }
};