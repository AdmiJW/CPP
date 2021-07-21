#include <string>
#include <vector>
using namespace std;

//https://leetcode.com/problems/push-dominoes/
/*
 * 	This is an array, DP based intuition (Not exactly DP) problem
 *
 * 	The brute force approach would involve O(N^2) time complexity, as the worst case is when only the first domino is pushed
 * 	to right, where other dominoes are vertically upright
 * 	We would iterate for N times, each time iterating through the string to see in that time moment, which domino would be tipped
 *
 * 	At first I thought about doing BFS on source dominoes. But then it ended up at this solution.
 *
 * 	Using a DP array, we can record what time does the domino ended up at the state it was currently.
 * 	For example, at index i, if the string character is 'R', and dp[i] = 3, it means the domino tilt to R due to a domino
 * 	that is 3 tiles away pushing it, like:
 *
 * 				  i
 * 			R . . .
 *
 * 	Result:
 *
 * 			R R R R
 * 	dp[i]   0 1 2 3
 *
 * 	Thus, we iterate thru the string to find source dominoes that has a initial force on it (dp[i] == 0 && c != '.')
 * 	Once found, we extend the force until it is no longer able to.
 * 	If we encounter a opposing force (Like L meets R), check the dp array to see when is the domino ended up in the current
 * 	state.
 * 	If dp[i] > currTime, then surely we could overwrite with the current force.
 * 	Otherwise if dp[i] == currTime, the force is balanced, so the domino should be '.'
 * 	Else, our current force cannot change the state of that domino.
 *
 * 	Time and space complexity is O(N)
 */

class Solution {
public:
	string pushDominoes(string dominoes) {
		const int len = dominoes.size();
		vector<int> dp(len, 0);

		// Locate source of forces to extend
		for (int i = 0; i < len; ++i) {
			char c = dominoes[i];
			if (c == '.' || dp[i] != 0) continue;	// Not a source of force

			// Extend left
			int time = 1;
			if (c == 'L') {
				for (int p = i - 1; p >= 0; ++time, --p) {
					if (dominoes[p] == 'L') break;						// Same direction
					if (dominoes[p] != '.' && dp[p] == 0) break;		// Do not manipulate other source of force
					// Standing domino, or 'R' domino that comes later
					if (dominoes[p] == '.' || dp[p] > time) {
						dominoes[p] = 'L';
						dp[p] = time;
					}
					// Balanced force
					else if (dp[p] == time) dominoes[p] = '.';
					// Impossible to extend the force further
					else break;
				}
			}
			// Extend Right
			else {
				for (int p = i + 1; p < len; ++time, ++p) {
					if (dominoes[p] == 'R') break;						// Same direction
					if (dominoes[p] != '.' && dp[p] == 0) break;		// Do not manipulate other source of force
					// Standing domino, or 'R' domino that comes later
					if (dominoes[p] == '.' || dp[p] > time) {
						dominoes[p] = 'R';
						dp[p] = time;
					}
					// Balanced force
					else if (dp[p] == time) dominoes[p] = '.';
					// Impossible to extend the force further
					else break;
				}
			}
		}
		return dominoes;
	}
};