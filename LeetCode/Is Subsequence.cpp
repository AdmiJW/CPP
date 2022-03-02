#include <string>
using namespace std;


//https://leetcode.com/problems/is-subsequence/submissions/
/*
*   Simple string problem. Simply keep a pointer on s, and iterate through characters of t.
*   As soon as character of t matches character on pointer s, increment the pointer.
* 
*   If t contains subsequence of s, then surely the pointer on s will already be at the end of the string
*   after iteration.
*/


class Solution {
public:
    bool isSubsequence(string s, string t) {
        int pointer = 0;
        
        for (char c : t) {
            if (c == s[pointer]) ++pointer;
            if (pointer == s.size()) break;
        }
        return pointer == s.size();
    }
};