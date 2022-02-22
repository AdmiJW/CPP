#include <string>
using namespace std;

//https://leetcode.com/problems/excel-sheet-column-number/
/*
 * 	In Excel, column numbers are just a Base 26 numbering system and each character is from A to Z
 * 	Therefore using base number formula, we can simply obtain the answer
 */



class Solution {
public:

    int titleToNumber(string columnTitle) {
        const int len = columnTitle.size();
        int res = 0;
        long long int base = 1;     // 26^0 initially.
    
        // Read "digits" from backwards
        for (int i = len - 1; i >= 0; --i, base *= 26)
            res += base * (columnTitle[i] - 'A' + 1);

        return res;
    }
}