#include <vector>
#include <string>
using namespace std;

//https://leetcode.com/problems/minimum-time-to-make-rope-colorful/
/*
 *	This is a greedy problem.
 *
 *	The best way to remove balloons to ensure no grouped colors together, are, of course,
 *	to identify identical color groups and remove all of them except one.
 *	Intuitively, there is no need to remove lone balloons. We only need to reduce group of identical balloons
 *	that are adjacent together.
 *
 *	Therefore, the problem can be easily solved by iterating the balloons once, left to right,
 *	identifying the balloon groups and remove all of them except the MAXIMUM COST balloon so that only one of them is left
 */



class Solution {
public:
    int minCost(string colors, vector<int>& neededTime) {
		int res = 0;

		// sum is the sum of neededTime of a colored balloon group
		// max is the maximum neededTime among a group of colored balloon group
		char color = ' ';
		int sum = 0, maxInGrp = 0;


		for (int i = 0; i < colors.length(); ++i) {
			char c = colors[i];
			int t = neededTime[i];

			if (c != color) {
				res += sum - maxInGrp;
				sum = 0;
				maxInGrp = INT32_MIN;
			}

			color = c;
			sum += t;
			maxInGrp = max(t, maxInGrp);
		}

		res += sum - maxInGrp;
		return res;
    }
};