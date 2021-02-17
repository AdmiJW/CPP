#include <vector>
using namespace std;

//https://leetcode.com/problems/container-with-most-water/
/*
 * 	This is a Array Two pointers question.
 *
 * 	At first thought, we might want to test out all possible combinations. This way, for each first line, we will try
 * 	out all the possible second lines combinations. This result in O(N^2) time complexity. Can we do better?
 *
 * 	To do better, we have to make observations! Assume we start at both ends. If we are being smart and greedy, we would
 * 	try to keep the higher line, and move forward the lower one. Keep doing this, and eventually all containers will be
 * 	shrinked and all cases will be tried. Among those cases, there must be a optimum solution inside!
 */

class Solution {
public:
	int maxArea(vector<int>& height) {
		const int len = height.size();
		int l = 0, r = len - 1;
		int res = 0;

		while (l < r) {
			res = max(res, (r - l) * min(height[l], height[r]));

			if (height[l] > height[r]) --r;
			else ++l;
		}
		return res;
	}
};