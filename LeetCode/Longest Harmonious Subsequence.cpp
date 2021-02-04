#include <vector>
#include <unordered_map>

using namespace std;


//https://leetcode.com/problems/longest-harmonious-subsequence/
/*
 * 	This is an Array, HashMap problem.
 *
 * 	Once such brute force-y way to solve is, consider we fix the starting element of the subsequence, say N.
 * 	Then, the subsequence now can only consist of N or N+1 or N-1.
 *
 * 	So, for each element,
 * 		>	Fix the first element. The subsequent element can only have N+1 or N-1 now.
 * 		>	For each element after, we have 2 cases: N is the maximum (accept N or N-1), or minimum (accept N or N+1)
 * 		>	Count the occurrences of each one.
 * 		>	Update the global maximum if N+1 exist, or N-1 exists.
 *
 * 	Time complexity is O(N^2), although in constant extra space
 *
 * 	--------------------------------------------------------------------------------------
 *
 * 	What if we record the previously seen results? This makes result retrieval O(1) for each element!
 *
 * 	Iterate through the array. The current element will be the last element in the subsequence. Check the HashMap
 * 	which records the frequency of each value:
 *
 * 		freq(N-1) + freq(N)
 * 		freq(N+1) + freq(N)
 *
 * 	if N-1 and N+1 exists, that is.
 *
 * 	We are trading time complexity with space complexity. The space complexity is O(T) where T is number of differnet
 * 	values in the array. Time becomes O(N)
 */


class Solution {
public:

	//	Brute force-y solution
	//	O(N^2) time albeit O(1) space
	int findLHS(vector<int>& nums) {
		const int len = nums.size();
		int res = 0;

		for (int i = 0; i < len; ++i) {
			int cntN = 0;
			int cntOneBig = 0;
			int cntOneSmall = 0;

			for (int j = i; j < len; ++j) {
				if (nums[j] == nums[i]) ++cntN;
				if (nums[j] == nums[i] - 1) ++cntOneSmall;
				if (nums[j] == nums[i] + 1) ++cntOneBig;
			}

			if (cntOneBig) res = max(cntOneBig + cntN, res);
			if (cntOneSmall) res = max(cntOneSmall + cntN, res);
		}
		return res;
	}


	//	HashMap one pass solution
	//	Although two pass may be faster due to one value only get checked once
	int findLHS2(vector<int>& nums) {
		unordered_map<int, int> freq;
		int res = 0;

		for (int n : nums) {
			int curr = freq[n] + 1;
			freq[n] = curr;

			if (freq[n - 1])
				res = max(freq[n - 1] + curr, res);
			if (freq[n + 1])
				res = max(freq[n + 1] + curr, res);
		}
		return res;
	}
};