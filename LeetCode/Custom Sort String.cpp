#include <string>
using namespace std;

//https://leetcode.com/problems/custom-sort-string/
/*
 *  This is a string sorting problem, kind of?
 *
 *  First thing to observe is that the type of values we have to sort is very small, only 26 possible values. In those
 *  cases, the algorithm we can use is Counting Sort, which counts the frequencies of occurrences, then sort.
 *
 *  Therefore, obtain the frequency table of characters from str. Then, from the order string, we refer to the frequency
 *  table and append however many we needed to the result string.
 *
 *  After the order string is done iteration, we can append the remaining characters that are not inside order string. Those
 *  not yet appended character shall still have non-zero frequency in the frequency table.
 */

class Solution {
public:
	// Counting sort Inspired Solution
	string customSortString(string order, string str) {
		const int len = str.size();
		int count[26] = {};
		string res = "";
		res.reserve(len);

		for (char c : str)
			++count[c - 'a'];

		for (char o : order)
			while (--count[o - 'a'] >= 0)
				res += o;

		// For those character not inside order str, we append it last
		for (char c = 'a'; c <= 'z'; ++c)
			while (--count[c - 'a'] >= 0)
				res += c;

		return res;
	}
};