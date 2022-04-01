#include <vector>
#include <algorithm>
using namespace std;

//https://leetcode.com/problems/reverse-string/
/*
* Simple reversing array problem.
* Using two pointers from both ends, swap the characters.
*/

class Solution {
public:
    void reverseString(vector<char>& s) {
        const int len = s.size();
        int l = 0, r = len - 1;

        while (l < r) {
            swap( s[l], s[r] );
            ++l; --r;
        }
    }
};