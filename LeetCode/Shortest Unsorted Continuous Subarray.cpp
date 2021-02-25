#include <algorithm>
#include <vector>
using namespace std;

//https://leetcode.com/problems/shortest-unsorted-continuous-subarray/
/*
 * One quick way to solve, is to actually sort the entire array, and compare both the sorted and unsorted arrays.
 * The leftmost mismatch is the start of the unsorted subarray, and the rightmost mismatch is the end of unsorted
 * subarray
 *
 * ----------------------------------------------------------------------
 *
 * A sorted array is always increasing. Meaning, the next element is always larger than all the elements, including
 * the largest one, in the previously seen elements.
 *
 * Therefore, perform a linear scan. If the next element is larger than largest, then nevermind, the array is fine
 *
 * If it is however smaller than largest, it can be either of two cases:
 *
 * >	Smaller than the smallest element in unsorted subarray. That means like: 1,2, (5,4), -1
 * 		The (5,4) is unsorted segment, and smallest is 4. Since -1 is already smaller than 4, we have to extend the
 * 		starting point of the unsorted subarray until (1,2,5,4, -1)
 *
 * >	Larger than the smallest element in unsorted subarray. In this case simply extend the end point. No need to
 * 		extend starting point
 */

class Solution {
public:
	//	Pointless solution: Sort the whole array to find out subarray to sort
	int findUnsortedSubarray(vector<int>& nums) {
		vector<int> copy(nums);
		sort(copy.begin(), copy.end());

		int l = 0, r = nums.size() - 1;

		while (l < nums.size() && nums[l] == copy[l]) ++l;
		while (r > l && nums[r] == copy[r]) --r;

		return r - l == 0 ? 0 : r - l + 1;
	}

	//	One pass solution by recording min and max in unsorted array
	int findUnsortedSubarray2(vector<int>& nums) {
		const int len = nums.size();
		int start = INT32_MAX, end = 0;
		int largest = INT32_MIN, smallest = INT32_MAX;

		for (int i = 0; i < len; ++i) {
			if (nums[i] >= largest) {
				largest = nums[i];			//	If the next num is larger, this element shall no need to sorted
			}
			//	Next int is smaller, it can have two cases: larger than smaller in sorted, or smaller than sorted
			//	If it is smaller than any of those in sorted, we need to extend the start.
			else {
				end = i;

				if (nums[i] < smallest) {
					start = min(start, i - 1);
					smallest = min(smallest, nums[i]);

					while (start > 0 && nums[start - 1] > smallest) {
						smallest = min(smallest, nums[start - 1]);
						--start;
					}
				}
			}
		}

		return start == INT32_MAX ? 0 : end - start + 1;
	}
};