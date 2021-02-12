//https://leetcode.com/problems/number-of-steps-to-reduce-a-number-to-zero/
/*
 * 	First, this problem can be solved directly. In the worst case, every time it get divides by 2,
 * 	it become odd, -1 will become even again. So time is O(2 Log N)
 *
 * 	We can use bit manipulation here -
 * 		Check LSB for oddness
 * 		Right shift for divide by 2.
 */

class Solution {
public:
	int numberOfSteps(int num) {
		int res = 0;
		while (num) {
			if (num % 2) num -= 1;
			else num /= 2;
			++res;
		}
		return res;
	}

	//	Quicker math, less iteration
	int numberOfSteps2(int num) {
		int res = 0;
		while (num) {
			if ( num % 2 ) ++res;
			++res;
			num /= 2;
		}
		return res - 1 > 0 ? res - 1 : 0;
	}



	//	Bit Manip
	int numberOfSteps3(int num) {
		int res = 0;
		while (num) {
			if (num & 1) ++res;
			++res;
			num >>= 1;
		}
		return res - 1 > 0 ? res - 1 : 0;
	}
};