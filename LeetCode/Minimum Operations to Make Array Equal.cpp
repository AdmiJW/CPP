//https://leetcode.com/problems/minimum-operations-to-make-array-equal/
/*
 * 	This is simply a math teaser. Make sure you open the arithmetic sequence topic textbook from your school times!
 *
 * 	First, think about it: The array is 100% an array of odd numbers, like [1,3,5,7,9...]
 *
 * 	Note that we can obtain the largest element by simply 2n-1. This formula is deduced from the arithmetic sequence formula
 * 		a + (n-1)d
 *
 * 	Now, turns out the minimum operation to perform is to reduce all numbers, to the MEAN. Eg: [1,3,5,7,9] mean is 5.
 * 	Also turns out, mean can be calculated in odd arithmetic sequences simply by taking the largest element,
 * 	L (calculated above), divide 2 and add 1.
 *
 * 		Mean = (L/2) + 1
 *
 * 	With the mean obtained, we want convert all numbers to the mean! It should take minimum operations that way
 * 		Eg: [1,3,5,7,9] to [5,5,5,5,5]
 * 			and [1,3,5,7,9,11] to [6,6,6,6,6,6]
 *
 * 	Since operations allowed are to +1 and -1 to two elements simultaneously, we can set the mean as a 'mirror'. While we
 * 	+1 in one element on left side, we -1 in one element on the right side.
 *
 * 		Eg: [1,3,5,7,9]. If I +1 to 3, then I'll -1 to 7
 *
 * 	Therefore to obtain answer, I simply find out how many times I gonna add +1 to the left half side of array is enough!
 * 	Since the very same operation is reflected on the right side.
 * 	Now, the length of the left side of array is easily obtained by:
 * 		n/2
 *
 * 		Eg:	[1,3,5,7,9],		 n/2 = 2, left side = [1,3]
 * 		Eg: [1,3,5,7,9,11], 	 n/2 = 3, left side = [1,3,5]
 *
 * 	Now, to make them equal to mean, we perform the operations based on length of array. See:
 *
 * 	>	Odd array of [1,3,5,7,9], LHS: [1,3] Operations: [+4, +2]
 * 		It is an array of even numbers!
 *
 * 	>	Even array of [1,3,5,7,9,11], LHS: [1,3,5] Operations: [+5, +3, +1]
 * 		It is an array of odd numbers!
 *
 * 	Through arithmetic sequence formula again, we obtain the following result:
 * 		Even: No of operations required is (LHS length)^2
 * 		Odd:  No of operations required is (LHS length)^2 + (LHS length)
 */

class Solution {
public:
    int minOperations(int n) {
        int length = n / 2;
        return length * length + ((n % 2 == 0) ? 0 : length);
    }
};