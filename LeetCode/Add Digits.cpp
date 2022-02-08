#include <string>
using namespace std;

//https://leetcode.com/problems/add-digits/
/*
 * The solution with iterations/recursion is simple. However, there exists a mathematical solution
 * which solves it in O(1) using digital root - Sum of digits in a number.
 *
 * See the official solution.
 */


class Solution {
public:

    // Iterative solution
    int addDigits(int num) { 
        while (num / 10) {
            int i = num;
            num = 0;

            for (; i; i /= 10)
                num += i % 10;
        }
        return num;
    }



    // Digital root mathematical solution
    int addDigits2(int num) {
        return (num == 0) ? 0 : (num - 1) % 9 + 1;
    }
};