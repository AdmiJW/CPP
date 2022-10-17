#include <string>
using namespace std;

//https://leetcode.com/problems/check-if-the-sentence-is-pangram/
/*
 * A really easy String + Set/Map problem
 *
 * Simply record the 26 alphabet's existance in a set/map or equivalent data structure.
 * If the size is 26, exit early and return true
 */

class Solution {
public:
    bool checkIfPangram(string sentence) {
		bool exist[26] = {};
		int count = 0;

		for (char c : sentence) {
			if (!exist[c - 'a']) {
				++count;
				exist[c - 'a'] = true;

				if (count == 26) return true;
			}
		}

		return false;
    }
};
