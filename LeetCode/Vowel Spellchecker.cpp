#include <string>
#include <vector>
#include <unordered_map>
#include <cctype>
using namespace std;

//https://leetcode.com/problems/vowel-spellchecker/
/*
 * 	This is a HashMap and String problem, and can be solved without using more complex data structures like Trie
 * 	(Using Trie might end up having harder implementation, since there are 3 states for this one, although highly
 * 	workable)
 *
 * 	For each string, consider the following cases:
 * 		>	Perfect match
 * 		>	Ignore case match
 * 		>	Vowel wildcard match
 *
 * 	Therefore for each word in dictionary, at maximum we'll push 3 index into the HashMap.
 * 		>	One perfect match, one
 * 		>	Lowercased version of the string, but remember to mark it as lowercased version. Otherwise it might not work
 * 			in cases like
 * 				['KiTe', 'kite'] and queries ['kite', 'Kite'], where supposed output is ['kite', 'KiTe']
 *
 * 		>	Wildcard vowel version. Replace vowels to some character like * to mark wildcard.
 */


class Solution {
public:
	vector<string> spellchecker(vector<string>& wordlist, vector<string>& queries) {
		unordered_map<string, string> dicts;
		vector<string> res(queries.size());

		for (string s : wordlist) {
			//Perfect match
			dicts[s] = s;

			//Ignore case match
			string lowered = toLower(s);
			if (!dicts.count("_" + lowered))
				dicts["_" + lowered] = s;

			//Vowel wildcard match
			lowered = encode(lowered);
			if (!dicts.count(lowered))
				dicts[lowered] = s;
		}

		cout << dicts["k*t*"];


		for (int i = 0; i < res.size(); ++i) {
			if (dicts.count(queries[i]))
				res[i] = dicts[queries[i]];
			else if (dicts.count("_" + toLower(queries[i])))
				res[i] = dicts["_" + toLower(queries[i])];
			else if (dicts.count(encode(toLower(queries[i]))))
				res[i] = dicts[encode(toLower(queries[i]))];
			else
				res[i] = "";
		}
		return res;

	}

private:
	string toLower(string s) {
		for (int i = 0; i < s.length(); ++i)
			s[i] = tolower(s[i]);
		return s;
	}

	string encode(string s) {
		for (int i = 0; i < s.length(); ++i) {
			char c = s[i];
			if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u')
				s[i] = '*';
		}
		return s;
	}
};