

//https://leetcode.com/problems/divide-two-integers/
/*
 * 	Really, the core concept is as follows:
 * 		Remember back your digital logic class. Multiplication and division can be done by repeatedly adding or subtracting
 * 		the numbers. So that's what we will do here.
 *
 * 	However, consider the case INT_MAX / 1. Are we really going to subtract INT_MAX times until we reached 0? Not quite!
 * 	It will result in time limit exceeded.
 *
 * 	Instead, think binary search! While the dividend is not reduced to negative, we want to subtract by divisor. However,
 * 	instead of subtracting divisor constantly, we multiply it by 2 each time, so it becomes 1,2,4,8... While the dividend
 * 	can still be subtracted with that multiplied divisor, we keep on multiplying.
 * 	The power is simply multiplying by 2 too! Say we have divisor of 4, then:
 *
 * 		4	->	8	->	 16		->	32
 * 	  (1*4)	   (2*4)	(4*4)		(8*4)
 *
 * 	Since we are prohibited from using * and /, we will use left shift and right shift as our way of multiplying and dividing
 *  2!
 *
 *  At last, when the dividend has finally reduced to negative, return the sum of powers. Remember that we have to determine
 *  if answer is negative or not based on the 2 inputs beforehand!
 */


#include <climits>
#include <cmath>
typedef long long int LONG;
using namespace std;

class Solution {
public:
	int divide(int dividend, int divisor) {
		if (dividend == INT_MIN && divisor == -1) return INT_MAX;

		bool isNegative = (dividend > 0 && divisor < 0) || (dividend < 0 && divisor > 0);
		LONG n = abs((LONG)dividend);
		LONG d = abs((LONG)divisor);

		LONG res = 0;
		while (n >= d) {
			LONG local = d, power = 1;
			
			while (local <= n) {
				local <<= 1;
				power <<= 1;
			}

			res += power >> 1;
			n -= local >> 1;
		}
		return isNegative ? -res : res;
	}
};