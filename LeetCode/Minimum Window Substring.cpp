#include <string>
#include <unordered_map>
using namespace std;

//https://leetcode.com/problems/minimum-window-substring/
/*
 * This is a HashMap, Two pointers (Sliding window) problem
 *
 * All of the characters occurring in t must occur in the subwindow in string s. We can construct a HashMap where characters
 * map to its frequency. The HashMap records number of characters that are still not paired in string s.
 *
 * For example, "aaab" in string t would have HashMap like
 * 		{
 * 			"a": 3,
 * 			"b": 1
 * 		}
 * This means we have 3 "a" and "b" to be included in subwindow, which is initially empty
 *
 * Now start with sliding window (two pointers). They are both initialized at leftmost of string s
 *
 * 	>	Whenever we still have no enough characters (HashMap is not yet all zero), then we will extend right pointer to include
 *		more character, hopefully to include the characters in t.
 *		If we met the character that is indeed in HashMap, decrement the frequency by 1, indicating we have less 1 character
 *		to look for, now.
 *
 *	>	Once the characters is already enough (HashMap is all zero), then this would be a valid window. However, we would try
 *		to be greedy and move the left pointer to shrink the sliding window and see whether a smaller window would also fit
 *		to be solution or not.
 *
 *  ======================================
 *
 *  There is a little optimization can be done. Since we don't even care about the characters that doesn't exist in t,
 *  we can reduce the two pointers to only iterate through characters that are only in string t.
 */


class Solution {
public:
	string minWindow(string s, string t) {
		const int len = s.length();
		int charsLeft = t.length();

		if (len < charsLeft) return "";

		// Records frequency of character left needed to form valid window. { char -> freq }
		unordered_map<char, int> freq;
		// Minimum window indices
		int minL = 0, minR = INT32_MAX;

		// Preprocess string t. Record frequency of characters in t
		for (char c : t)
			++freq[c];

		// Try to find window substring in s using two pointers
		for (int l = 0, r = -1; l < len; ) {
			// All characters is adequate in window currently. Can we shrink the size?
			if (charsLeft == 0) {
				if (freq.count(s[l])) {
					int afterShrink = ++freq[s[l]];
					if (afterShrink > 0) ++charsLeft;
				}
				++l;
			}
			// Otherwise the characters are inadequate yet in window. Expand
			else {
				++r;
				if (r >= len) break;

				if (freq.count( s[r] )) {
					int afterExpand = --freq[s[r]];
					if (afterExpand >= 0) --charsLeft;
				}
			}

			// If now charsLeft is 0, check if it is minimum window
			if (charsLeft == 0 && l <= r && minR - minL > r - l) {
				minR = r; minL = l;
			}
		}

		return (minR == INT32_MAX) ? "" : s.substr(minL, minR - minL + 1);
	}
};