#include <vector>
#include <algorithm>
using namespace std;

//https://leetcode.com/problems/missing-number/
/*
 * 	This is a Sorting / Set / Math / Bit Manipulation problem.
 *
 * 	The brute force solution - For each integer from 0 to N, run a linear scan through the array to check if it exists,
 * 	take O(N^2) time, and is not efficient at all.
 *
 * 	------------------------------------------------------------------------------------------------------
 *
 * 	Instead, observe when the array is sorted, ideally it will become 1,2,3,4,5.... Now if one number is skipped, it become
 * 	dead obvious and can be detected easily. This algorithm takes O(N log N) time.
 *
 * 	We can optimize a bit by using binary search after sorting. Since one number is missing, during binary search if the
 * 	middle element selected is perfectly matching the index, it means all element to the left is correct. So put left = mid + 1.
 * 	Otherwise, the missing element must be current element or at the left side, so put right = mid
 * 	However, time complexity remains the same.
 *
 * 	-------------------------------------------------------------------------------------------------------
 *
 * 	On the other hand, we can use extra space to keep a Set (or boolean array, since index 0 to N only is required), which
 * 	records which element is exist. At the end, run a linear scan again to identify the missing element.
 *
 * 	-------------------------------------------------------------------------------------------------------
 *
 * 	All elements are from 0 to N only. Notice how they can be mapped back into the index of the array itself. Also, elements
 * 	are all positive. Therefore, for visited elements, we mark the number at the respective index to become negative. At the
 * 	end, run a linear scan again to check if any element is positive - meaning not visited. If found, the index is the missing
 * 	integer.
 *
 * 	There are edge cases:
 * 		>	Element 0 cannot be made negative. However, using process of elimination - If all numbers are negative, then
 * 			the index where element is 0 must be missing!
 * 		>	Indexing only until N-1. We can use one single extra variable to record whether Number N is visited.
 *
 * 	------------------------------------------------------------------------------------------------------
 *
 * 	In a perfect array, the sum will be 1+2+3+...+N. This can easily calculated using formula:
 *
 * 		(N*(N+1))/2    <<- Using Gauss formula
 *
 * 	Now, run a linear scan and minus each element from it. The missing number will not be removed, thus at the end of linear
 * 	scan, it will remain, and can be returned.
 *
 * 	------------------------------------------------------------------------------------------------------
 *
 * 	XOR of 2 same numbers will result in 0. Use this fact:
 *
 * 	If we run a linear scan, all numbers ideally will appear twice: As index, and as element, except Number N, since indexing
 * 	only until N-1.
 *
 * 	Start out with N, keep XORing the element and the index as we traverse. if a number is missing, indeed at the end what
 * 	remains as result of XOR will be the answer
 */

class Solution {
public:

	//	Sort & linear scan solution
	int missingNumber(vector<int>& nums) {
		sort(nums.begin(), nums.end());
		for (int i = 0; i < nums.size(); ++i)
			if (i != nums[i]) return i;
		return nums.size();
	}


	//	Sort & binary Search Solution 
	int missingNumber2(vector<int>& nums) {
		sort(nums.begin(), nums.end());
		int l = 0, r = nums.size();
		while (l < r) {
			int m = l + (r - l) / 2;
			if (nums[m] == m) l = m + 1;
			else r = m;
		}
		return l;
	}


	//	Using array of boolean
	int missingNumber3(vector<int>& nums) {
		vector<bool> exist(nums.size() + 1);
		for (int i : nums) exist[i] = true;

		for (int i = 0; i < exist.size(); ++i)
			if (!exist[i]) return i;
		return -1;
	}


	//	In place marking solution
	int missingNumber4(vector<int>& nums) {
		const int len = nums.size();
		bool last = false;

		for (int i = 0; i < len; ++i) {
			int idx = abs(nums[i]);

			if (idx == len) last = true;
			else nums[idx] *= -1;
		}

		if (!last) return len;
		int zero = -1;
		for (int i = 0; i < len; ++i) {
			if (nums[i] > 0) return i;
			if (!nums[i]) zero = i;
		}
		return zero;
	}



	//	Mathematics Arithmetic Sum Formula / Gauss Formula
	int missingNumber5(vector<int>& nums) {
		const int len = nums.size();
		int supposed = (len * (len + 1)) / 2;
		
		for (int i : nums) supposed -= i;
		return supposed;
	}


	//	XOR solution - Using fact that supposedly all number and index appear twice, except the last index which doesn't appear
	int missingNumber6(vector<int>& nums) {
		const int len = nums.size();
		int res = len;
		for (int i = 0; i < len; ++i)
			res ^= (i ^ nums[i]);
		return res;
	}

};