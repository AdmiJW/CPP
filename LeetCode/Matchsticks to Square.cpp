#include <vector>
using namespace std;


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