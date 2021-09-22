#include <vector>
#include <algorithm>
#include <string>
using namespace std;

//https://leetcode.com/problems/maximum-length-of-a-concatenated-string-with-unique-characters/
/*
 * 	This is a backtracking (optional), string problem.
 *
 * 	Since input size is small, we could easily get away with backtracking (2^N) solution.
 * 	Every string, we could make an attempt to include it or not.
 *
 * 	- If we include it, then we mark the characters as existed, then proceed with the rest of strings (recurse)
 * 	- If we don't include it, we proceed to the other strings as usual.
 *
 * 	We will use a boolean array (Actually you can use bitmask) to mark whether characters already existed in the
 * 	string or not, so we will ignore those who have characters already in the string so far.
 *
 * 	Also, we'll directly ignore the strings that already have duplicate character in itself. Those strings will never
 * 	be considered even.
 */

class Solution {
public:
	int maxLength(vector<string>& arr) {
		vector<string> filtered(arr.size());
		vector<bool> occupied(26, false);
		copy_if(arr.begin(), arr.end(), filtered.begin(), [this](auto& x) { return isUnique(x); });
		return recurse(filtered, 0, 0, occupied);
	}

	// For each of the string, if it is unique characters and can fit inside string so far, we can try to include it.
	int recurse(vector<string>& arr, int from, int len, vector<bool>& occupied) {
		int res = len;

		for (int i = from; i < arr.size(); ++i) {
			// Check if string can fit
			auto& s = arr[i];
			if (!canFit(s, occupied)) continue;

			// String can fit. We will try include it and continue
			for (char c : s)
				occupied[c - 'a'] = true;
			// Recurse
			res = max(res, recurse(arr, i + 1, len + s.length(), occupied));
			// Backtrack
			for (char c : s)
				occupied[c - 'a'] = false;
		}

		return res;
	}

	// Checks if a string is made up of characters only once: no dupicates
	bool isUnique(string& s) {
		bool contain[26] = {};
		for (char c : s) {
			if (contain[c - 'a']) return false;
			contain[c - 'a'] = true;
		}
		return true;
	}

	// Given a occupied array and a string, checks if the string can fit inside without duplicate character
	bool canFit(string& s, vector<bool>& occupied) {
		for (char c : s)
			if (occupied[c - 'a']) return false;
		return true;
	}
};