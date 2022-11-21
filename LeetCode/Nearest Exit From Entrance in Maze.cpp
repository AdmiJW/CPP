
#include <vector>
#include <queue>

// https://leetcode.com/problems/nearest-exit-from-entrance-in-maze
/*
 * This is a BFS problem.
 * 
 * Starting from the entrance, we can use BFS to find the nearest exit, layer by layer.
 * Use a queue to store the coordinates of the cells to perform BFS.
 */



class Solution {
public:
    int nearestExit(vector<vector<char>>& maze, vector<int>& entrance) {
        int directions[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

        queue<vector<int>> queue;
        queue.push(entrance);
        maze[entrance[0]][entrance[1]] = '+';

        for (int i = 0; !queue.empty(); i++) {
            for (int j = queue.size(); j > 0; --j) {

                vector<int> current = queue.front();
                queue.pop();
                if (isExit(maze, current, entrance)) return i;
                
                for (auto& direction : directions) {
                    int x = current[0] + direction[0];
                    int y = current[1] + direction[1];

                    if (x >= 0 && x < maze.size() && y >= 0 && y < maze[0].size() && maze[x][y] == '.') {
                        maze[x][y] = '+';
                        queue.push({x, y});
                    }
                }
            }
        }

        return -1;
    }


    bool isExit(vector<vector<char>>& maze, vector<int>& current, vector<int>& entrance) {
        return !( current[0] == entrance[0] && current[1] == entrance[1] ) &&
            ( current[0] == 0 || current[0] == maze.size() - 1 || current[1] == 0 || current[1] == maze[0].size() - 1 );
    }
};