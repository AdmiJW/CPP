#include <unordered_set>
using namespace std;

//https://leetcode.com/problems/power-of-three/
/*
 * 	This is a Math problem.
 *
 * 	The native algorithm already runs in O(log3 N) time, via iteration or recursion by simply repeatedly
 * 	dividing the original n, given that it is not negative to begin with
 *
 * 	Some other methods are using logarithm to check if the power is actually an integer. If it is not, then
 * 	it is not valid power of three. However time complexity depends on the language implementation
 *
 * 	Also, we could convert number into base 3, and check if it leads with a single '1' digit followed by all zeros.
 *
 * 	Since by doing some math you know the number of solutions is relatively small, you can use HashSet for this job.
 *
 * 	Lastly the most hardest solution, is that realize 3 is a prime number, and prime x prime is also prime.
 * 	Therefore, first you know the upper bound of problem is only until INT_MAX, which the highest power of 3 is 3^19.
 * 	Then, for a number N to be valid power of 3 which is prime, it must be able to divide 3^19. Check with modulo
 */

class Solution {
public:
	bool isPowerOfThree(int n) {
		if (n < 0) return false;
		while (n > 1 && !(n % 3))
			n /= 3;
		return n == 1;
	}

	//	Recursive method
	bool isPowerOfThree2(int n) {
		if (n == 1) return true;
		if (n < 1 || n % 3) return false;
		return isPowerOfThree(n / 3);
	}


	//	Idea: 3 is prime. prime x prime is also prime. So check divisibility of 3^19 (Bounded)
	bool isPowerOfThree4(int n) {
		return n > 0 && !(1162261467 % n);
	}
};