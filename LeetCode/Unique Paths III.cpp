#include <vector>
using namespace std;

//https://leetcode.com/problems/unique-paths-iii/
/*
* 	This is a backtracking, DFS problem
*
* 	First, we have to obtain extra information from the grid itself. We need to know:
* 	>	How many non-obstacle grids are there, so we know when we have explored all non-obstacle grids
* 	>	The starting grid position, to know where to start the DFS backtracking
*
* 	Then, for each grid in the recursion (or do it iteratively), we first need to define the base case:
* 		>	If it is the ending grid, add 1 to the result (Meaning one path discovered) only if all the non-obstacle grids are
* 			explored (Represented as a counter which decrements)
* 	Otherwise, mark the grid as explored (Changing the value in place), then explore all 4 directions, but based on some constraints
* 	>	Not explored grid
* 	>	Not out of bounds
* 	>	Not obstacle
*
* 	After doing the exploration on 4 direction and obtained their results, revert the change to the grid itself. and return the value
*/


class Solution {
public:
    int solution = 0;

    int uniquePathsIII(vector<vector<int>>& grid) {
        // Step 1 - Identify numbers of grid required to explore, and also locate starting grid
        int toExplore = 0;
        int startR, startC;
        for (int i = 0; i < grid.size(); ++i) {
            for (int j = 0; j < grid[0].size(); ++j) {
                // Add 1 to toExplore if element is 0
                toExplore += grid[i][j] == 0;
                // Located start position. Mark it
                if (grid[i][j] == 1)
                    startR = i, startC = j;
            }
        }


        // Step 2 - Recurse and backtrack
        recurse(grid, startR, startC, toExplore + 1);

        return solution;
    }

    void recurse(vector<vector<int>>& grid, int r, int c, int toExplore) {
        // Out of bounds
        if (r == -1 || r == grid.size() || c == -1 || c == grid[0].size()) return;

        // Base case - Reached finish line
        if (!toExplore || grid[r][c] != 0 && grid[r][c] != 1) {
            solution += (grid[r][c] == 2 && !toExplore);
            return;
        }

        // Backtracking algorithm
        //      1 - Mark current grid as visited
        grid[r][c] = INT32_MAX;
        //      2 - 4 Directions
        recurse(grid, r - 1, c, toExplore - 1);
        recurse(grid, r + 1, c, toExplore - 1);
        recurse(grid, r, c - 1, toExplore - 1);
        recurse(grid, r, c + 1, toExplore - 1);
        //      3 - Undo changes
        grid[r][c] = 0;
    }
};