#include <vector>
#include <queue>
#include <unordered_set>
using namespace std;

//https://leetcode.com/problems/keys-and-rooms/
/*
 * 	This is a simple Graph DFS/ BFS problem.
 *
 * 	For all visited rooms, simply record in visited Set. Remember not to visit any previously visited room!
 * 	At the end, simply check if Set length == total no of rooms
 */


class Solution {
public:
	
	//	BFS
	bool canVisitAllRooms(vector<vector<int>>& rooms) {
		const int len = rooms.size();
		unordered_set<int> visited;
		queue<int> queue;

		visited.insert(0);
		queue.push(0);

		while (!queue.empty()) {
			for (int k : rooms[queue.front() ] ) {
				if (!visited.count(k)) queue.push(k);
				visited.insert(k);
			}
			queue.pop();
		}

		return visited.size() == len;
	}


	//	DFS
	bool canVisitAllRooms2(vector<vector<int>>& rooms) {
		const int len = rooms.size();
		unordered_set<int> visited;

		recurse(rooms, 0, visited);
		return visited.size() == len;
	}
	void recurse(vector<vector<int>>& rooms, int curr, unordered_set<int>& visited) {
		visited.insert(curr);
		for (int k : rooms[curr]) {
			if (!visited.count(k)) recurse(rooms, k, visited);
		}
	}
};