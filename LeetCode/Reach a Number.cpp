//https://leetcode.com/problems/reach-a-number/
/*
 * 	This is more of a mathematical problem than a coding one.
 *
 * 	Consider a target. Some key points to realize:
 *
 * 	-	Since we are just finding shortest steps to reach target, if the target is negative, change it to positive
 * 		as the solution to the positive can be swapped signs to reach negative answer
 *
 *	-	A target, t (Now positive), must involve 1,2,3,4,5... c sum in it. Just we don't know the signs of 1,2,3,4,5...c
 *		whether it should add or subtract.
 *
 *	The apporach is, keep summing up 1,2,3... until we reach a point where it exceeds (or match exactly) the target t.
 *	This means we have to subtract some value inside 1,2,3... by flipping sign.
 *
 *	The overflow must be less than the most recently added number. Consider now we sum at X, and we add 10 to target
 *	where in worst case,would just be X+1. The overflow s just X+1 - (X+10) = -9, which in magnitude is just less than
 *	10 we just added.
 *
 *	Now, if the delta (Overflowed value) is even, this means we can easily switch one of the matching even value in the
 *	equation, and it will definitely now match. Return c in this case (Most recently added value)
 *
 *	If it is not, we attempt the next value C+1. If overflow is still odd, it must be C+2 then as it is even alreeady.
 *	Otherwise, C+1 it is.
 */



class Solution {
public:
	int reachNumber(int target) {
		target = target < 0 ? -target : target;
		int c = 0;

		while (target > 0)
			target -= ++c;

		target = target < 0 ? -target : target;
		
		if (!(target % 2)) return c;
		else if (!((target + c + 1) % 2)) return c + 1;
		return c + 2;
	}
};