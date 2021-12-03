#include <vector>
using namespace std;


//https://leetcode.com/problems/maximum-product-subarray/

/*
 * 	This is a Dynamic Programming question, similar to that of Kadane's algorithm of finding maximum sum of subarray
 *
 * 	For brute force, it's implementation is direct. For each new element introduced, start with itself and start going
 * 	backwards, multiplying each element. Then after each multiplication, compare that with the result variable.
 *
 * 	It will take O(N^2) time and O(1) time
 *
 * 	===========================================================================================================
 *
 * 	Since the moment you see maximum, it may be tied to a Dynamic Programming concept, since it involves Optimization.
 * 	Now we have to see how the answer relates to previously computed answer
 *
 * 	From bottom up, we have to introduce a new element each iteration. Now, the new element can be spread into those cases:
 * 		>	It combines with the previous maximum product subarray, which the subarray must ended with element i-1
 * 		>	Or we shall be starting a new subarray from this element
 *
 * 	Say we currently are having a positive integer. Anything multiplied with positive integer will always be bigger. That's good! Just include it!
 * 	Say we know the previous maximum subarray (which ends with element at i-1), just multiply it
 *
 * 	However, if we got a new negative integer, how would we go and find the maximum? We shall notice that negative multiply negative
 * 	will become positive, and shall be viewed as two positive integers multiplied together. Problem is, how do we know if there's a
 * 	suitable negative integer before already for us to multiply into?
 *
 * 	The solution is somehow direct but ingenious: Aside from keeping track of the maximum, ALSO KEEP TRACK OF THE MINIMUM.
 * 	Since the minimum shall usually be negative of largest magnitude, multiplying a negative integer into it will make it
 * 	the largest magnitude positive product!
 *
 * 	This is not all. If we implement the logic to only check like so:
 * 		if (positive)
 * 			max = prevMax * thisNum
 * 			min = prevMin * thisNum
 * 		else if (negative or 0)
 * 			max = prevMin * thisNum
 * 			min = prevMax * thisNum
 *
 * 	Consider the case:
 * 		1, 0, 10
 *
 * 	After the 0, both the prevMax and prevMin shall be 0. Since it got multiplied by 0. (Kadanes algorithm requires the DP to always
 * 	involve the last element).
 * 	Now on to element 10, if we go with the above algorithm, then all subsequent answers will always be 0, since we are multiplying
 * 	with 0!
 * 	To resolve this, just make a comparison whether to start a new subarray with current element
 *
 * 		if (positive)
 * 			max = max( thisNum, prevMax * thisNum)
 * 			min = min( thisNum, prevMin * thisNum)
 * 		else if (negative or 0)
 * 			max = max( thisNum, prevMin * thisNum)
 * 			min = min( thisNum, prevMax * thisNum)
 */

class Solution {
public:

    int maxProduct(vector<int>& nums) {
        int prevMax = nums[0];
        int prevMin = nums[0];
        int res = nums[0];

        for (int i = 1; i < nums.size(); ++i) {
            int n = nums[i];
            int newMax = max(n, max(prevMax * n, prevMin * n));
            int newMin = min(n, min(prevMax * n, prevMin * n));
            prevMax = newMax;
            prevMin = newMin;

            res = max(prevMax, res);
        }

        return res;
    }

};