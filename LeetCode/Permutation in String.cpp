#include <string>
#include <vector>
using namespace std;

//https://leetcode.com/problems/permutation-in-string/
/*
 * 	Key to realise: For a permutation of s1 to be exist in part of s2, it must has the same frequency of characters in that substring of s2
 * 					Therefore it is a combination of hash map and sliding window problem
 * 					Additionally, we keep a counter of difference to see the difference between the hash map and substring checked, that way
 * 					we don't have to keep checking the hashmap over and over
 */


class Solution {
public:
    bool checkInclusion(string s1, string s2) {
        if (s1.length() > s2.length()) return false;

        vector<int> count(26, 0);
        for (char c : s1) ++count[c - 'a'];

        // Intiialize sliding window
        for (int i = 0; i < s1.length(); ++i) --count[s2[i] - 'a'];
        if (isAllZero(count)) return true;

        // General sliding window
        for (int i = s1.length(); i < s2.length(); ++i) {
            --count[s2[i]];
            ++count[s2[i - s1.length()]];
            if (isAllZero(count)) return true;
        }


        return false;
    }


    bool isAllZero(vector<int>& v) {
        for (int i : v) if (i) return false;
        return true;
    }
};