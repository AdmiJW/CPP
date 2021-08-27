#include <string>
#include <vector>
using namespace std;

//https://leetcode.com/problems/longest-uncommon-subsequence-ii
/*
 * This is a String, Two pointers problem.
 *
 * Since the input size is small, we could brute force our way.
 * To check whether a string is subsequence of another string, we could use two pointers technique.
 * Pointer l is on the potential subsequence string sub, while pointer r is on the longer string s.
 * Whenever character on l is same as the one on the r pointer, move the l pointer forward.
 * When pointer l successfully passed all the characters in sub, that means sub is indeed a valid subsequence.
 *
 * For each of the string in array, it could be the longest uncommon subsequence. Therefore, we run another
 * iteration to check if it is indeed the case.
 *
 * This solution runs in O(N^2 * L) time, where N = number of strings in array, L = avg length of words
 *
 * -----------------------
 *
 * To allow for early termination, we may choose to sort the strings by length first. Iterating from longest
 * string to shortest, once we found such string that is uncommon, we can return early.
 *
 *
 */

class Solution {
public:
    int findLUSlength(vector<string>& strs) {
		int res = -1;

		for (int i = 0; i < strs.size(); ++i) {
			bool isUncommon = true;

			for (int j = 0; j < strs.size(); ++j) {
				if (i == j) continue;

				if (isSubsequence( strs[i], strs[j])) {
					isUncommon = false;
					break;
				};
			}
			if (isUncommon) res = max(res, (int)strs[i].length());
		}
		return res;
    }

    bool isSubsequence(string& sub, string& s) {
		if (sub.length() > s.length()) return false;

		// Two pointers in both string
		int l = 0, r = 0;

		while (l < sub.length() && r < s.length()) {
			if (sub[l] == s[r])
				++l;
			++r;
		}
		return l == sub.length();
    }
};