#include <vector>
#include <unordered_set>
#include <algorithm>
#include <string>
using namespace std;

//https://leetcode.com/problems/stamping-the-sequence/
/*
 * 	This is a Greedy, String iteration problem.
 *
 * 	Think of chopping stamps. Say If I have 'abcdef' and I chop 'zzz' starting at index 1, then string becomes
 * 	'azzzef'.
 * 	Notice how zzz essentially replaces 'bcd', we can think of it as a layer of 'zzz' being stacked on top of it!
 * 	Now, target is formed by stamping multiple times, thus, it is like a stack of stamping layers!
 *
 * 	Therefore, the intuition is that, we can simply 'unstack' the layers. In other words, if we can reverse the target
 * 	back into "??????", then our job is done!
 *
 * 	The algorithm then becomes:
 * 		While there is still stamping layer, aka not all characters are unstamped, we shall iterate:
 * 			Check all substrings of same size as stamp. Check if they can be unstamped or not
 * 			If they can be unstamped, unstamp by replace the characters by wildcard like '*'
 *
 *	Note that unstamped characters are replaced by '*', so in future iterations, stamp 'abc' is able to match 'a**' or 'ab*'
 *	or '**c'. However, we shouldn't match '***' because the entire substring is already unstamped before!
 */


class Solution {
	vector<int> movesToStamp(string stamp, string target) {
		const int slen = stamp.length();
		const int tlen = target.length();

		int charStamped = 0;
		unordered_set<int> stamped;
		vector<int> res;

		while (true) {
			bool isInserted = false;

			for (int i = 0; i <= tlen - slen && !isInserted; ++i) {
				if (stamped.count(i)) continue;
				if (matches(stamp, target, i)) {
					stamped.insert(i);
					res.push_back(i);
					charStamped += unstamp(target, i, slen);
					isInserted = true;
				}
			}
			if (!isInserted) return vector<int>();
			if (charStamped == tlen) break;
		}

		reverse(res.begin(), res.end());
		return res;
	}

	bool matches(const string& stamp, const string& target, int idx) {
		for (int i = 0; i < stamp.length(); ++i) {
			if (target[i + idx] != stamp[i] && target[i + idx] != '*')
				return false;
		}
		return true;
	}


	int unstamp(string& target, int idx, int len) {
		int count = 0;
		for (int i = 0; i < len; ++i) {
			if (target[idx + i] != '*') ++count;
			target[idx + i] = '*';
		}
		return count;
	}
};