#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

// https://leetcode.com/problems/longest-palindrome-by-concatenating-two-letter-words/
/*
 * This is a Greedy, HashMap counting problem.
 *
 * First of all, count the number of occurrences of words into a frequency table/Hashmap.
 *
 * We will handle 2 cases: words that are symmetric like 'aa', and those who are unsymmetric 'ab'
 *
 * -----
 *
 * For unsymmetric its simple: If we want to use one occurrence of 'ab', we must append 'ba' at the other end.
 * Therefore for each of possible word w, we can make our result string longer by:
 *
 * 		min(
 * 			frequency( w ),
 * 			frequency( reverse(w) )
 * 		) * 4
 *
 * -----
 *
 * For symmetric ones, it can be ambiguous in 2 ways:
 * 		> If we have 2 'aa', we can treat them like in unsymmetric case: append one at the front and one at the back no problem.
 * 		> if we have lone 'aa', we can append it right at the center of the string, only ONCE
 *
 * Therefore, for each of the symmetric word w, we add to the result string:
 *
 * 		closestLowerEvenNumber(
 * 			frequency( w )
 * 		) +
 * 		( 2 if the center is not occupied yet and if frequency(w) is odd )
 */

class Solution {
public:

	int longestPalindrome(vector<string>& words) {
		unordered_map<string, int> symmetric, unsymmetric;
		int res = 0;

		for (string& s : words) {
			if (s[0] == s[1]) ++symmetric[s];
			else ++unsymmetric[s];
		}

		// Process symmetric first
		bool usedMiddle = false;

		for (auto& e : symmetric) {
			int isOdd = e.second % 2;

			res += (e.second - isOdd) * 2;

			if (!usedMiddle && isOdd) {
				res += 2;
				usedMiddle = true;
			}
		}


		// Now process unsymmetric
		for (auto& e : unsymmetric) {
			string reverse = reverse2(e.first);

			if (unsymmetric.count(reverse) ) {
				res += min( unsymmetric[e.first], unsymmetric[reverse] ) * 4;
				unsymmetric[e.first] = 0;
				unsymmetric[reverse] = 0;
			}
		}

		return res;
	}


	string reverse2(const string& s) {
		string res = "";
		res += s[1];
		res += s[0];
		return res;
	}
};