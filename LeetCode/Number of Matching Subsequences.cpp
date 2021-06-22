#include <vector>
#include <string>
using namespace std;

//https://leetcode.com/problems/number-of-matching-subsequences/
/*
 * 	This is a Array String problem.
 *
 * 	One brute force we can think of is for every word in words[], keep two pointers that pointing to
 * 	index in s and word, and attempt to find subsequence for word by iterating through s.
 * 	This apporach takes O(N * S) time, and results in TLE in leetcode
 *
 * 	Instead, we can preprocess the string S to store the index sequences of characters beforehand.
 * 	Example: s = "abcaaa", then we store for character a, indices = {0, 3, 4, 5}
 *
 * 	Then, for each word, we simply keep our progress in the indices. For every character in word, we have to
 * 	look for the next character in indices, but be careful not to take smaller indices that we had already progressed!
 */

class Solution {
public:

	//	Brute Force solution in O(N * S) time. S = length of s, N = number of string in words[]
	int numMatchingSubseq(string s, vector<string>& words) {
		const int len = s.length();
		int res = 0;
		for (string& w : words) {
			int wIndex = 0;
			for (int sIndex = 0; sIndex < len && wIndex < w.length(); ++sIndex) 
				if (s[sIndex] == w[wIndex]) ++wIndex;

			res += (wIndex == w.length()) ? 1 : 0;
		}
		return res;
	}


	int numMatchingSubseq2(string s, vector<string>& words) {
		const int len = s.length();
		int res = 0;
		vector<vector<int>> indices(26);
		
		for (int i = 0; i < len; ++i)
			indices[s[i] - 'a'].push_back(i);

		for (string& w : words)
			res += isSub(indices, w);
		return res;
	}	
	bool isSub(vector<vector<int>>& indices, string& w) {
		int its[26] = {};
		int curr = -1;

		for (char c : w) {
			int code = c - 'a';
			//	While the index of the next current character is already progressed by previous character
			while (its[code] < indices[code].size() && indices[code][its[code]] <= curr)
				++its[code];

			if (its[code] >= indices[code].size()) return false;
			curr = indices[code][its[code]];
			++its[code];
		}
		return true;
	}
};