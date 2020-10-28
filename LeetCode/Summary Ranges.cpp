

//https://leetcode.com/problems/summary-ranges/

#include <string>
#include <vector>
#include <iostream>

/*
	This is a Array problem.

	Given the property that the array is sorted, we could just keep the pointer to the current progress in the array.
	While we are not at the end of array yet, loop through this:

		Set the current element pointed by pointer as range starting point. 
		Then, while the next element is one greater than this current element, increment the index
		At the end, we will stop at either array end or the end of the range.
		Check if the start index is same as end index. If yes, just append the number. Otherwise, append the range

*/

class Solution {
public:
	std::vector<std::string> summaryRanges(std::vector<int>& nums) {
		std::vector<std::string> res;

		const int len = nums.size();
		int idx = 0;
		
		while (idx < len) {
			int start = idx;

			while (idx + 1 < len && nums[idx+1] == nums[idx] + 1)
				idx++;

			res.push_back(
				idx == start ? std::to_string(nums[start]) + "->" + std::to_string(nums[idx]) : std::to_string(nums[start])
			);
			idx ++;
		}

		return res;
	}
};

