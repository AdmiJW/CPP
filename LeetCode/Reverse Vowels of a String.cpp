#include <string>
#include <cctype>
using namespace std;

// https://leetcode.com/problems/reverse-vowels-of-a-string/
/*
 * Easy String problem
 *
 * You could do a two pass - One pass to record all the vowels, and second pass to replace the vowels reversely.
 * Or you could do two pointers: Left and right. Once the two pointers are both vowels, swap them.
 */


class Solution {
public:
    string reverseVowels(string s) {
		int l = 0, r = s.length() - 1;

		while (l < r) {
			if (!isVowel(s[l]) ) ++l;
			else if (!isVowel(s[r]) ) --r;
			else {
				char temp = s[l];
				s[l] = s[r];
				s[r] = temp;
				++l; --r;
			}
		}

        return s;
    }

    bool isVowel(char c) {
        c = tolower(c);
        return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
    }
};