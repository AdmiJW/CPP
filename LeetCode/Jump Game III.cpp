#include <vector>
using namespace std;

//https://leetcode.com/problems/jump-game-iii/
/*
 *	This is a graph DFS/BFS problem with possible recursion implementation
 *
 *	From a node with a specific value, I can jump to the node of index i - val or i + val. This is the graph edges
 *	connecting from this current node to the node i-val and i+val.
 *
 *	Therefore we have to explore the graph and see if we ever encounter the node 0 or not. If yes, then immediately we can
 *	return true.
 *
 *	Do remember that cycle can possibly exist in the graph. Therefore we need a way to record if we had already visited the
 *	graph or not to prevent revisiting a node that is currently already in the midst of visited, and therefore a node
 *	should never be visited twice
 *
 *	Worst case complexity is always O(N) for both space and time. Imagine [1,1,1,1,1,1,1,1,1,1,0] and starting at index 0.
 *	Every node has to be explored and recorded.
 */

class Solution {
public:
	bool canReach(vector<int>&arr, int start) {
		bool* visited = new bool[arr.size()]{};
		bool res = recurse(arr, start, visited);
		delete[] visited;
		return res;
	}
	bool recurse(vector<int>& arr, int i, bool* visited) {
		if (i < 0 || i >= arr.size() || visited[i]) return false;
		if (!arr[i]) return true;

		visited[i] = true;
		return recurse(arr, i - arr[i], visited) || recurse(arr, i + arr[i], visited);
	}






	bool canReach2(vector<int>& arr, int start) {
		const int len = arr.size();
		vector<int> deque;
		deque.push_back(start);

		bool* visited = new bool[len];

		while (!deque.empty()) {
			int node = deque.back();
			deque.pop_back();
			int val = arr[node];

			if (!val) {
				delete[] visited;
				return true;
			}
			visited[node] = true;

			if (node - val >= 0 && !visited[node - val]) deque.push_back(node - val);
			if (node + val < len && !visited[node + val]) deque.push_back(node + val);
		}
		delete[] visited;
		return false;
	}
};