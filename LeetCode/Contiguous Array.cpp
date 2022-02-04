
#include <vector>
#include <unordered_map>
using namespace std;

//https://leetcode.com/problems/contiguous-array/

/*
 * 	The key for O(n) solution is that realize if we plot the graph of the counter which every time we encounter 1, it increments by 1 and
 * 	every time it encounters 0, it decrements by 1.
 * 	We have to observe the graph that every time it has equal zeroes and ones, it would touch the same level again (Not necessary 0).
 * 	Therefore we have to take a hash map to record the earliest index that the point is passed before. Later if the point is touched again,
 * 	it straight indicates there is a equal ones and zeroes somewhere and we have to check if the length is the maximum. This way we could achieve
 * 	O(n) time complexity in exchange for O(n) space complexity.
 */


class Solution {
public:

    // Prefix sum + HashMap solution - Treat 0 as -1.
    int findMaxLength(vector<int>& nums) {
		unordered_map<int, int> record;
		record[0] = 0;
		int pos = 0;
		int res = 0;

		for (int i = 0; i < nums.size(); ++i) {
			pos += (nums[i] == 0) ? -1 : 1;

			//We shall consider the first element in array to be indexed from 1 onwards, as we have defined starting point as 0
			if (record.count(pos)) {
				res = max(res, i - record[pos] + 1);
			}
			
			if (!record.count(pos)) record[pos] = i + 1;
		}
		return res;
    }
};