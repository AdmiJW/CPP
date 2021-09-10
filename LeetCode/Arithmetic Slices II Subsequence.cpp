#include <vector>
#include <unordered_map>
using namespace std;

typedef long long int LONG;

//https://leetcode.com/problems/arithmetic-slices-ii-subsequence/
/*
 * 	This is a Dynamic Programming problem.
 *
 * 	For brute force, we essentially pick every element to be start of subsequence, then making choices:
 * 	whether to or not to include the element. This ends up O(2^N) time complexity.
 *
 * 	-------------------------------------------
 *
 * 	For every element i in the array nums, it can do two things:
 * 	1. It can extend any previous formed subsequence (if valid). This requires us to have knowledge about
 * 	   all the previously formed subsequence beforehand - The number of subsequences that can be extended
 * 	   by current element i.
 *
 *  2. It can choose ANY previous element to form a new subsequence of length 2, which can be extended by
 *  	future elements.
 *
 *  My initial implementation is to have nested HashMap as my DP array. DP[i] will store information on
 *  how many subsequences can be extended if the current element is i.
 *  However, extended subsequences can be further extended by future elements too! For this, DP[i] will
 *  instead also be a HashMap that maps (difference)->(count). Once extended, the extended subsequence
 *  can be further extended if element (i + difference) is met.
 *
 *  However, my solution passes all but several test case. A mystery until now.
 *
 *  ---------------------------------------------
 *
 *  The official solution instead keeps a HashMap on each of the elements. It maps to number of subsequences
 *  by their arithmetic difference. Eg: DP[i].get(5) represents number of subsequences that end at element index
 *  i, that has arithmetic difference of 5.
 *
 *  For every element i in iteration, we look backwards each element j from 0 up to but not include i. Calculate
 *  their difference, and see if a extended subsequence can be formed from j to i or not.
 */


class Solution {
public:
	int numberOfArithmeticSlices(vector<int>& nums) {
		const int len = nums.size();
		int res = 0;
		vector< unordered_map<int, int>> mapper(len);

		for (int i = 1; i < len; ++i) {
			for (int j = 0; j < i; ++j) {
				LONG diff = (LONG)nums[i] - nums[j];
				if (diff < INT32_MIN || diff > INT32_MAX) continue;

				// Extendable is simply how many subsequences that this element can extend
				int extendable = 0;
				if (mapper[j].count(diff)) {
					extendable = mapper[j][diff];
					res += extendable;
				}
				mapper[i][diff] += extendable + 1;
			}
		}
		return res;
	}
};