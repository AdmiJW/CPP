#include <vector>
using namespace std;

//https://leetcode.com/problems/count-of-smaller-numbers-after-self/
/*
 *  This turns out to be a Merge sort / BST problem
 * 	However, only merge sort solution is discussed here as it is guaranteed O(N log N) time.
 *
 * 	Merge sort, uses divide and conquer strategy with recursion to sort an array. For given range in an array [l,r],
 * 	it splits the range into two to sort. Once returned, it will use two pointers to finally MERGE the two separate
 * 	sorted array into one.
 *
 *  Notice here, during splitting, original order of the array is not yet lost:
 *  		[1,2,3,4,5,6,7]
 *  	[1,2,3,4]   [5,6,7]
 *   [1,2] [3,4]	[5,6]  [7]
 *  [1] [2] [3] [4] [5] [6]
 *
 *  In all the levels, the right subarray elements must be to the right of all left subarray elements in the original unsorted
 *  array. Does that ring a bell?
 *
 *  Let's start from bottom. Once the subarray of size 1 (base case) is returned, we will combine two subarrays.
 *  Let's say left side is [5], and right size is [1].
 *  We'll notice that right side's [1] has to be go to the left of [5]! This means in original unsorted array, 5 comes before
 *  1, which means a smaller number after 5!
 *
 *  Therefore, the idea is to count the number of elements in right subarray that has to go before elements in left subarray.
 *  When left element is selected, I have to account for how many right subarray elements had been choosen before this left
 *  subarray element is chosen (How many smaller numbers are to the right of the element).
 *
 *  This means I have to track the original indices of each element as well, because I need to update the result array as well.
 *  This can be done by having a pair of {val, idx}
 */

class Solution {
public:
	vector<int> countSmaller(vector<int>& nums) {
		const int len = nums.size();
		vector<int> res(len, 0);

		//	Create the array of [val, idx] for sorting
		vector<pair<int, int>> indexedNums(len);
		for (int i = 0; i < len; ++i)
			indexedNums[i] = make_pair<>(nums[i], i);

		//	Merge sort the indices while filling count in the process
		mergeSort(indexedNums, 0, len - 1, res);

		return res;
	}


	void mergeSort(vector<pair<int, int>>& indexedNums, int left, int right, vector<int>& res) {
		if (left == right) return;

		int mid = left + (right - left) / 2;
		mergeSort(indexedNums, left, mid, res);
		mergeSort(indexedNums, mid + 1, right, res);

		vector<pair<int, int>> temp;
		int countRight = 0;
		int l = left, r = mid + 1;

		while (l <= mid || r <= right) {
			//	Have to take the left element
			if (l <= mid && (r > right || indexedNums[l].first <= indexedNums[r].first)) {
				temp.push_back(indexedNums[l]);
				res[indexedNums[l].second] = res[indexedNums[l].second] + countRight;
				++l;
			}
			//	Add the right element. We have to track number of right section elements coming to left side
			else {
				temp.push_back(indexedNums[r]);
				++countRight;
				++r;
			}
		}

		int p = left;
		for (auto t : temp)
			indexedNums[p++] = t;
	}

};