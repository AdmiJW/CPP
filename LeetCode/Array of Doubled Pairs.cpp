#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

//https://leetcode.com/problems/array-of-doubled-pairs/
/*
 * This is a Sorting, Greedy and HashMap problem.
 *
 * Every n must have n*2 somewhere in the array. The position in the array does not matter here.
 *
 * Therefore, we could use a HashMap that maps certain value to its frequency in the array. That provides O(1) lookup time
 * However, consider the case [4,8,2,16]
 * We could make the solution as [2,4,8,16]. However, if no preprocessing is done, 4 and 8 would be paired, and 2, 16 couldn't
 * possibly form a pair!
 *
 * The solution for this is to sort the array beforehand. This ensures that we process the smaller element first.
 *
 * For every element e in sorted array:
 * 		>	If e is negative, check if e*2 existed in the HashMap (Due to sorting, we see larger magnitude negative first)
 * 		>	If e is positive, check if e is divisible by 2 and e/2 existed in HashMap (Due to sorting, we see smaller magnitude positives first)
 * 		>	Otherwise, this element is not paired yet. Add 1 to its frequnecy in HashMap
 *
 * At the end, check if there is still leftover value that isnt paired yet.
 *
 * -------------------------
 *
 * We could do this in O(1) space without HashMap, albeit this will modify the array.
 * We will mark the paired elements with a absurd value like Integer.MAX_VALUE
 *
 * First, sort the array
 *
 * Initialize two pointers at index 0.
 * 	>	If left pointer's value is Integer.MAX_VALUE, move left pointer forward
 * 	>	If right pointer's value is Integer.MAX_VALUE, move right pointer forward
 * 	>	Otherwise, check if left pointer and right pointer can form a pair or not
 * 		- Yes, then mark them as paired with Integer.MAX_VALUE, and move both pointers
 * 		- No, then move only right pointer.
 *
 *  At the end, all values should be Integer.MAX_VALUE. If not, return false
 */

class Solution {
public:
	bool canReorderDoubled(vector<int>& arr) {
		unordered_map<int, int> nums;
		int numsLeft = 0;

		// Sort to ensure we process in order
		sort(arr.begin(), arr.end());

		for (int i : arr) {
			// First, check if there exists ix2 or i/2 already in the map
			if (i <= 0 && nums[i * 2] > 0) {
				--nums[i * 2];
				--numsLeft;
			}
			else if (i > 0 && i % 2 == 0 && nums[i / 2] > 0) {
				--nums[i / 2];
				--numsLeft;
			}
			else {
				++nums[i];
				++numsLeft;
			}
		}
		return numsLeft == 0;
	}

	bool canReorderDoubled2(vector<int>& arr) {
		// Sort to ensure we process in order
		const int len = arr.size();
		sort(arr.begin(), arr.end());
		int l = 0, r = 0;

		while (l < len && r < len) {
			if (arr[l] == INT32_MAX) ++l;
			else if (arr[r] == INT32_MAX) ++r;
			else {
				if (arr[l] == arr[r] * 2 || arr[r] == arr[l] * 2)
					arr[l++] = arr[r++] = INT32_MAX;
				else
					++r;
			}
		}

		for (int i = 0; i < len; ++i)
			if (arr[i] != INT32_MAX) return false;
		return true;
	}
};