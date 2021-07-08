#include <vector>
using namespace std;

//https://leetcode.com/problems/maximum-length-of-repeated-subarray/
/*
 * This is a Dynamic Programming problem / RabinKarp String Matching Algorithm (Rolling Hash) problem
 *
 * For DP approach, think: the DP rows represent the range of the nums1 array that we include, and
 * columns represent the range of nums2 array that we include.
 *
 * For example, i=3 and j=5 will answer the question "What is the longest subarray that can be formed
 * from nums1 until 4th element and MUST END WITH 4th element (0-indexing), if we only consider nums2 array
 * range until 6th element?"
 *
 * When DP iterates until index i, j, we check whether nums1[i] == nums2[i]. If it matches, that leaves
 * us one question of whether the current match can extend the previous match or not? This is done by
 * simply checking the DP array when the indices are i-1 and j-1.
 * Otherwise if no match, then simply put dp[i][j] = 0
 *
 * Due to this behavior, the answer may not be contained in dp[len1][len2]. Thus, we need to have a variable
 * that updates when a match is found.
 *
 * Note that unlike Longest Subsequence problem, this problem only checks the previous diagonal element. This
 * very well opens a possibility to optimize our DP array to be 1D, taking O(N) size only
 *
 * ========================================================================
 *
 * One more advanced solution is to use binary search to find out the length of maximum length subarray, and using
 * rolling hash algorithm to find matches in the subarray.
 *
 * For the binary search part is self explainatory, taking O(log (min(M,N)) time. When a value is estimated, we need to
 * verify it.
 * First, perform rolling hash on nums1 array, storing each possible hashes in a O(1) lookup data structure like Set, then
 * perform rolling hash on nums2 array. A match is found if hashes are correct.
 * For more secure, we could use naive check when the hashes match.
 *
 */

class Solution {
public:
    // 2D Dynamic Programming soln
    int findLength(vector<int>& nums1, vector<int>& nums2) {
        const int l1 = nums1.size(), l2 = nums2.size();
        vector<vector<int>> dp(l1+1, vector<int>(l2+1, 0));
        int res = 0;

        for (int i = 0; i < l1; ++i) {
            for (int j = 0; j < l2; ++j) {
                if (nums1[i] == nums2[j]) {
                    dp[i + 1][j + 1] = dp[i][j] + 1;
                    res = max(res, dp[i + 1][j + 1]);
                }
            }
        }
        return res;
    }


    //	1D optimized DP soln
    int findLength2(vector<int>& nums1, vector<int>& nums2) {
        const int l1 = nums1.size(), l2 = nums2.size();
        vector<int> dp(l2+1, 0);
        int res = 0;

        for (int i = 0; i < l1; ++i) {
            for (int j = l2 - 1; j >= 0; --j) {
                if (nums1[i] == nums2[j]) {
                    dp[j + 1] = dp[j] + 1;
                    res = max(res, dp[j + 1]);
                }
                else
                    dp[j + 1] = 0;
            }
        }
        return res;
    }
};