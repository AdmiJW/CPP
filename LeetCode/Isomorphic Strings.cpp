#include <string>
using namespace std;

//https://leetcode.com/problems/isomorphic-strings/
/*
 * This is a HashMap problem.
 *
 * Essentially, for each indices i, we will check to see if it is valid to convert all s[i] to t[i] without problem.
 * With this, we use a HashMap to record the mapping.
 *
 * We know it is not valid when:
 * 	>	s[i] is already mapped, and mapped character is not t[i]
 * 	>	s[i] is not mapped, but t[i] is already mapped by another character
 */

class Solution {
public:
	bool isIsomorphic(string s, string t) {
		const int len = s.length();
		char maps[128] = {};
		bool used[128] = {};

		for (int i = 0; i < len; ++i) {
			char sc = s[i], tc = t[i];

			if (maps[sc] != 0 && maps[sc] != tc || maps[sc] == 0 && used[tc])
				return false;
			maps[sc] = tc;
			used[tc] = true;
		}
		return true;
	}
};