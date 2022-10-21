#include <vector>
#include <unordered_map>
using namespace std;

//https://leetcode.com/problems/contains-duplicate-ii/
/*
 * 	This is a sliding window + HashMap problem.
 *
 * 	We have to return true if there is duplicated element within sub-window of the array of size k+1.
 * 	Therefore, use the sliding window technique to update our window HashMap that a number is within the current subwindow or not.
 */

class Solution {
public:
	bool containsNearbyDuplicate(vector<int>& nums, int k) {
		unordered_map<int, bool> window;

		for (int i = 0; i <= min( (int)nums.size() - 1, k); ++i) {
			if (window[nums[i]]) return true;
			window[nums[i]] = true;
		}

		for (int i = k + 1; i < nums.size(); ++i) {
			window[nums[i - k - 1]] = false;
			if (window[nums[i]]) return true;
			window[nums[i]] = true;
		}

		return false;
	}
};