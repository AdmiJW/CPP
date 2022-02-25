#include <string>
using namespace std;


//https://leetcode.com/problems/compare-version-numbers/
/*
 * 	The base idea is to split the numbers on the delimiter dot '.'
 * 	Then iterate the number until the end of one of the shorter version numbers.
 *
 * 	If in the midst of the iteration one of the version number is larger, then return -1 or 1 immediately.
 *
 * 	After the iteration, if one of the version number is actually longer, then continue the other one. If it is found a non-zero
 * 	number, then it is larger version. Return -1 or 1 immediately.
 *
 * 	If after iteration of all the numbers still is equal, return 0
 *
 *
 * 	Note on the split method. Since it takes in a regex string, the dot . is actually a wildcard. We need to pass in
 * 	the escape character "\.", but the escape character by itself need to be escaped as well. Therefore "\\."
 *
 */


class Solution {
public:
    int compareVersion(string version1, string version2) {
        const int l1 = version1.length(), l2 = version2.length();
        int p1 = 0, p2 = 0;

        while (p1 < l1 || p2 < l2) {
            int v1 = 0, v2 = 0;

            // Read version1's revision number
            if (p1 < l1) {
                while (version1[p1] >= '0' && version1[p1] <= '9')
                    v1 = v1 * 10 + version1[p1++] - '0';
                
                if (p1 < l1 && version1[p1] == '.') ++p1;
            }

            // Read version2's revision number
            if (p2 < l2) {
                while (version2[p2] >= '0' && version2[p2] <= '9')
                    v2 = v2 * 10 + version2[p2++] - '0';

                if (p2 < l2 && version2[p2] == '.') ++p2;
            }

            // Compare
            if (v1 > v2) return 1;
            else if (v1 < v2) return -1;
        }

        return 0;
    }
};