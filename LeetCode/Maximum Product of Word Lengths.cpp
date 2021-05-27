#include <string>
#include <vector>
using namespace std;

//https://leetcode.com/problems/maximum-product-of-word-lengths/
/*
 * 	This is a bit manipulation problem, where we use 32 bits to represent
 * 	whether a string contains a character in it or not.
 *
 * 	For every string, convert into their 32 bit (integer) representation. Every bit
 * 	indicates the presence or absence of a character. Like 000..001 should represent
 * 	that 'a' is present. 000...010 indicates 'b' is present
 *
 * 	At the end, run a nested loop O(N^2), attempting all i and j pairs.
 * 	Since both strings cannot have intersection of characters, this property of bit must apply:
 *
 * 		bitStr[i] | bitStr[j]      ==	bitStr[i] + bitStr[j]
 *
 * 	If you know binary addition and bitwise OR operation, it is not hard to see why it works.
 */

class Solution {
public:

	int maxProduct(vector<string>& words) {
		const int len = words.size();
		vector<int> bitWords(len, 0);
		int res = 0;

		//	Convert each string into 32 int representing presence of characters
		for (int i = 0; i < len; ++i) {
			int repr = 0;
			for (char c : words[i])
				repr = (repr | (1 << (c - 'a')));
			bitWords[i] = repr;
		}

		//	Finding two strings that has no intersection of characters
		for (int i = 0; i < len; ++i) {
			for (int j = i + 1; j < len; ++j) {
				if (bitWords[i] + bitWords[j] == (bitWords[i] | bitWords[j]))
					res = max(res, (int)(words[i].length() * words[j].length()));
			}
		}
		return res;
	}
};