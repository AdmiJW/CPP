#include <string>
#include <vector>
using namespace std;

// https://leetcode.com/problems/delete-columns-to-make-sorted/
/*
 * Easy problem with strings.
 *
 * Run 2 loops. Outer loop determines the index of character (column) we will be checking.
 * The inner loop runs through the strings and checks if the character at the index is greater than the next string's character.
 *
 * Because if the characters up to n-1 is already sorted, we only need to check if the current character is greater than the
 * next string's character to invalidate the sorted property
 */

class Solution {
public:
    int minDeletionSize(vector<string>& strs) {
        const int m = strs.size();
        const int n = strs[0].length();

        int res = 0;

        // ith character of strings
        for (int i = 0; i < n; ++i) {

            for (int j = 0; j < m - 1; ++j) {
                if (strs[j][i] > strs[j+1][i]) {
                    ++res;
                    break;
                }
            }
        }

        return res;
    }
};