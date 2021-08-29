#include <vector>
using namespace std;

//https://leetcode.com/problems/patching-array/
/*
 * 	This is a Hard Greedy problem. The idea is hard to come up with, but the implementation is rather
 * 	simple
 *
 * 	Firstly, you must realize:
 * 		>	If your current array is able to form any number between [1...n], then if you add an element
 * 			k into it, then suddenly you are able to form any number between [1...n+k] already, since:
 *
 * 			- [1..n] is already formable without k
 * 			- To form k, use k itself.
 * 			- To form [k+1...n+k], use k itself + [1..n]
 *
 * 	Using this property, we can keep track of the current range that our array covered. Since the array is
 * 	already sorted, it is already convenient.
 *
 * 	Initially, our missing number is 1. Say first element is 1, that means we can form [1..1]. Update missing
 *	number to 2.
 *	Next number is 2. Thus, we are able to form [1..3] (Sum of elements). Update missing number to 4.
 *	If next number is 9, we quickly realize we cannot form the missing number 4. Therefore, we would use greedy
 *	and add 4 into it. Suddenly, we can form [1..7]. Update missing number to 8.
 *
 *		Why add 4 and not other numbers? See: Our missing number so far is 4
 *		If we add 1,2 or 3, it is plausible, but since we are greedy and want to extend as much as possible,
 *      4 gives us best choice.
 *      If we add 5,6,7,8..., the missing number 4 still won't be patched!
 *
 *	Since 8 still can't be formed, add 8 into array. Now we can form [1..15]. Missing number now becomes 16.
 *
 *	Repeat this process until the next missing number is larger than n. That means we have covered all numbers
 *  from [1..n]
 */

class Solution {
public:
	int minPatches(vector<int>& nums, int n) {
		long long int patches = 0, range = 0;
		int index = 0;

		while (range < n) {
            // The current missing number is (range+1). 
                        // If the next element in array is smaller, we would extend our range.
            if (index < nums.size() && nums[index] <= range + 1) {
                range += nums[index];
                ++index;
            }
            // Otherwise we detected that missing number is impossible to form. Patch the missing 
            // number and extend the range.
            else {
                range += range + 1;
                ++patches;
            }
        }
        return (int)patches;
	}
};