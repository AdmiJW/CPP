#include <vector>
using namespace std;

//https://leetcode.com/problems/next-permutation/
/*
 * 	If only this question show up earlier prior to me learning this algorithm.
 *
 * 	---------------------------------------------------------------------------
 *
 * 	As said before, we can generate the next lexicographically permutation without having to utilize
 * 	backtracking, in O(N) time. To generate every permutation would still become O(N!N)
 *
 * 	We start our work from behind. To find out the next lexicophaphically permutation, the first number
 * 	to disrupt the ascending order must be swapped. See:
 *
 * 	14765. As you can see, 765 is descending, swapping any of them makes a smaller permutation so we don't
 * 	touch them. However, the 4 in 4765 must be swapped with any of them in 765 so it makes a overall bigger
 * 	number!
 * 	Pivot at 4, then find the next SMALLEST number among 765 to be swapped with 4. In this case is 5.
 *
 * 	Now it becomes 15764. Wait because the 764 is not smallest next permutation yet. It shall be 15467. Therefore,
 * 	reverse the part after the pivot part entirely to make it smallest. There you go! A Next permutation algorithm
 *
 * 	In case pivot can't be found, it means that the sequence is already largest. To make it back into smallest,
 * 	reverse entirely sequence.
 */

class Solution {
public:
	void nextPermutation(vector<int>& nums) {
		const int len = nums.size();
		int pivot = -1;

		//	Find the pivot point. The one element that needs to be swap
		for (int i = len - 2; i >= 0; --i) {
			if (nums[i] < nums[i + 1]) {
				pivot = i;
				break;
			}
		}

		//	The ordering is already maximum. Reverse entirely to get back minimum
		if (pivot == -1) {
			reverse(nums, 0, len - 1);
			return;
		}

		//	Find the second element to swap. After that reverse everything after the pivot
		for (int i = len - 1; i > pivot; --i) {
			if (nums[i] > nums[pivot]) {
				swap(nums, pivot, i);
				reverse(nums, pivot + 1, len - 1);
				return;
			}
		}

	}


	void swap(vector<int>& nums, int x, int y) {
		int temp = nums[x];
		nums[x] = nums[y];
		nums[y] = temp;
	}

	void reverse(vector<int>& nums, int from, int to) {
		while (from < to)
			swap(nums, from++, to--);
	}
};