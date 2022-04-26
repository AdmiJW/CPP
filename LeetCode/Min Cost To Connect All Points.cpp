#include <vector>
using namespace std;

//https://leetcode.com/problems/min-cost-to-connect-all-points/
/*
 * 	This is a minimum spanning tree (MST) problem (Greedy).
 * 	Minimum spanning tree is a subgraph of the original graph where the number of edges is exactly N-1, but
 * 	covers every node in the graph, and the total weight of the edges is minimal.
 *
 * 	There are two main MST algorithms: Kruskal's Algorithm and Prim's Algorithm.
 *
 *  For this particular problem, since every node is "logically" connected to any other node, we can solve this
 *  in O(N^2) time and O(N) space using optimized Prim's algorithm.
 *
 *  ------------------------------------------------
 *
 *  We will have an array: weights[] which weight[i] indicates at the current state of the MST, what is the minimum
 *  weight to reach node i.
 *
 *  Therefore initially our MST is empty, so the distance to any other nodes are infinity, except for one particular
 *  node we will start at, set it to 0.
 *
 *  Since we have to include N nodes in our MST, we iterate N times:
 *
 *  	> Select the new node to include into our MST, which we will choose the one with minimal weights[] value.
 *  	> Update the total weight into our result.
 *  	> Then, since this new node is included into MST, we have to update all other values inside weights[] that
 *  	  aren't included yet into the MST.
 */


class Solution {
public:
    int minCostConnectPoints(vector<vector<int>>& points) {
		const int len = points.size();

		int nodesIncluded = 0;
		int res = 0;
		vector<bool> visited(len);
		vector<int> weights(len, INT32_MAX);
	
		weights[0] = 0;

		while (nodesIncluded < len) {
			int minNode = -1;
			int minCost = INT32_MAX;

			// Select a new node to be included in the Minimum Spanning Tree
			for (int i = 0; i < len; ++i) {
				if (visited[i]) continue;
				if (weights[i] < minCost) {
					minNode = i;
					minCost = weights[i];
				}
			}

			// Include the node into the minimum spanning tree
			res += minCost;
			visited[minNode] = true;
			++nodesIncluded;

			// From the newly added node, update the distances to those node whose haven't been visited yet
			for (int i = 0; i < len; ++i) {
				if (visited[i]) continue;
				int cost = abs(points[minNode][0] - points[i][0]) + abs(points[minNode][1] - points[i][1]);
				if (cost < weights[i]) weights[i] = cost;
			}
		}

		return res;
    }
};