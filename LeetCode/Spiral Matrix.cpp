#include <vector>
using namespace std;


//https://leetcode.com/problems/spiral-matrix/
/*
 * This is a matrix simulation problem.
 *
 * Really, to solve this problem, all we need is to keep track of our boundaries, which constricts whenever
 * we completed a cycle.
 *
 * Initially, our boundaries are whole matrix. In each cycle, we have to
 * 	- Move left to right
 * 	- Move top to bottom
 *  - Move right to left
 *  - Move bottom to top (Don't visit again the initial element!)
 *
 * Once a cycle is completed, we constrict our boundary all inwards by size 1. Whenever the boundaries
 * are still valid, we know we still have cycles to do.
 * Be careful in edge cases where we're left with one row or column, as we might end up adding same element
 * twice. However that can be detected easily by checking the boundaries.
 *
 * In my solution, I only do boundary updating once a cycle is completed. However in official solution,
 * you would as well update the boundaries after you done one step (Traversed one row or column).
 */

class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        vector<int> res;
        // The boundary constricts after completing a cycle
        int leftBound = 0, rightBound = matrix[0].size() - 1;
        int topBound = 0, botBound = matrix.size() - 1;
        // Current position
        int r = 0, c = 0;

        // Repeat while there is still valid 'cycles' (AKA still got elements haven't traversed)
        while (leftBound <= rightBound && topBound <= botBound) {
            // Left to Right
            while (c <= rightBound) {
                res.push_back(matrix[r][c]);
                ++c;
            }
            --c;	// Adjust back
            ++r;	// Go to a row below.

            // Top to bottom
            while (r <= botBound) {
                res.push_back(matrix[r][c]);
                ++r;
            }
            --r;	// Adjust back
            --c;	// Go to one col to left

            // Right to left, only if there's 2 or more rows 
            if (topBound != botBound) {
                while (c >= leftBound) {
                    res.push_back(matrix[r][c]);
                    --c;
                }
                ++c;	// Adjust back
                --r;	// Go to one row up
            }

            // Bottom to top, only if there's 2 or more columns
            if (leftBound != rightBound) {
                while (r > topBound) {
                    res.push_back(matrix[r][c]);
                    --r;
                }
                ++r;	// Adjust back
                ++c;	// Go to next column
            }

            // Constrict the boundary
            ++leftBound; --rightBound;
            ++topBound; --botBound;
        }
        return res;
    }
};