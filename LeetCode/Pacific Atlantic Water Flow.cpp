#include <vector>
#include <queue>
using namespace std;


//https://leetcode.com/problems/pacific-atlantic-water-flow/
/*
 * 	This is a graph BFS/ DFS problem. Each grid can be represented as node which connects to all 4 directions
 *
 * 	Instead of brute force, which we need to iterate over all cells, and check if all cells if it can be connected
 * 	to both oceans, we reverse the thinking:
 *
 * 		"What cells can be possibly be the origin for both oceans?"
 *
 * 	The answer is, the cell which has path to both atlantic and pacific ocean. Then, we further break the problem down:
 *
 *		"What cells has path to atlantic?" and "What cells has path to pacific?"
 *
 *	If we have individual answer to both problems, then we can combine the solution of both problem to solve general problem.
 *	That is, if a cell is both path to atlantic and path to pacific, then that cell is connected to both oceans!
 *
 *
 *	Start BFS/ DFS from any one ocean. Instead of as problem stated to go downwards, we only explore nodes which has higher
 *	height. Any node which is explored, is marked as possible path to the ocean. Record that in data structure.
 *
 *	At the end, compare both data structure to determine the position of cells which is connected to both oceans.
 */


class Solution {
public:
    vector<vector<int>> pacificAtlantic(vector<vector<int>>& matrix) {
        vector<vector<int>> res;
        if (!matrix.size()) return res;

        const int row = matrix.size(), col = matrix[0].size();
        const int dirs[4][2] = { {1,0}, {0,1}, {-1,0}, {0,-1} };
        vector<vector<bool>> intersect1(row, vector<bool>(col));
        vector<vector<bool>> intersect2(row, vector<bool>(col));

        queue< pair<int, int> > queue;

        //	First, explore from Pacific
        //	Initialize
        for (int i = 0; i < col; ++i) {
            queue.push(make_pair<>(0, i));
            intersect1[0][i] = true;
        }
        for (int i = 0; i < row; ++i) {
            queue.push(make_pair<>(i, 0));
            intersect1[i][0] = true;
        }

        //  Explore upstream to find the source
        while (!queue.empty()) {
            auto& pos = queue.front();

            for (auto& dir : dirs) {
                int r = pos.first + dir[0], c = pos.second + dir[1];
                if (r < 0 || r >= row || c < 0 || c >= col) continue;
                if (matrix[pos.first][pos.second] <= matrix[r][c] && !intersect1[r][c]) {
                    queue.push(make_pair<>(r, c));
                    intersect1[r][c] = true;
                }
            }
            queue.pop();
        }


        //	Then, explore from Atlantic
        //	Initialize
        for (int i = 0; i < col; ++i) {
            queue.push(make_pair<>(row - 1, i));
            intersect2[row - 1][i] = true;
        }
        for (int i = 0; i < row; ++i) {
            queue.push(make_pair<>(i, col - 1));
            intersect2[i][col - 1] = true;
        }

        //  Explore upstream to find the source
        while (!queue.empty()) {
            auto& pos = queue.front();

            for (auto& dir : dirs) {
                int r = pos.first + dir[0], c = pos.second + dir[1];
                if (r < 0 || r >= row || c < 0 || c >= col) continue;
                if (matrix[pos.first][pos.second] <= matrix[r][c] && !intersect2[r][c]) {
                    queue.push(make_pair<>(r, c));
                    intersect2[r][c] = true;
                }
            }
            queue.pop();
        }


        for (int r = 0; r < row; ++r) {
            for (int c = 0; c < col; ++c) {
                if (intersect1[r][c] && intersect2[r][c])
                    res.push_back({ r,c });
            }
        }


        return res;
    }
};