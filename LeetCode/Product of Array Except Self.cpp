#include <vector>
using namespace std;

//https://leetcode.com/problems/product-of-array-except-self/
/*
 * 	This is a prefix/suffix sum(multiplication) array problem.
 *
 * 	If we can use division, then the problem is going to be easier. We simply run a first iteration to obtain the
 *	product of all numbers nums[0] * nums[1] * nums[2] ... nums[n].
 *	Then for each index i, answer would be just (products / nums[i])
 *
 *	---------------------------------------------------------
 *
 *	To do it without division, we reformulate the formula:
 *		nums[i] = (prefix multiplication up to i-1) * (suffix multiplication up to i+1)
 *
 *	As we know, suffix or prefix can be done in O(1) space via a variable. However, knowing both at the same time cannot
 *	be done in O(1) space.
 *
 *	Initialize an result array. In first iteration, initialize it with prefix multiplications of array nums.
 *	In the second pass, we iterate backwards while keeping track of suffix multiplication. At every index i, the
 *	result would then be (prefixMult[i-1] * suffixMult)
 */

class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
		const int len = nums.size();
		vector<int> res(len, 0);

		// Initialize res with prefix multiplication first
		res[0] = nums[0];
		for (int i = 1; i < len; ++i)
			res[i] = res[i - 1] * nums[i];

		// At index i, the result is (prefix multiplication) * (suffix multiplication)
		int suffix = 1;
		for (int i = len - 1; i > 0; --i) {
			res[i] = res[i - 1] * suffix;
			suffix *= nums[i];
		}

		res[0] = suffix;
		return res;
    }
};