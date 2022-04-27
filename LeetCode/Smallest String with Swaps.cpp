#include <string>
#include <algorithm>
#include <vector>
using namespace std;

//https://leetcode.com/problems/smallest-string-with-swaps/
/*
 * This is a graph, DFS, optionally Union find (Disjoint set) problem. Quite hard to implement
 *
 * Prior to discussing the algorithm, you must observe a key point from the problem: Pairs can be used infinitely.
 * This indicates that characters at any of the connected pairs can be moved freely! See:
 *
 * 		Pairs: [0,1],[1,2],[2,3]
 *
 * In the above case, you shall realize that characters at (0,1,2,3) can be moved freely throughout among themselves!
 * The character at index 0 can be moved to index 1, 2 or 3 with no restriction!
 *
 * However, this rule does have a 'locality' to it. See:
 *
 * 		Pairs: [0,1],[1,2],[3,4]
 *
 * Although character at (0,1,2) can move freely among themselves, character at (3,4) cannot move to (0,1,2)!
 * (Hopefully you see why with the disjoint set now?)
 *
 * With this being clear, you can realize:
 * 	- If we have a list of indices and characters within a "local" group (Eg: indices and characters of (0,1,2) in above
 *    case), we can easily sort them to obtain how they should be rearranged to obtain lowest lexicographical order!
 *
 * -----------------------------------------------------------------------
 *
 * For the graph DFS solution, simply build a adjacency list out of the pairs first. Then, using DFS, we can easily
 * obtain every indices and characters within a local group. Then we would sort them, and rearrange the characters
 * accordingly in the result string.
 */

class Solution {
public:
    string smallestStringWithSwaps(string s, vector<vector<int>>& pairs) {
		const int len = s.length();

		vector<vector<int>> adj(len, vector<int>());
		vector<bool> visited(len);

		// Create adjacency list
		for (auto& p : pairs) {
			adj[p[0]].push_back(p[1]);
			adj[p[1]].push_back(p[0]);
		}

		// For each of the 'local' groups
		for (int i = 0; i < len; ++i) {
			if (visited[i] || adj[i].empty()) continue;

			// DFS to find out every character included in the local group
			vector<int> indices;
			vector<char> ch;
			dfs(s, i, visited, indices, ch, adj);

			// Sort them to obtain how the local group should be arranged to lowest lexicographical
			sort(indices.begin(), indices.end());
			sort(ch.begin(), ch.end());

			// Arrange them back 
			for (int j = 0; j < indices.size(); ++j)
				s[ indices[j] ] = ch[j];
		}

		return s;
    }
	

	// Simple dfs to explore the graph, adding indices and characters
	void dfs(string& s, int i, vector<bool>& visited, vector<int>& indices, vector<char>& ch, vector<vector<int>>& adj) {
		if (visited[i]) return;

		indices.push_back(i);
		ch.push_back(s[i]);
		visited[i] = true;

		for (int next : adj[i]) dfs(s, next, visited, indices, ch, adj);
	}

};