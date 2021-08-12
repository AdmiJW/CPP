#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

//https://leetcode.com/problems/group-anagrams/
/*
 *	This is a Sorting, String, HashMap problem
 *
 * 	First of all, be informed that anagrams are made of same set and frequency of characters. That means, if the anagrams are
 *  sorted by character, they represent the same form:
 *
 *  		"bbcca", "cacbb"   ----Sorting---> "aabbc"
 *
 *  Thus, we can sort the anagrams in O(N) time, by bucket sort technique where we count frequency of 'a','b','c' and later assemble
 *  them back.
 *
 *	Then, use a HashMap to store group of anagrams
 */

class Solution {
public:
	vector<vector<string>> groupAnagrams(vector<string>& strs) {
		vector<vector<string>> res;
		unordered_map<string, vector<string>> map;

		for (string& s : strs) {
			string key = sortString(s);
			map[key].push_back(s);
		}

		for (auto& p : map)
			res.push_back(p.second);

		return res;
	}

	string sortString(string& s) {
		int freq[26] = {};
		string res = "";

		//Count frequency of alphabets
		for (char c : s)
			++freq[c - 'a'];

		for (int i = 0; i < 26; ++i)
			while (freq[i]-- > 0)
				res += (char)(i + 'a');
		return res;
	}
};

