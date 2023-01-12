#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <string>
using namespace std;

// https://leetcode.com/problems/number-of-nodes-in-the-sub-tree-with-the-same-label/
/*
 * This is a tree, recursion DFS problem.
 *
 * Since the labels are only lowercase alphabet letters of 26 characters, we can simply do recursion and query
 * the frequency of each letters of the subtree. Then using that information to solve the original problem of
 * how many nodes in subtree that has the same label.
 */




class Solution {
public:
    vector<int> res;

    vector<int> countSubTrees(int n, vector<vector<int>>& edges, string& labels) {
        res = vector<int>(n);

        // Build tree
        unordered_map<int, vector<int>> tree;
        for (auto& edge: edges) {
            tree[edge[0]].push_back(edge[1]);
            tree[edge[1]].push_back(edge[0]);
        }

        // Visited record
        unordered_set<int> visited;

        recurse(0, labels, tree, visited );
        return res;
    }

    vector<int> recurse(int n, string& labels, unordered_map<int, vector<int>>& tree, unordered_set<int>& visited) {
        int i = labels[n] - 'a';
        visited.insert(n);

        vector<int> count(26, 0);
        ++count[ i ];

        for (int child: tree[n]) {
            if (visited.count(child)) continue;
            vector<int> childCount = recurse(child, labels, tree, visited);
            for (int c = 0; c < 26; ++c) count[c] += childCount[c];
        }

        res[ n ] = count[ i ];
        return count;
    }
};