#include <string>
#include <cctype>
using namespace std;

//https://leetcode.com/problems/determine-if-string-halves-are-alike/
/*
 * 	Easy string problem.
 *
 * 	Iterate the two halves of the string. Keep a counter to record the numbers of vowels met so far.
 * 	You can use 2 counters for this: 1 for first half, 1 for second half.
 *
 * 	At the end, if it is alike, 2 counters should equal.
 *
 * 	Since two counters should end with same amount, c1 - c2 = 0; Therefore, we can use 1 counter only,
 * 	and for first half vowel encounter, we increment the counter. For second half vowel encounter, we decrement
 * 	the counter. At the end, check if the counter are 0.
 */

class Solution {
public:
	bool halvesAreAlike(string s) {
		int cnt = 0;
		int half = s.length() / 2;

		for (int i = 0; i < half; ++i) {
			char c1 = tolower(s[i]);
			char c2 = tolower(s[half + i]);

			if (c1 == 'a' || c1 == 'e' || c1 == 'i' || c1 == 'o' || c1 == 'u') ++cnt;
			if (c2 == 'a' || c2 == 'e' || c2 == 'i' || c2 == 'o' || c2 == 'u') --cnt;
		}
		return !cnt;
	}
};