#include <vector>
using namespace std;

//https://leetcode.com/problems/dungeon-game/

/*
 * 	A Dynamic Programming question which is easier to spot and realize. The question asks for the minimum health required to reach princess grid.
 * 	Therefore we could see the optimization (min) and can divide into subproblems (What is the min health required to reach princess from this
 * 	grid?)
 *
 * 	** Second time doing this problem thoughts: Well I couldn't come up with solution the second time, because I tried DP from top left corner.
 * 		This gives a lesson: If I were to brute force, i begin with top left. DP is a bottom up problem, means we should probably start from the
 * 		destination.
 * 		Some DP problem are better off start from destination than starting from source.
 *
 * 	We would create a new 2D array of same size where each cell represents the min health required to reach princess from this cell. (Actually,
 * 	we could overwrite the original dungeon array as well, which further reduces the space complexity to O(1) )
 *
 * 	The initialization would be to determine the min health to reach princess FROM PRINCESS GRID ITSELF, which depends:
 * 		-If it is damaging room, then it would be abs(damage) + 1 (So that the knight still have 1HP left and not die)
 * 		-If it is healing room, then it would be 1 (Of course, hero dies at HP 0)
 *
 * 	Then we would simply just loop thru the array from bottom up. Each cell we would determine by the following equation:
 * 		Take the minimum value between minHealthGrid(right, bottom) --- To take the path which requires lowest health possible
 * 		and subtract the current dungeon value 						--- So that if it is damaging (negative), we would add to the required health
 * 																	--- of next step, and if it is healing, we would lessen the required health
 *
 * 	Last note is that, if the calculated min health value is below or equal 0 (Occurs when the room heals big) we simply put required health as 1
 *
 * 	Therefore we will return the original question:
 * 		The minimum health required to reach princess from origin (0,0)
 *
 */


class Solution {
public:

    int calculateMinimumHP(vector<vector<int>>& dungeon) {
        const int r = dungeon.size();
        const int c = dungeon[0].size();
        vector<vector<int>> dp(r, vector<int>(c, INT32_MAX));

        // Initilization at princess room
        dp[r - 1][c - 1] = max(1, 1 - dungeon[r - 1][c - 1]);

        // From bottom right, dp until reach topleft
        for (int i = r - 1; i >= 0; --i) {
            for (int j = c - 1; j >= 0; --j) {
                // From bottom
                if (i != r - 1)
                    dp[i][j] = max(1, dp[i + 1][j] - dungeon[i][j]);
                // From right
                if (j != c - 1)
                    dp[i][j] = min(dp[i][j], max(1, dp[i][j + 1] - dungeon[i][j]));
            }
        }
        return dp[0][0];
    }

};