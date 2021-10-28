#include <vector>
#include <algorithm>
using namespace std;

//https://leetcode.com/problems/3sum/
/*
 * 	My first try is to seperate the numbers into the 3 sections: Positive, zero, and Negative. Iterate through the array and put them into respective map
 * 	which maps from the value to the frequency. For the value zero just a counter is enough.
 *
 * 	Now notice the key for a three sum. For any positive integer, there must be AT LEAST ONE negative integer for it to reduce it to zero. This goes the same
 * 	for negative integer, which must have one positive integer to increase it to zero.
 * 	This decrease the possibility of combination down to 4 of them:
 * 		-Positive, Positive, Negative
 * 		-Positive, Negative, Negative
 * 		-Positive, Zero, Negative
 * 		-Zero, Zero, Zero
 *
 * 	Therefore we will iterate the positive integer keysets of unique values, and from negative integer keysets of unique value, check if the third number that
 * 	reduce the pair to zero exists or not. If the targeted integer is same as the positive int or negative int selected, we have to check the frequency of it is
 * 	greater than 2 or not.
 * 	A crucial point is it can cause duplicate issues. Selecting 1 as positive and -3 as negative will make combination of [1, -3, 2]
 * 											 	Later, Selecting 2 as positive and -3 as negative will make combination of [2, -3, 1]
 *
 * 	A way to solve this is to enforce a rule where the target must be less than the negative int or greater than the positive int for it to pass the test and
 * 	create a combination. Since from the 2 duplicate combinations are of two different int, it must have 1 of the combination to be true for it to pass the test
 * 	while the other will fail.
 *
 * --------------------------------------------------------------------------------------------------------------------------------------
 *
 * 	The real solution is to first sort the array. Then we have to iterate the non-positive part of the array one by one to choose the first num.
 * 	Remember to check if the current first number is same as previous (Duplicate), if it's duplicate, skip this iteration and go forward
 *
 * 	Now the first number is selected, we can know the target to find is actually -(n1), negative of first integer. From here, use two pointers where left pointer is
 * 	first number index + 1, and right pointer is end of array. Note this sorted array pattern:
 *
 * 	More negative									More positive
 * 	------------------------------------------------------------>
 *
 * 	Therefore we can find the sum of number of the 2 pointers. If it is equal to target, then append this 3 pairs to the result array, and move the left and right
 * 	pointer until there is no duplicates, which will be checked again
 * 	If the sum of two number is greater than target, that means the right pointer is too big perhaps, try to decrement right pointer
 * 	If the sum of two number is lesser than target, that means the left pointer is too small perhaps, so try to increment the left pointer
 *
 * 	Until the first number iterates until positive number, which means the integers to right side is always positive, that is impossible to form zero therefore we
 * 	can safely break and return result here.
 *
 */

class Solution {
public:

    vector<vector<int>> threeSum(vector<int>& nums) {
        const int len = nums.size();
        vector<vector<int>> res;

        // Necessary: Sort the array
        sort(res.begin(), res.end());

        // Fixing the first number at index i
        for (int i = 0; i < len; ++i) {
            // Since 3 sum must contain negative number or 0, if current is already positive, we exit early
            if (nums[i] > 0) return res;
            // Skip duplicates, we cannot have duplicate 3 sums
            if (i && nums[i] == nums[i - 1]) continue;

            // Use two pointers to locate the second and third element respectively.
            int l = i + 1, r = len - 1;
            while (l < r) {
                // Skip duplicates on both pointers.
                if (l != i + 1 && nums[l - 1] == nums[l]) ++l;
                else if (r != len - 1 && nums[r + 1] == nums[r]) --r;
                else {
                    int sum = nums[l] + nums[r] + nums[i];

                    // Exact match. Append result
                    if (!sum) {
                        res.push_back({ nums[l], nums[r], nums[i] });
                        ++l; --r;
                    }
                    // Too large. Reduce right pointer
                    else if (sum > 0) --r;
                    // Too small. Increase left pointer
                    else ++l;
                }
            }
        }
        return res;
    }

};