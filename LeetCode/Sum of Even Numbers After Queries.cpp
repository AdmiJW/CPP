#include <vector>
using namespace std;


//https://leetcode.com/problems/sum-of-even-numbers-after-queries/
/*
 * 	This is an array problem.
 *
 * 	Given an initial array nums[], and series of queries[], such that we have to modify one element in nums[] for each query,
 * 	and get the sum of even elements.
 *
 * 	Each element can only be in two states: even or odd. Therefore let's say we have the sum of even elements: sumEvenBefore
 * 	before we perform modification on the array.
 *
 * 	If now we have to modify one of the elements from nums[], how will it affect the even sum?
 *
 * 	1. Odd elem to Odd elem 	- sum of even remain unchanged
 * 	2. Odd elem to Even elem 	- add the changed elem to the sum
 * 	3. Even elem to Odd elem	- subtract the original elem from the sum
 * 	4. Even elem to Even elem 	- add the delta (modified - original) from the sum
 *
 *  With this algorithm, you don't have to run a linear sum scan through the array, reducing the time complexity from
 *  O(N^2) to O(N)
 */


class Solution {
public:
    vector<int> sumEvenAfterQueries(vector<int>& nums, vector<vector<int>>& queries) {
		vector<int> res(queries.size(), 0);
		int sumEven = 0;

		// Sum up initial even values;
		for (int i : nums) sumEven += (i % 2 == 0) ? i : 0;

		// For each query, determine whether to modify sumEven or not.
		// Make sure to update the nums array
		for (int i = 0; i < queries.size(); ++i) {
			auto& q = queries[i];
			int original = nums[q[1]];
			int modified = original + q[0];

			// Case 1: Original odd, modified even
			if ((original % 2 != 0) && (modified % 2 == 0)) sumEven += modified;
			// Case 2: Original even, modified odd
			else if ((original % 2 == 0) && (modified % 2 != 0)) sumEven -= original;
			// Case 3: Original even, modified even
			else if ((original % 2 == 0) && (modified % 2 == 0)) sumEven += (modified - original);

			res[i] = sumEven;
			nums[q[1]] = modified;
		}

		return res;
    }
};