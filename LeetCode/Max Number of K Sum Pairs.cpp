#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

//https://leetcode.com/problems/max-number-of-k-sum-pairs/
/*
 * 	This is a HashMap / Two pointers Sorting Problem
 *
 * 	Each number n, we will raise a question. Is there a existing number i in the array such that
 * 			n + i = k
 *
 * 	Therefore, we can set up a HashTable like a "Wanted Number Counter" which keeps track of the searched
 * 	number by previously visited numbers.
 *
 * 	So, each number,
 * 		if the number is being searched by HashTable, res += 1. And remove the search frequency of the number
 * 		by 1
 *
 * 		Else, we want to search for k-n. Update in HashTable
 *
 * 	---------------------------------------------------------------------
 *
 * 	We can also solve it in sorted array.
 *
 * 	Start two pointers from both ends of array. It shall be pointing at max and min element of array.
 *
 * 	Now, add the two elements pointed up. Say x+y. Check:
 * 		if x+y == k, we found a pair. Update in result variable, and move both pointers
 * 		if x+y < k, the smallest element is too small even if paired with large element. Move left pointer
 * 		if x+y > k, the largest element is too large even if paired with smallest element. Move right pointer
 */

class Solution {
public:

	//	HashMap solution - "WANTED Table"
	int maxOperations(vector<int>& nums, int k) {
		int res = 0;
		unordered_map<int, int> finding;

		for (int i : nums) {
			if (finding.count(i) && finding[i] > 0) {
				++res;
				finding[i] -= 1;
			}
			else {
				finding[k - i] = finding.count(k - i) ? finding[k - i] + 1 : 1;
			}
		}

		return res;
	}


	int maxOperations2(vector<int>& nums, int k) {
		int res = 0;
		sort(nums.begin(), nums.end());

		int left = 0, right = nums.size() - 1;

		while (left < right) {
			//	Case 1 - Match!
			if (nums[left] + nums[right] == k) {
				++res;
				++left;
				--right;
			}
			//	Case 2 - x+y < k. The small one is too small. Need increase!
			else if (nums[left] + nums[right] < k)
				++left;
			//	Case 3 - x+y > k. The big is too big even paired with smallest int. Need decrease
			else
				--right;
		}

		return res;
	}
};