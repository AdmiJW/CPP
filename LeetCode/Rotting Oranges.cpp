#include <vector>
#include <queue>
using namespace std;

//https://leetcode.com/problems/rotting-oranges/
/*
 * 	This is a BFS problem. Since it involves turn-taking, and finding out how many turns to rot the whole orange, each turn
 * 	is considered one 'round' of BFS
 *
 * 	First do a initial scan to know the amount of oranges and amount of rotten ones. Add the rotten one's position into queue.
 * 	Then on round 1, we will start to rot the oranges adjacent to it. Note that we will also change the so-mentioned fresh orange
 * 	to rotten so we won't end up in a loop. Those rotten oranges need to be added to the queue to spread the rot-ness in the next
 * 	round of BFS
 */




class Solution {
public:
    int orangesRotting(vector<vector<int>>& grid) {
        const int r = grid.size();
        const int c = grid[0].size();

        int rounds = 0;
        int fresh = 0;
        queue<pair<int, int>> rotten;

        // Initial scan -> get fresh oranges and rotten ones
        for (int i = 0; i < r; ++i) {
            for (int j = 0; j < c; ++j) {
                if (grid[i][j] == 1) ++fresh;
                else if (grid[i][j] == 2) rotten.push({ i, j });
            }
        }

        // BFS
        while (fresh && rotten.size()) {
            ++rounds;

            for (int i = rotten.size(); i; --i) {
                auto rot = rotten.front();
                rotten.pop();

                // Up
                if (rot.first && grid[rot.first - 1][rot.second] == 1) {
                    --fresh;
                    grid[rot.first - 1][rot.second] = 2;
                    rotten.push({ rot.first - 1, rot.second });
                }
                // Down
                if (rot.first != r - 1 && grid[rot.first + 1][rot.second] == 1) {
                    --fresh;
                    grid[rot.first + 1][rot.second] = 2;
                    rotten.push({ rot.first + 1, rot.second });
                }
                // Left
                if (rot.second && grid[rot.first][rot.second - 1] == 1) {
                    --fresh;
                    grid[rot.first][rot.second - 1] = 2;
                    rotten.push({ rot.first, rot.second - 1 });
                }
                // Right
                if (rot.second != c - 1 && grid[rot.first][rot.second + 1] == 1) {
                    --fresh;
                    grid[rot.first][rot.second + 1] = 2;
                    rotten.push({ rot.first, rot.second + 1 });
                }
            }
        }

        return fresh ? -1: rounds;
    }
};