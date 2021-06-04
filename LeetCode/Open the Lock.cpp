#include <vector>
#include <unordered_set>
#include <queue>
using namespace std;

//https://leetcode.com/problems/open-the-lock/
/*
 * 	This is a Breadth first search problem.
 *
 * 	Starting from 0000, we can make 8 moves. Here how it is:
 *	>	We can pick 1 out of 4 digits, and either spin up or down.
 *
 *	Spinning creates a new permutation of 4 digit number, which may be the correct way to the solution, or it doesn't
 *	We won't know until we've explored it.
 *
 *	Therefore, using BFS, we explore the moves, but remember to avoid computing for the numbers we've seen before. Also,
 *	deadends represent we cannot move anymore, so if we obtained a deadend, do not generate moves for it.
 *
 *	BFS is plausible because the states of numbers are limited. Maximum states is only 0000 to 9999, which is 10000.
 *	With this, we can say that the time complexity of the algorithm also be constant time.
 *
 *	==================================================================
 *
 *	The algorithm can be improved using bi-directional BFS, where in one turn, I explore subchild of 0000, then in next
 *	turn, i explore subchild of target, then take turns.
 *
 *	Although bi-directional BFS doesn't reduce the worst case time complexity, it does try to reduce the time taken
 *	because the explore space is narrower.
 */

class Solution {
public:
	int openLock(vector<string>& deadends, string target) {
		unordered_set<string> setOfDeadend(deadends.begin(), deadends.end());
		unordered_set<string> visited;
		queue<string> bfs;
		int level = 0;

		if (setOfDeadend.count("0000")) return -1;
		visited.insert("0000");
		bfs.push("0000");

		while (!bfs.empty()) {
			int size = bfs.size();
			while (size--) {
				string pop = bfs.front(); bfs.pop();
				if (target == pop) return level;

				//	Generate the available 8 moves
				for (int d = 0; d < 4; ++d) {
					string spinup = pop;
					string spindown = pop;

					spinup[d] = (pop[d] == '9') ? '0' : pop[d] + 1;
					spindown[d] = (pop[d] == '0')? '9': pop[d] - 1;
				
					//	Spinning up this digit, it is a new number and not a deadend
					if (!visited.count(spinup) && !setOfDeadend.count(spinup)) {
						visited.insert(spinup);
						bfs.push(spinup);
					}
					//	Spinning down this digit, it is a new number and not a deadend
					if (!visited.count(spindown) && !setOfDeadend.count(spindown)) {
						visited.insert(spindown);
						bfs.push(spindown);
					}
				}
			}
			++level;
		}
		//	Finished BFS and found no target. Thus return -1
		return -1;
	}
};