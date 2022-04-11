#include <vector>
using namespace std;

//https://leetcode.com/problems/shift-2d-grid/
/*
* This is a matrix problem.
* 
* Although it is a 2D matrix which consist of 2 indices i and j, we can easily "flatten" the indices:
* Given a matrix of IxJ, we can flatten it as an linear array of size IxJ, and we can easily convert from the linear index to
* row and column index:
* 
* To 2D indices:
*       i = index / col
*       c = index % col
* To linear index
*       index = i * col + c
* 
* --------------------------------
* 
* To solve this problem, we can either use extra space by creating a brand new matrix and returning it, or we can do it inplace.
* To solve this problem in-place by modifying the input matrix, you may refer to problem "Rotate Array" also on Leetcode, and
* available in the same repository.
* 
*/


class Solution {
public:
    vector<vector<int>> shiftGrid(vector<vector<int>>& grid, int k) {
        const int row = grid.size(), col = grid[0].size();
        const int n = row * col;
        int count = 0;
        int prev = 0;

        // Avoid overshifting
        k = k % n;

        for (int i = 0; count != n; ++i) {
            int curr = i;

            // Calculate the element index to be shifted first
            int index = (n + i - k) % n;
            prev = grid[index / col][index % col];

            do {
                // cout << curr;
                int r = curr / col, c = curr % col;
                int temp = grid[r][c];
                grid[r][c] = prev;
                prev = temp;

                curr = (curr + k) % n;
                ++count;
            } while (curr != i);
        }

        return grid;
    }
};