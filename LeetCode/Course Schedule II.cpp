#include <vector>
#include <queue>
#include <unordered_set>
#include <unordered_map>
using namespace std;


//https://leetcode.com/problems/course-schedule-ii/
/*
 * 	This question involves directed graphs which we have to topologically sort it. (Meaning, return an array of nodes which the nodes are
 * 	sorted in such a way that can be think of having preconditions, some node has to be visited first before visiting this node.
 *
 * 	This can be solved using Topological sort algorithm (For more info, see Topics/Algorithms/Graph_Topological_Sort
 */


class Solution {
public:
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
		unordered_map<int, unordered_set<int>> map;
		vector<int> incoming(numCourses, 0);

		// Construction of graph: { node -> set of neighbors }
		for (auto& pairs : prerequisites) {
			map[pairs[1]].insert(pairs[0]);
			++incoming[pairs[0]];
		}

		queue<int> queue;

		// The ones we'll start exploring is the one without any prerequisites
		for (int i = 0; i < numCourses; i++)
			if (incoming[i] == 0) queue.push(i);

		vector<int> res;
		int i = 0;

		while (!queue.empty()) {
			int polled = queue.front();
			queue.pop();

			if (map.count(polled)) {
				// Explore neighbors
				for (int next : map[polled]) {
					// Only explore if after deducting the inbound edge, we get in-degree of 0.
					if (--incoming[next] == 0)
						queue.push(next);
				}
			}
			++i;
			res.push_back(polled);
		}

		return (i < numCourses) ? vector<int>() : res;
    }
};