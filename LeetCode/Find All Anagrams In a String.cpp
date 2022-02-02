#include <string>
#include <vector>
using namespace std;


///https://leetcode.com/problems/find-all-anagrams-in-a-string/
/*
 * 	My first attempt was writing a helper method and keep the character count of anagram and string seperate, but this would mean everytime
 * 	i move the window, it has to run 26 iterations to check the character map one by one if it has difference (which means the substring is not anagram)
 *
 * 	Instead, a solution is to keep a difference count and only using one hashmap / bucket
 * 	The bucket works like this:
 * 		-Negative = There is an unwanted character in the window
 * 		-0 		  = Exactly correct amount of this character in the window
 * 		-Positive = The character is needed in the window
 *
 * 	-Eg : String: abcd, Anagram: abc
 * 	-Initially the map would be {b:1 c:1 d:1} and difference should be initialized to 3, the length of anagram (since window is still at size 0)
 * 	-Now we make the window, after that the map should be {a:-1 b:0 c:0 d:1} and difference is 2, 1 for the excess 'a' and 1 for absence of 'd'
 * 	-After the window moves to 'bcd', the map should become {a:0 b:0 c:0 d:0} and difference is 0. Whenever the difference is 0, that's the substring!
 */


class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        const int sl = s.length(), pl = p.length();
        vector<int> res;
        vector<int> window(26, 0);

        // Edge case
        if (sl < pl) return res;

        // Add string p into the requirements window
        for (char c : p)
            ++window[c - 'a'];

        // Window initialization
        for (int i = 0; i < pl; ++i)
            --window[s[i] - 'a'];
        if (isZero(window)) res.push_back(0);

        // General sliding window
        for (int i = pl; i < sl; ++i) {
            --window[s[i] - 'a'];
            ++window[s[i - pl] - 'a'];

            if (isZero(window)) res.push_back(i - pl + 1);
        }
        return res;
    }


    // Checks whether a vector is all 0.
    bool isZero(vector<int>& v) {
        for (int i : v) if (i) return false;
        return true;
    }
};