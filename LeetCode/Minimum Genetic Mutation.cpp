#include <string>
#include <queue>
#include <unordered_set>
#include <vector>
using namespace std;

// https://leetcode.com/problems/minimum-genetic-mutation/
/*
 * 	This is a BFS, HashMap/HashSet problem.
 *
 * 	Starting from the start string, we will be generating all of its possible mutations. All mutations
 * 	that are inside the bank will be pushed to the queue for next iteration.
 *
 * 	Since we are using Breadth First Search, we can guarantee that whenever we found the mutation string matches
 * 	end, it is always the minimum number of mutations for the BFS depth.
 *
 * 	Generating all mutations for a string takes approximately O(SE) where S = string length, E = number of genetic elements (ACGT)
 * 	At worst case we will generate all mutations B times, where B = bank size.
 *
 * 	Thus time complexity O(BSE)
 */

class Solution {
public:
    int minMutation(string start, string end, vector<string>& bank) {
		queue<string> queue;
		unordered_set<string> visited(bank.begin(), bank.end());

		char elem[] = {'A', 'C', 'G', 'T'};

		visited.erase(start);
		queue.push(start);

		for (int depth = 0; !queue.empty(); ++depth) {

			for (int layerSize = queue.size(); layerSize > 0; --layerSize) {
				string toMutate = queue.front();
				queue.pop();
				if (toMutate == end) return depth;

				for (int i = 0; i < toMutate.length(); ++i) {
					char ori = toMutate[i];

					for (char c : elem) {
						toMutate[i] = c;

						if (visited.count(toMutate)) {
							queue.push(toMutate);
							visited.erase(toMutate);
						}
					}

					toMutate[i] = ori;
				}
			}
		}

		return -1;
    }
};