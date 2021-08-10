#include <string>
#include <vector>
using namespace std;

//https://leetcode.com/problems/flip-string-to-monotone-increasing/
/*
 * 	This is a Dynamic Programming problem.
 *
 * 	Let's approach this bottom up:
 *  Although it is not obvious, to convert the string s of size N depends on the solution to converting string s of size N-1.
 *
 *  See:
 *  	Say I have string s of size N I want to convert to a monotonic string. Also, I know for a fact that previously computed
 *  	solution of size N-1, is already valid monotonic string.
 *
 *  	Now, I have 2 choices:
 *  		>	For latest character, I want it to be ending with '0' and remain a valid monotonic string
 *  		>	For latest character, I want it to be ending with '1' and remain a valid monotonic string
 *
 * 	In case 1, it is no other than
 * 		DP(End with 0) + (1 if need to convert else 0)
 * 	In case 2,
 * 		min(DP(End with 0), DP(End with 1) ) + (1 if need to convert else 0)
 *
 *  ==================================================
 *
 *  Another DP way of solving is using prefix sum, more precisely, cumulative frequency of 0.
 *
 *  If we know how many 0's in the substring up to any length N, we can deduce many informations out of it.
 *
 *  Once we obtain the frequency array, we can attempt all possible number of 0's in final result and check which one is minimum
 */

class Solution {
public:
	int minFlipsMonoIncr(string s) {
		int dpLatest0 = 0;
		int dpLatest1 = 0;

		for (char c : s) {
			int newDPLatest0 = dpLatest0 + (c == '1');
			int newDPLatest1 = min(dpLatest0, dpLatest1) + (c == '0');

			dpLatest0 = newDPLatest0;
			dpLatest1 = newDPLatest1;
		}
		return min(dpLatest0, dpLatest1);
	}


	int minFlipsMonoIncr2(string s) {
		// prefix0[i] means number of 0's up to string index i-1. Index 0 is always 0
		vector<int> prefix0(s.length() + 1, 0);
		int res = INT32_MAX;

		// Fill prefix sum
		for (int i = 0; i < s.length(); ++i)
			prefix0[i + 1] = prefix0[i] + (s[i] == '0');

		// Consider all possible number of 0 in final result
		for (int i = 0; i <= s.length(); ++i) {
			int leftSegment1 = i - prefix0[i];
			int rightSegment0 = prefix0[s.length()] - prefix0[i];

			res = min(res, leftSegment1 + rightSegment0);
		}
		return res;
	}
};