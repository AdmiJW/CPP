#include <vector>
#include <unordered_map>
#include <unordered_set>
using namespace std;

// https://leetcode.com/problems/minimum-time-to-collect-all-apples-in-a-tree/
/*
 * This is a recursion DFS, Tree problem.
 *
 * Build the tree first. Then, we would maintain a global variable `time` to represent the minimum time to collect
 * all apples in the tree.
 *
 * Observe: Let say we are on node N and it has parent node P. It is mandatory that we arrive at node N from node P
 * using 2 times: Once (P -> N) and once (N -> P), since we must return to root node as stated in the problem.
 *
 * So, we can use recursion to solve this problem. On each node, we try to solve whether we have a need to arrive
 * at this node from the parent node, and if we do, we need to do (time := time + 2) to account for the arriving
 * trip and return trip.
 * As for whether we need to arrive at the node, depends on whether the node has apple, or any of its child has
 * apples or not.
 */

class Solution {
public:
    int time = 0;

    int minTime(int n, vector<vector<int>>& edges, vector<bool>& hasApple) {
        // Build tree
        unordered_map<int, vector<int>> tree;
        unordered_set<int> visited;
        for (auto& edge : edges) {
            tree[edge[0]].push_back(edge[1]);
            tree[edge[1]].push_back(edge[0]);
        }

        // Recurse
        visited.insert(0);
        for (int child: tree[0]) recurse(child, tree, visited, hasApple);

        return time;
    }

    bool recurse(int n, unordered_map<int, vector<int>>& tree, unordered_set<int>& visited, vector<bool>& hasApple) {
        bool res = hasApple[n];
        visited.insert(n);

        for (int child: tree[n]) {
            if (!visited.count(child))
                res |= recurse(child, tree, visited, hasApple);
        }

        if (res) time += 2;
        return res;
    }
};