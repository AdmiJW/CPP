#include <string>
#include <vector>
using namespace std;

//https://leetcode.com/problems/find-and-replace-pattern/
/*
 * 	This is a String, HashMap problem
 *
 * 	For every string, one specific character from original string can only map to a character
 * 	in the pattern and vice versa. This means one to one relationship.
 *  To solve this, we build one by one:
 *
 * 	From index 0 to N-1, obtain character from both strings.
 * 	To initiate mapping from original to another, conditions:
 * 		>	original char must not yet map to any pattern char
 * 		>	pattern char must not yet map to any original char
 * 	The invalid pattern matching occurs when:
 * 		>	original char already maps to a pattern char but is not pattern char
 * 		>	pattern char already maps to a original char but is not original char
 *
 * 	Time is O(NK) where N is number of words, K is length of words
 * 	Space is O(K) if you don't consider the result array, otherwise O(NK)
 *
 * 	-----------------------
 *
 * 	We could try to reduce each string into a normalized pattern string. Eg:
 * 	"abbccdea" => "01122340"
 * 	Explaination: Each char is represented into an int value which is the order they are first encountered
 *
 *  First generate normalized pattern string of pattern. Then for each word, generate pattern string and check
 *  if equal or not
 */

class Solution {
public:
	//	Two maps solution. Must be in One to One Relationship
	vector<string> findAndReplacePattern(vector<string>& words, string pattern) {
		vector<string> res;
		for (string& s : words) {
			if (isMatchPattern(s, pattern))
				res.push_back(s);
		}
		return res;
	}
	bool isMatchPattern(string& ori, string& pat) {
		int oriToPat[27] = {};
		int patToOri[27] = {};
		for (int i = 0; i < ori.length(); ++i) {
			int o = ori[i] - 'a' + 1;
			int p = pat[i] - 'a' + 1;
			if (oriToPat[o] == 0 && patToOri[p] == 0) {
				oriToPat[o] = p;
				patToOri[p] = o;
			}
			else if (oriToPat[o] != p || patToOri[p] != o)
				return false;
		}
		return true;
	}



	//	Pattern matching solution
	vector<string> findAndReplacePattern2(vector<string>& words, string pattern) {
		string pat = toPattern(pattern);
		vector<string> res;
		for (string& s : words) {
			if (toPattern(s) == pat)
				res.push_back(s);
		}
		return res;
	}
	string toPattern(string& s) {
		int charToIdx[26] = {};
		int counter = 1;
		string res = "";

		for (char c : s) {
			//	If the character is never seen before, assign a new value, and increment the value
			if (!charToIdx[c - 'a'])
				charToIdx[c - 'a'] = counter++;
			res += charToIdx[c - 'a'];
		}
		return res;
	}
};