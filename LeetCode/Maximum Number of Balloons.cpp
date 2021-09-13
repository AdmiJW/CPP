#include <string>
using namespace std;

//https://leetcode.com/problems/maximum-number-of-balloons/
/*
 * 	This is a simply string / counting problem
 *
 * 	Count frequencies of characters, especially 'b' 'a' 'l' 'o' 'n'
 * 	The max number of balloons can be formed are:
 *
 * 	min(
 * 		freq(b),
 * 		freq(a),
 * 		freq(l) / 2,
 * 		freq(o) / 2,
 * 		freq(n)
 * 	)
 */


class Solution {
public:
    int maxNumberOfBalloons(string text) {
        int freq[26] = {};
        for (char c : text)
            ++freq[c - 'a'];
        int res = freq['b' - 'a'];
        res = min(res, freq['a' - 'a']);
        res = min(res, freq['l' - 'a'] / 2);
        res = min(res, freq['o' - 'a'] / 2);
        res = min(res, freq['n' - 'a']);
        return res;
    }
};