#include <vector>
#include <queue>
using namespace std;

//https://leetcode.com/problems/is-graph-bipartite/
/*
 * 	This is a graph coloring problem. Asking whether there can be set A and B where each node can only be either in A or B,
 * 	and its neighbors can only in the other set, is just exactly same with coloring the graph with 2 different colors!
 *
 * 	------------------------------------------------------------
 *
 * 	One solution is by breadth first search. Starting out by coloring one node, its neighbors must be in another color.
 * 	If detected that neighboring nodes are of same color as parent node, then it is not a bipartite graph
 *
 * 	------------------------------------------------------------
 *
 * 	DFS solution also works well. Simply pass the colors array  which we use to record whether a node is in Set A
 * 	or B (or set) around.
 */

class Solution {
public:

	//	Breadth First Search solution using array to record colors
	bool isBipartite(vector<vector<int>>& graph) {
		const int n = graph.size();
		int* colors = new int[n] {};

		//	Each node loop
		for (int i = 0; i < n; ++i) {
			//	Subgraph visited already. Skip
			if (colors[i]) continue;

			//	Otherwise perform BFS
			queue<int> queue;
			int curr = 1;
			queue.push(i);
			colors[i] = 1;

			while (!queue.empty()) {
				int lvl = queue.size();
				while (lvl-- > 0) {
					int node = queue.front(); queue.pop();

					for (int adj : graph[node]) {
						if (colors[adj] == curr) return false;
						if (!colors[adj]) queue.push(adj);
						colors[adj] = curr == 1 ? 2 : 1;
					}
				}
				curr = curr == 1 ? 2 : 1;
			}
		}
		return true;
	}





	//	Depth First Search solution
	bool isBipartite2(vector<vector<int>>& graph) {
		const int n = graph.size();
		int* colors = new int[n] {};

		for (int i = 0; i < n; ++i) {
			if (colors[i]) continue;
			colors[i] = 1;
			if (!recurse(i, colors, graph) ) return false;
		}
		return true;
	}

	bool recurse(int n, int* colors, vector<vector<int>>& graph) {
		int other = colors[n] == 1 ? 2 : 1;
		for (int adj : graph[n]) {
			if (colors[adj] == colors[n]) return false;
			if (colors[adj]) continue;		//	Already explored
			colors[adj] = other;
			if (!recurse(adj, colors, graph)) return false;
		}
		return true;
	}
};