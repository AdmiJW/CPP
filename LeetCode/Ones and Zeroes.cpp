#include <string>
#include <vector>
using namespace std;

//https://leetcode.com/problems/ones-and-zeroes/
/*
 * 	This is a 01 knapsack dynamic programming problem, with a little modification in it.
 *
 * 	01 Knapsack problem is, given a list of items and a limitation on the items that you can choose, use dynamic programming
 * 	through memoization or tabulation to determine the maximum profit / score you can pick the items in.
 *
 * 	In tabulation method, the row represent the range of items you are considering. Row 0 means you are not considering anything
 * 	in the items list. Row 1 means you consider the first item. Row 2 means you consider first item along with second item...
 *
 * 	Column on the other hand, represents the limitation. Say our limitation is bag size, then column 0 means bag size of 0,
 * 	column 1 means size of 1 and so on... until reaching the limitation stated in the problem.
 *
 * 	Every step, you have the choice to either include the item or not, which is determined by:
 * 	>	Picking the item, since it will occupy some limitations, therefore visit same row in DP, but with limitations subtracted
 * 		with the item's limitation.	(Same row, column - item's limitation)
 * 	>	Not picking the item, which is same as last row's same limitation. Thus (last row, same column)
 *
 * 	At the rightmost bottom border of the table is the original problem statement:
 * 		Consider all items and limitations limit, the best result that can be obtained.
 *
 * 	In this problem, we have to use 3D array or encode the zeroes and ones (m and n) into one array and have 2D array. Either
 * 	way, perform knapsack algorithm on it and you'll get the result.
 *
 * 	-------------------------
 *
 * 	Since the DP depends on only the last row same column, you can reduce space complexity to be O(MN) only with one array
 * 	Note that in this form, we have to reverse iteration (except the outermost loop) because we won't want to include the
 * 	same bitstring twice once included!
 *
 * 	Or to prevent above case, use 2 separate arrays prev and curr.
 */


class Solution {
public:
    int findMaxForm(vector<string>& strs, int m, int n) {
        const int rows = strs.size();
        const int zerodim = m + 1;      //	Included 0. That's why m+1 and n+1
        const int onedim = n + 1;

        vector< vector< vector<int> > >dp(rows + 1, vector<vector<int>>(zerodim, vector<int>(onedim, 0)));
        
        for (int x = 1; x <= rows; ++x) {
            int zero = 0, one = 0;
            for (char c : strs[x - 1]) {
                if (c == '0') ++zero;
                else ++one;
            }

            //  Zero - m
            for (int y = 0; y < zerodim; ++y) {
                //  Ones - n
                for (int z = 0; z < onedim; ++z) {
                    //	We can include current string here
                    if (y - zero >= 0 && z - one >= 0)
                        dp[x][y][z] = dp[x - 1][y - zero][z - one] + 1;
                    //	Either case, take the same zeroes and ones, but last row without including current bitstr
                    dp[x][y][z] = max(dp[x][y][z], dp[x - 1][y][z]);
                }
            }
        }
        return dp[rows][m][n];
    }


    //	Since we only need last row's result, reduce space complexity from ( len(strs) * m * n) to 2( m*n) only
    int findMaxForm(vector<string>& strs, int m, int n) {
        const int rows = strs.size();
        const int zerodim = m + 1;      //	Included 0. That's why m+1 and n+1
        const int onedim = n + 1;

        vector<vector<int>>dp(zerodim, vector<int>(onedim, 0));

        for (int x = 1; x <= rows; ++x) {
            int zero = 0, one = 0;
            for (char c : strs[x - 1]) {
                if (c == '0') ++zero;
                else ++one;
            }

            //  Zero - m
            for (int y = zerodim - 1; y >= 0; --y) {
                //  Ones - n
                for (int z = onedim - 1; z >= 0; --z) {
                    //	We can include current string here
                    if (y - zero >= 0 && z - one >= 0)
                        dp[y][z] = max(dp[y][z], dp[y - zero][z - one]);
                }
            }
        }
        return dp[m][n];
    }
};