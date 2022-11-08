#include <string>
using namespace std;

// https://leetcode.com/problems/make-the-string-great/
/*
 * A Stack String problem.
 * 
 * For each character, look at the top of the stack.
 *  > If stack empty, simply push
 *  > If stack peek is not the opposite of current character, simply push
 *  > Otherwise pop.
 */



class Solution {
public:
    string makeGood(string s) {
        string res = "";

        for (char c: s) {
            if (res.length() == 0 || res[res.length() - 1] != opposite(c) ) {
                res += c;
            } else {
                res.pop_back();
            }
        }

        return res;
    }

    char opposite(char c) {
        if (c >= 'a' && c <= 'z') return (char) (c - 'a' + 'A');
        return (char) (c - 'A' + 'a');
    }
}