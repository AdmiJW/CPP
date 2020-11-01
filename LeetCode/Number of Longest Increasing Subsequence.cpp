#include <vector>
#include <cmath>


/*
 * 	This is a Dynamic Programming Problem (DP), and possibly more advanced, segment tree problem.
 *
 * 	Whenever we see the maximum problem and also subsequence, we can almost get that this might be an DP question.
 *
 * 	For each element in the array, it might be able to connect with one among previous subsequences available in the
 * 	array. To achieve this, we can iterate backwards one by one to check the suitable candidates to form subarray with.
 *
 * 	Now, let's say we found a suitable candidate. How do we know once we connected the element with previous subsequnce,
 * 	what is the length of the final subsequence, and how many subsequences of such length is created?
 * 	This is where DP comes in. With DP, we already assume we know the answers to previous subproblems. That is,
 * 		>	The maximum length subsequence that can be formed with this element as the ending element
 * 		>	The number of subsequences that can be formed with such maximum length, and this element as the ending element
 *
 * 	When we form subsequence with said previous element,
 * 		>	The length of resulting subsequence would be:				prev max length + 1 (current element)
 * 		>	The count of resulting subsequence would actualy be same; How many subsequences previously, we append an element
 * 			to all of them. The count doesn't change.
 *
 * 	With those information in power, when we finished iteration backwards, we shall already know two things:
 * 		>	The length of maximum subsequence ending with current element
 * 		>	The number of subsequences with this maximum length, formed with current element as last element.
 * 	Which is exactly the answer to the current subproblem of DP!
 * 	Also, since DP does not directly solve the actual problem, We have to compare each subproblem answer to the global answer.
 * 	THat is,
 *
 * 		If the current subproblem's maximum length is equal to global maximum length, then add the count of possible
 * 		subsequences that can be formed into global count.
 * 		Otherwise, if the current subproblem's maximum length is GREATER than global maximum length, we actually have to
 * 		update the global maximum, reset the global count to the subproblem's count
 */


class Solution {
public:

    int findNumberOfLIS(std::vector<int>& nums) {
        const int len = nums.size();

        int globalLen = INT_MIN;        //  The global longest substring length.
        int globalCnt = 0;                 //  The global count for longest substring

        int* dplen = new int[len];      //  Stores the maximum length substring can be formed by this as last element
        int* dpcnt = new int[len];      //  Stores the number of maximum length substring can be formed by this last element

        for (int i = 0; i < len; i++) {
            int n = nums[i];

            int localLen = 1;       //  Will be storing the maximum length substring met so far with this element.
            int localCnt = 1;       //  Will be storing the number of maximum length substring met so far with this element

            for (int j = i - 1; j >= 0; j--) {
                if (nums[j] >= n) continue;

                int lenFormed = dplen[j] + 1;       //  We combine this element with the said previous element, this is length of
                                                    //  of subsequence formed
                if ( lenFormed == localLen) localCnt += dpcnt[j]; //  Formed the maximum subsequence
                else if ( lenFormed > localLen) {
                    localLen = lenFormed;
                    localCnt = dpcnt[j];            //  The count becomes the count of maximum length subsequence of that prev element
                }
            }

            dplen[i] = localLen;
            dpcnt[i] = localCnt;

            if (globalLen == localLen) globalCnt += localCnt;
            else if (localLen > globalLen) {
                globalLen = localLen;
                globalCnt = localCnt;
            }
        }
        return globalCnt;
    }

};