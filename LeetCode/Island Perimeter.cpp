#include <vector>
using namespace std;

//https://leetcode.com/problems/island-perimeter/

/*
 * 	This question is solved by iterating through all the grids. If encountered a land, then find out the perimeter associated with this piece of land, where
 * 	each side facing a water will increase the perimeter by 1.
 *
 * 	To optimize, since we are iterating from top left corner to the right and eventually until bottom right, and realizing the fact that for a piece of land which
 * 	it has another neighboring island, then the perimeter is already effectively -2 since the neighboring island cannot include the perimeter where it is facing
 * 	with the current island now.
 * 	Therefore when we iterate, we only check the right and bottom islands, and count the number of islands as well as neighbors. After the iteration,
 * 	return islands * 4 (Each island maximum has 4 unit of perimeter, but unlikely if the land is connected) - neighbors * 2 (We count the neighbors of right and bottom only)
 *
 */

class Solution {
public:
    int islandPerimeter(vector<vector<int>>& grid) {
        const int r = grid.size();
        const int c = grid[0].size();
        int res = 0;

        for (int i = 0; i < r; ++i) {
            for (int j = 0; j < c; ++j) {
                if (!grid[i][j]) continue;

                if (i - 1 == -1 || grid[i - 1][j] == 0) ++res;
                if (j - 1 == -1 || grid[i][j - 1] == 0) ++res;
                if (i + 1 == r || grid[i + 1][j] == 0) ++res;
                if (j + 1 == c || grid[i][j + 1] == 0) ++res;
            }
        }
        return res;

    }
};