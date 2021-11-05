#include <math.h>
using namespace std;

//https://leetcode.com/problems/arranging-coins/submissions/
// This question can be modelled as a quadratic formula problem, thus solving it in O(1) time
// 
// First, the formula to get the sequence of 1 + 2 + 3 + 4 + ... + n is:
//
//      n(n + 1)
//      --------  = x
//          2
//
// From the problem, first row contains 1 coin, second row contains 2 coin and so on. The above formula is just perfect.
// Therefore, using above formula, I can just find out number of complete rows immediately given the x (number of coins
// given). I just have to round down the result.
//
// Rearrange the equation to be quadratic:
//      n^2 + n - 2x = 0
// and solve using quadratic formula:
//
//      -1 + Å„1 - 4(-2)(x)
//      ------------------
//              2


class Solution {
public:

    // Math solution using Quadratic formula
    // Calculate in double to prevent integer overflow
    int arrangeCoins(int n) {
        return (int)((-1 + sqrt(1 - 4.0 * -2 * n)) / 2);
    }

};