#include <string>
#include <vector>
using namespace std;

//https://leetcode.com/problems/slowest-key/
/*
 * Simple array problem.
 *
 * For each char, compute the duration for this key. Compare with the global maximum duration
 * if current duration is longer or not.
 * In case duration is same, compare the characters.
 */

class Solution {
public:
    char slowestKey(vector<int>& releaseTimes, string keysPressed) {
        char res = 'a';
        int prev = 0;
        int maxdur = 0;

        for (int i = 0; i < releaseTimes.size(); ++i) {
            int duration = releaseTimes[i] - prev;
            char c = keysPressed[i];

            if (duration > maxdur) {
                maxdur = duration;
                res = c;
            }
            else if (duration == maxdur)
                res = c > res ? c : res;
            prev = releaseTimes[i];
        }
        return res;
    }
};