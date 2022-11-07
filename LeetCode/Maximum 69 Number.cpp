#include <string>
using namespace std;


// https://leetcode.com/problems/maximum-69-number
/*
 * Ezpz and nice problem. Just change the first occurence of 6 to 9, and not do anything if there's no 6
 */


class Solution {
public:
    int maximum69Number (int num) {
        string s = to_string(num);

        for (int i = 0; i < s.size(); ++i) {
            if (s[i] == '6') {
                s[i] = '9';
                return stoi(s);
            }
        }

        return num;
    }
};