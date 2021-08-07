#include <vector>
#include <string>
using namespace std;

//https://leetcode.com/problems/palindrome-partitioning-ii/
/*
 * 	This is a Dynamic Programming problem.
 *
 * 	The initial idea is that, if we detect a palindrome is formable from the start of the string or end of the string,
 * 	if we already have the answer to the minCut solution to the substring that comes after or before it (which is DP),
 * 	then we can solve it in O(N^2) time.
 *
 * 	Note:
 * 		(1)	A single character (string length 1) is a palindrome
 * 		(2)	If a string is a palindrome, if we remove the first and last character, it is a palindrome.
 * 			Similarly, if we have a palindrome, we can check if it can be extended by checking if the neighboring
 * 			characters are same.
 *			Eg: 'racecar', by removing 'r', 'aceca' is still palindrome, like 'cec', 'e'
 *
 * 	For exmaple, see the following case:
 *
 * 		>	'racecarbbba'
 * 		We may detect that 'racecar' is a palindrome. If we can know the minCuts required for the remaining 'bbba',
 * 		then we can know if we perform the cut right after 'racecar', what is the minimum cut required for whole string!
 *
 *  One way is that we preprocess the string to construct a DP array isPalindrome[][], where isPalindrome[i][j] shows
 *  whether the substring from i to j is a palindrome or not.
 *  Then, setup a dp[] array which shows the minimum cut required to fully partition the string up until string [i].
 *  For this, we have to use two pointers representing the left and right boundary we are considering:
 *  	'aaaracecar'
 * 			^     ^
 * 	Say we are fixing the two pointers above and know that 'racecar' is palindrome (through (2)),
 *  then the minimum cut is of course, dp[leftPointer - 1] + 1.
 *
 * 	=============================================================================
 *
 * 	Turns out we dont even need to preprocess the string. In above solution, we always check the isPalindrome at indices
 * 	up until rightPointer-1, which is already computed previously. We can fill dp[] and isPalindrome[] at same time.
 * 	See solution below for the code.
 *
 * 	=============================================================================
 *
 * 	Again, in each iteration, we always check isPalindrome[leftPt+1][rightPt-1], and the rightPt never changes does it?
 * 	Therefore, we can reduce the DP array to space complexity of O(N)!
 */

class Solution {
public:
	int minCut(string s) {
		int len = s.length();
		vector<vector<bool>> isPalindrome(len, vector<bool>(len, 0));
		// dp[i] represents the minimum cut to partition palindrome, where
		// the substring ends at index i
		vector<int> dp(len, 0);

		// Right Boundaries
        for (int right = 0; right < len; ++right) {
            int minCuts = INT32_MAX;

            // Left boundaries
            for (int left = 0; left <= right; ++left) {

                // Is a palindrome if first and last char is same, and middle substring is
                // also a palindrome (or there is no middle substring)
                if (s[left] == s[right] && (left + 1 > right - 1 || isPalindrome[left + 1][right - 1])) {
                    isPalindrome[left][right] = true;
                    minCuts = (left == 0) ? 0 : min(minCuts, dp[left - 1] + 1);
                }
            }
            dp[right] = minCuts;
        }
        return dp[len - 1];
	}
};