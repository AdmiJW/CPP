#include <vector>
#include <string>
#include <algorithm>
using namespace std;

//https://leetcode.com/problems/longest-string-chain/
/*
 * 	This is a Dynamic Programming Problem / Topological sort
 *
 * 	To find chain of words, we could make use of certain properties to allow faster computation.
 *	First, a word is a predecessor of another if and only if another word is formed by adding one character
 *	to word. Checking for that is done in O(L) time where L is length of string
 *
 *	Say we fix a string s1 and we assume it is a predecessor. We would try to find for string s2 in words which s1 was
 *	predecessor of.
 *	Say we found s2. Problem is, we don't know if s2 can also be predecessor for s3, s4... etc.
 *
 *	Therefore, what we could do is, knowing the maximum length strings in words couldn't possibly be predecessor for any
 *	other string, their chain is fixed to length of 1 only if they are first element in chain!
 *	This intuition calls for DP approach.
 *
 *	First, sort strings by their lengths.
 *	All of the strings with maximum length can only form chain of length 1.
 *	Then, start iterating shorter strings, and find predecessor in longer lengthed string. If found, simply take the
 *	maximum length chain formed by the longer lengthed string + 1.
 *
 *
 *	------------------------------------
 *
 *	The approach is O(N^2 * L) - For each word, we iterate thru longer strings to find s2 such that this string is predecessor
 *	of it. Performing checking of predecessor is O(L).
 *
 *	But from the problem, L is fixed to 16 which is small. Therefore instead, we could try to use a HashMap where keys are
 *	strings, and values are maximum length of chain.
 *	For each string, try to insert a character at each possible position. Then, lookup in HashMap.
 *	This way, time complexity is O(N * L^2)
 */

class Solution {
public:
	int longestStrChain(vector<string> words) {
		const int len = words.size();
		sort(words.begin(), words.end(), [](const string& x, const string& y) -> bool {
			return x.size() < y.size();
		});
		vector<int> dp(len, 1);
		int res = 1;

		for (int i = len - 1; i >= 0; --i) {
			for (int j = i + 1; j < len; ++j) {
				if (isPredecessor(words[i], words[j]))
					dp[i] = max(dp[i], dp[j] + 1);
			}
			res = max(res, dp[i]);
		}
		return res;
	}



	bool isPredecessor(const string& pred, const string& str) {
		if (pred.size() != str.size() - 1) return false;

		bool isUsed = false;
		for (int l = 0, r = 0; l < pred.size(); ++l, ++r) {
			if (pred[l] != str[r]) {
				if (isUsed) return false;
				isUsed = true;
				--l;
			}
		}
		return true;
	}
};