#include <vector>
#include <unordered_set>
#include <deque>
using namespace std;

//https://leetcode.com/problems/minimum-height-trees/
/*
 * 	In a tree where every node can be travelled from another root node with only ONE path. (Yes, since there are no cycles,
 * 	a node can be accessed from another node with only one path, NO MULTIPLE PATHS ARE AVAILABLE)
 *
 * 	We have to think of a root node that we select, that gives us the minimum depth tree available.
 *
 * 	-------------------------------------------------------------------------------------------------
 *
 * 	One unexpected thought is: How many such minimum depth tree that it can form, given any number of nodes?
 * 	The answer for that is: Maximum 2.
 *
 * 	We can imagine the whole tree as a circle or a area. To choose the root node, we must not choose the edge
 * 	ones because the distance from one edge node to another end would span over a great distance and thus resulting in
 * 	not the minimum depth tree.
 * 	Therefore, the optimal root node should be to choose the center ones (Centroid). And by proving by contradiction,
 * 	it can be shown that only maximum 2 such root node can exist in a tree.
 *
 * 	-------------------------------------------------------------------------------------------------
 *
 * 	Suppose we have 3 nodes that result in minimum depth tree. When we trimmed them from the leaf nodes, suppose
 * 	the nodes left are those 3 nodes. Those 3 nodes must now have depth of only 1. However, it is impossible since
 * 	those 3 nodes are to be connected somehow, and without cycles. The only way to form equal depth is by a triangular
 * 	edge, but that would oppose the property of tree. Therefore, the maximum is only 2.
 *
 * 	As you can see, since every node must be connected. One way to solve this is like topological sorting, eliminating
 * 	those leaves nodes, and check to see if the nodes connected are becoming leaf nodes as well. If they does, then
 * 	remove them in the next turn.
 * 	By shredding off the leaf nodes in each turn, eventually we would reach at the centroid nodes which is the root nodes
 * 	that will form minimum depth tree.
 *
 *  ============================================================================================
 *
 * 	Another way is to find out the 2 edge nodes, like 'diameter' of the whole tree. First iteration DFS we will start
 * 	with any node, and get the maximum depth node from it. Then in the second DFS, we will use that last node which is
 * 	one of edges node, and attempt to find the other maximum depth node, which is on the other end, while tracking the
 * 	path used to get there.
 * 	Since now we have the nodes on the two opposite ends, we can find out the middle distance, and obtain the centroid
 * 	for it. If the length is even (like there are 2 nodes in between), then we have to return 2 centroid nodes in our
 * 	answer
 *
 */




class Solution {
public:
    vector<int> findMinHeightTrees(int n, vector<vector<int>>& edges) {
        if (n == 1) return { 0 };
        if (n == 2) return { 0, 1 };

        // Construct adjacency list
        vector<unordered_set<int>> adj( n, unordered_set<int>() );
        for (auto& edge : edges) {
            adj[edge[0]].insert(edge[1]);
            adj[edge[1]].insert(edge[0]);
        }


        // Begin trimming - Keep trimming those nodes which only has one connection
        deque<int> trimmer;
        for (int i = 0; i < n; ++i)
            if (adj[i].size() == 1) trimmer.push_back(i);
    

        // We must trim until the nodes left are less than or equal 2
        while (n > 2) {
            int bst = trimmer.size();

            for (int i = 0; i < bst; ++i) {
                int leaf = trimmer.front();
                trimmer.pop_front();

                for (int connectedNode : adj[leaf]) {
                    adj[connectedNode].erase(leaf);

                    if (adj[connectedNode].size() == 1)
                        trimmer.push_back(connectedNode);
                }

                --n;
            }
        }
        
        return vector<int>(trimmer.begin(), trimmer.end());
    }
};