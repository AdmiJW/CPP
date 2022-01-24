#include <string>
#include <cctype>
using namespace std;


//https://leetcode.com/problems/detect-capital/
/*
*   Simple string problem. Count number of lowercases (or uppercases).
*   
*   If all lowercase (lowercaseCount = len) or all uppercase (lowercaseCount = 0) or first upper, rest lower
*   (lowercaseCount = len - 1 && word[0] is upper), then return true.
*/


class Solution {
public:
    bool detectCapitalUse(string word) {
        const int len = word.length();
        int countLower = 0;

        for (char c : word) countLower += islower(c)? 1: 0;

        return (
            (countLower == 0) ||
            (countLower == len) ||
            (countLower == len - 1 && isupper(word[0]))
        );
    }
};