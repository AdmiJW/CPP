#include <algorithm>
#include <vector>
using namespace std;

//https://leetcode.com/problems/4sum/
/*
 *	This is a two pointers, sorting problem (Deserved to be hard?)
 *
 *	In 2 sum problem, what we could do is to have two pointers in SORTED ARRAY (left initially points to smallest element,
 *	and right points to largest element). By summing this two element up, we compare with target.
 *
 *	>	If sum > target, that means the right pointer too large. We decrement the right pointer
 *	>	If sum < target, that means the left pointer too small. We increment the left pointer
 *	>	If sum == target, we found one solution. After saving, we increment left & right pointer.
 *
 *	Another solution to 2 sum is to use HashSet, where we can immediately check for another number if it exists or not
 *
 *	Let's see how we can apply this technique in our solution:
 *
 *	We'll fix n1, n2 in a sorted array. The leftover elements to the right will be equivalent to finding 2 sum problem.
 *	However, do take note that we cannot have duplicated answers (Eg: In [2,2,2,2,2], our solution is [[2,2,2,2]] only)
 *	For this, simply check if the current element is same as previous element when fixing n1, n2, n3 and n4. We MUST ensure
 *	that n1,n2,n3 and n4 doesn't occur twice or more.
 *
 *	The solution for this problem is O(N^3)
 *	=======================================================
 *
 *	Generally, we can see if we are required to find kth Sum, we simply fix k-2 values, and perform 2 sum on the remaining elements
 */

class Solution {
public:
	vector<vector<int>> fourSum(vector<int>& nums, int target) {
		const int len = nums.size();
		vector<vector<int>> res;

		sort(nums.begin(), nums.end());

		for (int i = 0; i < len - 3; ++i) {
			if (i != 0 && nums[i] == nums[i - 1]) continue;

			for (int j = i + 1; j < len - 2; ++j) {
				if (j != i + 1 && nums[j] == nums[j - 1]) continue;

				int l = j + 1, r = len - 1;

				while (l < r) {
					int sum = nums[i] + nums[j] + nums[l] + nums[r];
					if (sum < target || (l > j + 1 && nums[l] == nums[l - 1]))
						++l;
					else if (sum > target || (r < len - 1 && nums[r] == nums[r + 1]))
						--r;
					else {
						res.push_back({ nums[i], nums[j], nums[l++], nums[r--] });
					}
				}
			}
		}
		return res;
	}
};