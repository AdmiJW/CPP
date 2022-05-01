#include <string>
using namespace std;

//https://leetcode.com/problems/backspace-string-compare/
/*
*   This is a two pointers / Stack problem.
* 
*   The easiest approach using O(N) space is by stack, simply simulate the process on two strings and check at the end
*   whether the two strings are equal or not.
* 
*   -------------------------------------
* 
*   If the string is mutable and if we are allowed to mutate the input string, we can utilize the input string as our "extra space"
*   using two pointers and still get the resulting string at the end.
* 
*   To mutate a string, initialize two pointers, 1 fast 1 slow. The slow pointer indicates the current position of the cursor, and
*   the fast pointer simply iterate over all characters of the original string.
* 
*   If the fast pointer meets a '#' (backspace), the slow pointer has to reverse by 1 step.
*   Otherwise, the slow pointer will put the character into the index, and proceed by 1 step.
* 
*   At the end, the substring up until slow pointer is the resulting string. Compare both, and you get the answer
* 
*   ---------------------------------------
* 
*   By iterating in reverse, we can solve the problem.
* 
*   The key idea is, by iterating in reverse, once we meet a '#' (backspace), we will have to skip the next non backspace
*   character. However, remember to account for consecutive backspaces by using a counter!
* 
*   (Not implemented in this CPP)
*/


class Solution {
public:

    // Simulation solution with stack - O(N) time & space
    bool backspaceCompare(string s, string t) {
        // Simulate string s
        string resultS = "";
        for (char c : s) {
            if (c == '#' && !resultS.empty() ) resultS.pop_back();
            else if (c != '#') resultS.push_back(c);
        }
        
        // Simulate string t
        string resultT = "";
        for (char c : t) {
            if (c == '#' && !resultT.empty()) resultT.pop_back();
            else if (c != '#') resultT.push_back(c);
        }

        return resultS == resultT;
    }



    // Modify in place solution
    bool backspaceCompare2(string s, string t) {
        int l1 = simulate(s);
        int l2 = simulate(t);

        if (l1 != l2) return false;

        for (int i = 0; i < l1; ++i)
            if (s[i] != t[i]) return false;
        return true;
    }


    // The function modify the string in-place, and returns the final length of the string.
    // Implemented using two pointers
    int simulate(string& s) {
        int pt = 0;
        
        for (char c : s) {
            if (c == '#' && pt != 0) --pt;
            else if (c != '#') s[pt++] = c;
        }

        return pt;
    }

};