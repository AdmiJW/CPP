#include <vector>
using namespace std;

//https://leetcode.com/problems/array-nesting/
/*
 *	This is a Depth First Search problem.
 *
 * 	First thought would be to brute force this problem. Every element, we can simulate the process by walking
 * 	through the process, recording the length of the set and stopping whenever we met back an element that is
 * 	already visited.
 * 	However, this algorithm by itself takes O(N^2) time and is insufficient to solve the problem.
 *
 *  To reduce O(N^2) to O(N), we would utilize extra space of O(N) to record which elements is already 'walked'
 *  before in a cycle.
 *  The core idea is, any set of indices will always be a cycle. We want to find the maximum length of cycle
 *  possible, and no matter which element we choose in a cycle, we will always obtain the same length. See:
 *
 *  For example, we have a longest set:
 *  		{ 5, 6, 2, 0 }
 *  No matter if we enter the cycle from 5, or enter from 0, we always end up determining the cycle length is 4,
 *  because it is the same cycle afterall.
 *
 *  Therefore, by recording the elements that we'd already visited before, at worst we will only iterate over
 *  same element twice (Say if each element maps to itself). Therefore time complexity is O(N).
 */

class Solution {
public:
	int arrayNesting(vector<int>& nums) {
		const int len = nums.size();
		vector<bool> isVisited(len, 0);
		int res = 0;

		// Every element could be inside the longest cycle. Check
		for (int i = 0; i < len; ++i) {
			int curr = nums[i];
			int cycleLen = 0;

			while (!isVisited[curr]) {
				isVisited[curr] = true;
				++cycleLen;
				curr = nums[curr];
			}
			res = max(res, cycleLen);
		}
		return res;
	}
};