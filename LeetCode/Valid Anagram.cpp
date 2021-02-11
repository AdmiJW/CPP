#include <algorithm>
#include <string>
using namespace std;


//https://leetcode.com/problems/valid-anagram/
/*
 * 	This is a Hash map / Sorting problem.
 *
 * 	Determine if it is anagram simply means to check if frequency of characters in both strings are equal.
 * 	Thus, there are ways to do this:
 *
 * 	1. Sorting
 *
 * 	After sort, if the frequency are really identical, both sorted strings shall be identical. Time complexity is
 * 	O(N log N) where N is length of string. Although merge or quick sort takes O(log N) space, usually assumed is O(1)
 *
 *
 * 	2. Hash Table.
 *
 * 	Use a Hash table to record frequency of characters in both string. At the end, frequency shall match correspondingly.
 *	Furthermore, since there is only 2 strings, we can make one string be adding and the other subtracting. If the
 *	frequencies truly match, at the end the frequencies should be 0.
 */


class Solution {
public:
	bool isAnagram(string s, string t) {
		if (s.length() != t.length()) return false;

		sort(s.begin(), s.end());
		sort(t.begin(), t.end());

		return !s.compare(t);
	}
	

	bool isAnagram2(string s, string t) {
		if (s.length() != t.length()) return false;

		int counter[26] = {};
		for (int i = 0; i < s.length(); ++i) {
			++counter[s[i] - 'a'];
			--counter[t[i] - 'a'];
		}

		for (int i : counter) if (i) return false;
		return true;
	}
};