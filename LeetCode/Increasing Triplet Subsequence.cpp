#include <vector>
using namespace std;

//https://leetcode.com/problems/increasing-triplet-subsequence/

/*
 * 	This is a Array, with a little mix of dynamic programming element inside.
 *
 * 	The most brute force solution would be for each element, try to find the another two pair. Time is O(N^3), and it
 * 	obviously results in time out
 *
 * 	------------------------------------------------------------------
 *
 * 	Looking at the problem, we can notice that we can iterate the array from left to right, keeping track of the
 * 	minimum element, and the iterating element we're on means the second element. How do we know that there is a
 * 	third number which is larger after current element?
 * 	Using O(N) space, we can have an array record the largest element from current index until the rightmost end.
 * 	This way by iterating the array, we can simultaneously know the min element to the left, current element and
 * 	max element to the right. This way it can be solved.
 *
 * 	----------------------------------------------------------------------
 *
 * 	My attempt for O(N) and O(1) goes as follows. The same concept of recording minimum element still applies, and we
 * 	are iterating on each element as the second element. How are we able to find out the third larger element?
 *
 * 	The idea is, from the current element, attempt to find the next 2 subsequence elements that are strictly increasing.
 * 	Say we have
 * 			10, 1, 5, 4, 3, 2, 6
 * 	When we reach element 5, The min recorded is 1 and current element is 5. Since it is strictly increasing 2 elements,
 * 	we try to find the increasing subsequence starting from the element 5 itself
 *
 * 	By applying same technique, we would end up with minimum 2 and the increasing element is 6. We can make observations:
 *
 * 	>	If the minimum of next increasing subsequence is already greater than the first min, then immediately it forms
 * 		3 increasing subsequence already. Return true
 *
 * 	>	If it is not, then we iterate backwards once more to find out if there is a element that is greater than first
 * 		min. If there is, then surely the three increasing subseqence is already found. Return true.
 *
 * 	>	Otherwise not found. Since the next increasing subsequence we already found, and the minimum is less than or equal
 * 		to first min,
 * 			-	We set first min to the found minimum
 * 			-	We immediately jump the current pointer to the second large element in the second increasing subseqence
 * 				found.
 *
 * 	This way each element is at most iterated 3 times, thus is O(N) time and O(1) space.
 *
 * 	-----------------------------------------------------------------------
 *
 * 	The ingenious solution is the most seemingly naive one.
 * 	Initialize n1 and n2 to be infinity
 *
 * 	>	If the element is greater than n2, return true
 * 	>	Else if the element is less than n1, set n1 to be element
 * 	>	Else if the element is greater than n1, set n1 to be n2
 *
 * 	Why this works?
 *  See this case [1,2,0,3]
 *
 *	At the end, n1 = 0, n2 = 2, and returned true at 3. Doesn't seem right, but still, it works actually!
 *
 *	Notice that n2 is set due to the fact that there existed n1 that is less than n2.
 *	Even if we overwrite n1, it doesn't change the fact that the prior larger n1 existed, DUE to the entire premise that
 *	n2 is ALREADY SET due to prior n1!
 *  We are returning true by checking n2 itself! The fact that n2 exists must mean that a smaller element existed before!
 *
 *	Now when n2 is overwrite, it is completely valid due to it being a later element than n1 now.
 */


class Solution {
public:
    bool increasingTriplet(vector<int>& nums) {
        const int len = nums.size();
        vector<int> maxElem(len, 0);
        maxElem[len - 1] = nums[len - 1];

        for (int i = len - 2; i >= 0; --i)
            maxElem[i] = max(maxElem[i + 1], nums[i]);

        int minE = nums[0];
        for (int pt = 1; pt < len - 1; ++pt) {
            if (minE < nums[pt] && maxElem[pt + 1] > nums[pt])
                return true;
            minE = min(nums[pt], minE);
        }
        return false;
    }




    bool increasingTriplet2(vector<int> nums) {
        const int len = nums.size();
        int min = nums[0];
        int curridx = 1;

        while (curridx < len - 1) {
            if (min < nums[curridx]) {

                int localmin = curridx;
                int localidx = curridx + 1;

                while (localidx < len && nums[localidx] <= nums[localmin])
                    localmin = localidx++;

                if (localidx >= len) return false;  //  No more increase subsequence until end. Impossible case
                if (nums[localmin] > min) return true;

                // We have found a increasing subsequence, but the min value been reduced to smaller than min.
                // Run a last backwards iteration to ensure that there is one element larger than min, but smaller than
                // the larger element found
                for (int i = localidx - 1; i >= curridx; --i)
                    if (nums[i] >= nums[curridx] && nums[i] < nums[localidx]) return true;

                min = nums[localmin];
                curridx = localidx;
            }
            else
                min = nums[curridx++];
        }
        return false;
    }




    bool increasingTriplet3(vector<int> nums) {
        int first = INT32_MAX, second = INT32_MAX;
        
        for (int i = 0; i < nums.size(); ++i) {
            if (nums[i] > second) return true;
            else if (nums[i] < first) first = nums[i];
            else if (nums[i] != first) second = nums[i];
        }
        return false;
    }
};