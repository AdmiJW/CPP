#include <cmath>
using namespace std;


//https://leetcode.com/problems/power-of-two/


class Solution {
public:

    // Built in logarithm solution
    bool isPowerOfTwo(int n) {
        return fmod(log2(n), 1) == 0;
    }


    // Bit XOR solution - O(32)
    bool isPowerOfTwo(int n) {
        if (n <= 0) return false;

        for (int i = 0; i < 32; ++i) {
            if ( (n ^ (1 << i)) == 0) return true;
        }
        return false;
    }


    //Magical bitwise operation. We AND the n and n-1. If n is power of 2, then its binary form would have only exactly 1 Ones. Then the
    // n-1 would have all the zeroes after the lone Ones flipped to 1. See:
    /*
     * 	Eg: If n = 16, binary = 10000
     * 		   n-1 = 15, binary = 01111
     * 	Therefore if we AND these two, it shall end up as zero, else it is not power of 2
    */
    bool isPowerBitwise(int n) {
        return n > 0 && (n & (n - 1)) == 0;
    }
};