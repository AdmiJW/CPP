#include <string>
#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>
using namespace std;

//https://leetcode.com/problems/word-ladder-ii/
/*
 * 	This is a HARD to implement Graph, BFS, Backtracking problem.
 *
 * 	First of all, once you realize this is a graph problem, you may be tempted to immediately build the graph. A node
 *  containing a string is connected with another node if they differ by one character only.
 *  We can do this by permutating the string character by character, since the string is small.
 *
 *  However, we have to think once the graph is built, how are we going to retrieve all the shortest paths? BFS will do,
 *  but do we need to maintain a list of paths and at the end, pick up all the ones that are valid? It can be inefficient.
 *
 *  Instead, we build the graph using BFS. We intelligently build the graph that contain the property:
 *  	>	No nodes will connect back to upper layer in BFS
 *  	>	No nodes will interconnect with other nodes in same layer
 *  This way, once the graph is built, we can use backtracking to retrieve the path without costing too much on the performance.
 */

class Solution {
public:
	int len;
	string endWord;
	vector<vector<string>> res;
	unordered_map<string, vector<string>> graph;
	unordered_set<string> availableNodes;


	vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
		len = wordList.size();
		this->endWord = endWord;
		availableNodes = unordered_set<string>(wordList.begin(), wordList.end());	// Set with all wordlist available in it

		// Build the graph using BFS. If return false, means cannot reach endWord given beginWord
		if (!bfsBuildGraph(beginWord)) return res;

		// Perform backtracking on the graph
		vector<string> progress;
		progress.push_back(beginWord);
		backtrack(beginWord, progress);
		return res;
	}


	// Build a graph using BFS, given the beginning word
	// The graph is guaranteed to not contain a cycle, and nodes in same layer does not interconnect
	// To optimize, stop when the layer contains the endString already. No need to further extend
	bool bfsBuildGraph(string beginWord) {
		vector<string> bfs;
		bfs.push_back(beginWord);
		bool endInLayer = false;

		while (!bfs.empty() && !endInLayer) {
			// Store all the nodes in current layer in a Set (No nodes will connect between same layers)
			unordered_set<string> currLayer(bfs.begin(), bfs.end());
			bfs.clear();

			for (string s : currLayer) {
				availableNodes.erase(s);

				// Generate available permutations
				for (int i = 0; i < s.size(); ++i) {
					string perm = s;
					for (char c = 'a'; c <= 'z'; ++c) {
						perm[i] = c;

						if (availableNodes.count(perm) && !currLayer.count(perm)) {
							if (perm == endWord) endInLayer = true;	// Already found end
							graph[s].push_back(perm);
							bfs.push_back(perm);
						}
					}
				}
			}
		}
		return endInLayer;
	}


	// Backtracking on the graph
	void backtrack(string currWord, vector<string>& progress) {
		if (currWord == endWord) {
			res.emplace_back(vector<string>(progress.begin(), progress.end()));
			return;
		}

		// A leaf node which does not lead to endWord
		if (!graph.count(currWord)) return;

		for (string next : graph[currWord]) {
			progress.push_back(next);
			backtrack(next, progress);
			progress.pop_back();
		}
	}

};