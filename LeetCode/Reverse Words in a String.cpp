#include <string>
#include <algorithm>
using namespace std;

//https://leetcode.com/problems/reverse-words-in-a-string/
/*
 * 	To reverse words in a string, The most easiest direct solution is to using split with white spaces as delimiter (using regex is better
 * 	since it matches multiple white spaces), then reverse the array and joining with seperated spaces.
 *
 *  The problem is still easier if we are allowed to utilize O(N) extra space. What we will do is to construct a new result string, and in the
 *  original string, we locate the boundaries of each word FROM BEHIND (Thus reversing), and appending it to the result string.
 *
 *  ---------------------------------------------------------------
 * 
 *  The hardest part is to do it in-place in languages like C++. To do it in place, first idea that you need to get is:
 *      >   Reverse the whole string, then reverse individual words to achieve what the problem originally want.
 *  Seems easy, but consider multiple spaces to be eliminated. Then it becomes quite more complicated
 *  Example:
 *      "      quick    brown fox jumps     over "
 * 
 *  >   Reverse whole string
 *  >   Keep an index: startIndex, indicating where we will insert our next word, in-place next. The reason for this is because of multiple spaces:
 *      "      a " -> startIndex = 0 means when we encouter the 'a', we will put at index 0.
 *  >   Iterate each character. Once encounter a character:
 *      - Shift it to startIndex.
 *      - Meanwhile, also locate the right boundary
 *  >   Then we essentially have the shifted word at range [startIndex, startIndex+wordLen]. Reverse it.
 * 
 *  >   At the end, discard leftover characters.
 */


class Solution {
public:

    // Mutable O(1) space solution
    string reverseWords(string s) {
        const int len = s.length();
        // Reverse whole string
        reverse(s.begin(), s.end());

        int head = 0;
        for (int l = 0; l < len; ++l) {
            if (s[l] == ' ') continue;

            // Append space if we have previous words
            if (head) s[head++] = ' ';

            // Locate the right boundary of the word, while also shifting it to eliminate unnecessary spaces
            int r = l;
            while (r < len && s[r] != ' ')
                s[head++] = s[r++];

            // Reverse the shifted word
            reverse(s.begin() + head - (r - l), s.begin() + head );

            // Assign l to r so that we proceed to next word
            l = r;
        }
        // After eliminating some spaces, we will eliminate what was leftover
        s.erase( s.begin() + head, s.end() );
        return s;
    }
};