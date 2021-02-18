#include <vector>
using namespace std;

//https://leetcode.com/problems/arithmetic-slices/
/*
 *	This is considered a Dynamic Programming problem
 *
 *	Think about it, every element can be starting of a new arithmetic, like so:
 *			1,2,3,4,5,7 		<- In this case, 7 is starting a new arithmetic of difference 2
 *	Or the element can extend the previous arithmetics:
 *			1,2,3,4,5 			<- In this case, 5 is extending the arithmetic
 *
 *	Let's think what each case we need to do:
 *
 *	>	If it is extending the previous arithmetic, we have to know the length of the previous streaks:
 *			1,2,3,4,(5)
 *
 *		Now the streak length becomes 5. Assume the previous combinations are already included, now we
 *		simply have to add number of arithmetics that includes element (5), which is (1,2,3,4,5), (2,3,4,5)
 *		and (3,4,5). Thus formula is N-2
 *
 *	>	If it is starting new arithmetic, it is no longer possible to extend previous arithmetic so we discard
 *		and reset our streak. Set the difference to be new, and reset streak length to be 2.
 */

class Solution {
public:
	int numberOfArithmeticSlices(vector<int>& A) {
		const int len = A.size();
		int res = 0;
		int diff = INT32_MIN;
		int streak = 0;

		for (int i = 1; i < len; ++i) {
			if (A[i] - A[i - 1] != diff) {
				diff = A[i] - A[i - 1];
				streak = 2;
			}
			else {
				++streak;
				res += streak - 2;
			}
		}
		return res;
	}
};