#include <unordered_map>
#include <vector>
using namespace std;

//https://leetcode.com/problems/redundant-connection/
/*
 *  This is a Tree / Graph - Disjoint set (Union Find) problem
 *  Nodes can be clustered as first, like:
 *
 *  (2)-(3)-(4)-(5)                            (1)-(7)-(9)-(8)
 *
 *  Now, connecting (1) and (2) will not cause any cycle to occur, and it is perfectly valid.
 *  Cycles occur when both sides of node occur in the same cluster, like
 *
 *  (2)-(3)-(4)-(5)-(1)-(7)-(9)-(8)
 *
 * 	Attempt to connect any of 2 nodes within will definitely cause cycle!
 *
 *  The easiest solution is to use Disjoint Set (If you are acknowledged of it, of course).
 *  Here I implemented one quick DisjointSet class that is not too optimized, but does the job
 *
 *  =====================================================================
 *
 *  Without using disjoint set, we can do the job in worse time complexity using DFS.
 *
 *  For each of the edges (u,v), we do not introduce the edge into the graph we had built first. We perform dfs
 *  on the existing graph to see whether u and v are already connected or not.
 */

class DisjointSet {
	unordered_map<int, int> map;
public:
	void insert(int node) {
		map.insert({ node, -1 });
	}

	int findParent(int node) {
		if (map[node] == -1) return node;
		int parent = findParent(map[node]);
		map[node] = parent;
		return parent;
	}

	bool unionNode(int node1, int node2) {
		int p1 = findParent(node1);
		int p2 = findParent(node2);
		if (p1 == p2) return false;
		map[p1] = p2;					//Supposedly connect by rank, but whatever
		return true;
	}
};

class Solution {
public:
	//	Disjoint Set solution
	vector<int> findRedundantConnection(vector<vector<int>>& edges) {
		DisjointSet ds;

		for (auto& e : edges) {
			ds.insert(e[0]);
			ds.insert(e[1]);

			if (!ds.unionNode(e[0], e[1])) return e;
		}
		return {};
	}
};