package Easy;

#include <vector>
#include <unordered_map>
#include <queue>
using namespace std;

// https://leetcode.com/problems/find-if-path-exists-in-graph/
/*
 * This is a graph problem.
 * Simply construct the graph and do BFS search starting from source node.
 * Once we find the destination node, return true.
 * If we exhaust all nodes and cannot find the destination node, return false.
 */



class Solution {
public:
    bool validPath(int n, vector<vector<int>>& edges, int source, int destination) {
        // Construct graph
        unordered_map<int, vector<int>> graph;
        for (auto& edge : edges) {
            graph[edge[0]].push_back(edge[1]);
            graph[edge[1]].push_back(edge[0]);
        }

        // BFS search
        vector<bool> visited(n, false);
        queue<int> queue;
        queue.push(source);

        while (!queue.empty()) {
            int node = queue.front();
            queue.pop();

            if (node == destination) return true;
            if (visited[node]) continue;

            visited[node] = true;
            if (!graph.count(node)) continue;

            for (int neighbor : graph[node]) {
                if (!visited[neighbor]) queue.push(neighbor);
            }
        }

        return false;
    }
};