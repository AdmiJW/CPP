//https://leetcode.com/problems/broken-calculator/
/*
 *	Say I have a integer n. Now I have to multiply by 2 or add 1 to it until it reaches Y.
 *	If I am greedily multiplying, I might be unable to reach the optimal solution, as the -1 operation turns out
 *	to be stacking each time I multiply. See:
 *
 *		N-1
 *		2N-2
 *		4N-4
 *		8N-8
 *
 *	With each multiplication, the +1 actually turned to become +8 at the very end! Thus, the problem is very hard to
 *	solve by multiplication and +1.
 *
 *	Turns out, the solution can be solved by reversing the operations: Dividing by 2, and plus 1. Since when each divide,
 *	the +1 done previously will be diminished instead of stacking on top of each other.
 *
 *	Say we have a series of operations [ ..., +1, +1, /2 ]. Since the +1 total up to 2, but at the end, dividing becomes
 *	+1, so it can be simplified to [ /2, +1 ], which means that greedily dividing first leads to optimal solution
 *
 *	----------------------------
 *
 *	It can also be thought in binary representation. Doing *2 and -1 will cause us harder to build the exact binary representation
 *	of Y from X. Say we are multiplying by 2 (Left shift) and -1 (Minus last bit with 1). Say we are building up the representation
 *	for Y, and partial part of binary X is already matching Y. Now say 10000000, if we minus 1, will cause big trouble since bits
 *	has to be borrowed from MSB.
 *
 *	Instead, dividing (RIght shifting) and plus 1 Will hardly ever cause problem in building binary representation. Keep right shifting
 *	as long as Y is too long, then add 1 until whole bit representation matches
 */


class Solution {
public:
	int brokenCalc(int X, int Y) {
		if (Y < X) return X - Y;
		
		int op = 0;
		while (Y != X) {
			if (Y > X && !(Y % 2)) Y /= 2;
			else ++Y;
			++op;
		}
		return op;
	}
};