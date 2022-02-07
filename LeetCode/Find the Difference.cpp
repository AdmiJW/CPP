#include <string>
using namespace std;


//https://leetcode.com/problems/find-the-difference/

/*
 * 	Given t is one character longer than s, and there is only 1 extra character in t compared to string s.
 *
 * 	Solution 1 is to count the characters. Once there is a difference in frequency of characters, we know it is that character
 * 	Instead of using 2 Hash Tables, use only 1 and Incrementing for string t, and decrementing for string t.
 * 	If the frequency value fall below 0 (Should be -1), then immediately we know that character is the extra in string t.
 *
 * 	------------------------------------------------------------
 *
 * 	Since each character can be represented in ASCII codes, when we find the difference in the sum of ASCII codes from both string,
 * 	it is absolutely clear that the resultant difference will be the ASCII code of the extra character in string t.
 * 	Add all ASCII codes in string t, and subtract all ASCII codes in string s. All character pair in s will cancel out those in t, except
 * 	for the extra character
 *
 * 	--------------------------------------------------------------
 *
 * 	Remember one unique property of XOR bitwise operation. If we XOR two same numbers, they will cancel out each other
 * 	Therefore we could just XOR EVERY SINGLE CHARACTER in both strings, and it will end up in the not cancelled extra character!
 */

class Solution {
public:

    // Counting solution
    char findTheDifference(string s, string t) {
        int count[26] = {};

        // Count characters in string s
        for (char c : s) ++count[c - 'a'];

        // Decrement characters from t. 
        for (char c : t) {
            --count[c - 'a'];
            if (count[c - 'a'] == -1) return c;
        }
        return 0;
    }


    // Summing solution
    char findTheDifference2(string s, string t) {
        int sum = 0;
        for (char c : t) sum += c;
        for (char c : s) sum -= c;
        return sum;
    }
};