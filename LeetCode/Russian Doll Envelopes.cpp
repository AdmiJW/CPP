#include <vector>
#include <algorithm>
using namespace std;

//https://leetcode.com/problems/russian-doll-envelopes/
/*
 * 	This is indeed quite hard to get intuition at, especially for a O(N log N) solution, to realize that this is a
 * 	Longest Increasing Subsequence in disguise problem
 *
 * 	---------------------------------------------------------------------------------
 *
 * 	Start by sorting the envelopes by width. This way the problem becomes solvable via straight loop thru the envelopes.
 * 	This is because at particular point in the envelopes array, I know that the previous must consist of smaller envelope,
 * 	and in front is larger envelopes which I cannot wrap in current envelope
 *
 * 	First of all, think of a DP solution. In the final maximum envelopes subsequence, one of the elements in envelopes array
 * 	must be the ending envelope. Thus, we iterate through the envelopes. In each iteration, the envelope will be the ending
 * 	envelope for the subsequence, and we'll find out what is the maximum length of prior subsequences that can be prepended
 * 	to this ending envelope, thus we use DP here
 *
 * 	Have a DP array of same size as envelopes (Except is just a 1D array). The element at index i represents if the envelope[i]
 * 	has to be ending envelope, what is the maximum length of subsequence that it can form. This is computed via having a
 * 	nested second loop which loop backwards to check each previous DP cases and whether the ending envelope for that one
 * 	is smaller than current ending envelope
 *
 * 	Therefore with this algorithm, the time complexity is O(N^2) while space used is O(N).
 *
 * 	-------------------------------------------------------------------------------------
 *
 * 	Think again about the sorted properties: In front of current point is larger envelopes, and previous ones are smaller.
 * 	Therefore, the problem for width of envelope is solved. Now, I actually just have to find out the longest increasing
 * 	height subsequence in the sorted envelopes! In other words, it is a longest increasing subsequence problem of heights!
 *
 * 	However, there is one problem: Consider [1,1], [1,2], [1,3].
 * 	If I follow suit the original sorting algorithm and apply LIS algorithm on this, the longest subsequence found will be
 * 	(1,2,3), although the width is the same and can't be counted! How to remedy this?
 *
 * 	If you smart, then you know to sort the heights by descending order, like so:
 * 		[1,3], [1,2], [1,1]
 * 	Then the longest subsequence algorithm won't be able to span anymore, and that's the behavior we want!
 *
 *
 * 	Time is reduced to O(N log N) time, with same space complexity of O(N)
 */


class Solution {
public:
	int maxEnvelopes(vector<vector<int>>& envelopes) {
		const int len = envelopes.size();
		int res = 1;

		//	Sort solely on increasing width. If width is same, sort on height so when iterate backwards, no need to consider
		//	those with higher heights'
		sort(envelopes.begin(), envelopes.end(), [](auto x, auto y)-> bool {
			if (x[0] == y[0]) return x[1] < y[1];
			return x[0] < y[0];
		});
		vector<int> dp(len);

		for (int i = 0; i < len; ++i) {
			dp[i] = 1;
			for (int j = 0; j < i; ++j) {
				if (envelopes[i][0] > envelopes[j][0] && envelopes[i][1] > envelopes[j][1])
					dp[i] = max(dp[i], dp[j] + 1);
			}
			res = max(dp[i], res);
		}
		return res;
	}


	//	DP - Patience sort solution O(N log N) solution
	int maxEnvelopes2(vector<vector<int>>& envelopes) {
		const int len = envelopes.size();

		vector<int> arr;

		//	Sort on increasing width. If width is same, sort them by decreasing height
		sort(envelopes.begin(), envelopes.end(), [](auto x, auto y) -> bool {
			if (x[0] == y[0]) return y[1] < x[1];
			return x[0] < y[0];
		});

		for (auto& env : envelopes) {
			int idx = binarySearch(arr, env[1]);

			if (idx == arr.size()) arr.push_back(env[1]);
			else arr[idx] = env[1];
		}
		return arr.size();
	}

	int binarySearch(vector<int>& arr, int hval) {
		int l = 0, r = arr.size();

		while (l < r) {
			int m = l + (r - l) / 2;
			if (arr[m] < hval) l = m + 1;
			else r = m;
		}
		return l;
	}
};