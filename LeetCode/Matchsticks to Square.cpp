#include <vector>
using namespace std;

//https://leetcode.com/problems/matchsticks-to-square/
/*
 * 	This is a (Backtracking) DFS, potentially DP problem
 *
 * 	First of all, given a set of matches, one can check if it is even possible to form a square
 * 	by first obtaining the sum of lengths, and see if it can be perfectly divisible by 4.
 * 	Also, number of matches must exceed or equal 4.
 *
 * 	For DFS, each match must exactly belong to one group. Therefore we imagine a decision tree
 * 	of N levels, and at each level, we will choose to make the match belong to either of 4 sides,
 * 	say group1, group2, group3 and group4.
 *
 * 	You can check when we ran out of matches, whether g1,g2,g3 and g4 are all equal to target length.
 * 	If yes, then definitely a square is formed.
 *
 * 	One fact is that given the divisible by 4 is established, if 3 sides are already formed, then the
 * 	last side must be formable too! This may lead us for early termination by checking whether 3 sides
 * 	had formed target length already or not.
 *
 * 	One trick is to sort matches descending order before recursion. This is because longer match will be
 * 	used first, and if impossible, will lead to early termination which is good
 *
 * 	=============================
 *
 * 	There is a valid Dynamic Programming solution in leetcode, but it is considered harder to implement due to
 * 	involvement of encoding states in integer32. If interested, one may visit the solution there
 */

class Solution {
public:
	bool makesquare(vector<int>& matchsticks) {
		//	You need at least 4 matchsticks
		if (matchsticks.size() < 4) return false;

		//	First, obtain the sum of matchsticks
		int sum = 0;
		for (int i : matchsticks) sum += i;

		int target = sum / 4;
		//	If it is not perfectly divisible by 4, return false immediately
		if (sum / 4.0 != target) return false;

		return dfs(0, matchsticks, target, target, target, target);
	}



	bool dfs(int depth, vector<int>& matchsticks, int g1, int g2, int g3, int g4) {
		if (g1 == g2 && g2 == g3 && g1 == 0 ||
			g1 == g3 && g3 == g4 && g1 == 0 ||
			g2 == g3 && g3 == g4 && g2 == 0)
			return true;

		int match = matchsticks[depth];

		//	Attempt to fit in g1, g2, g3 or g4
		return (g1 - match >= 0 && dfs(depth + 1, matchsticks, g1 - match, g2, g3, g4) ||
			g2 - match >= 0 && dfs(depth + 1, matchsticks, g1, g2 - match, g3, g4) ||
			g3 - match >= 0 && dfs(depth + 1, matchsticks, g1, g2, g3 - match, g4) ||
			g4 - match >= 0 && dfs(depth + 1, matchsticks, g1, g2, g3, g4 - match));
	}
};