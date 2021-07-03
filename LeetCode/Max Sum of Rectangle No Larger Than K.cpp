#include <vector>
#include <set>
using namespace std;

//https://leetcode.com/problems/max-sum-of-rectangle-no-larger-than-k/
/*
 * This is a Matrix, Binary Tree (TreeSet), Dynamic Programming (Kadane's Algorithm) problem.
 * The problem is HARD, should not expect to be able to solve it without even any hints
 *
 * First of all, consider brute force approach. We need to either:
 * 	>	Select all left upper corner and lower right corner, and find sum. O(n^2 * m^2) if uses prefix sum method. Otherwise
 * 		time complexity is worse
 * 	>	Instead of above, you can also consider select all left upper corner, then all possible width and height. Same time
 * 		complexity.
 *
 * 	We need a method to lower the time complexity. Let's see how:
 * 	>	We can afford to consider all rectangles of different widths. Thus we can attempt rectangles with width from coordinates
 * 		(0,0), (0,1), (0,2)...(1,1), (1,2)... (N,N), taking time O(N^2) at first
 *
 * 	>	Within each of this width rectangles, we want a better approach to find out what height gives the best sum within k.
 * 		What we could do is, perform prefix sum across that width rectangle.
 *
 * 		Say our matrix is sized 5 row x 3 column. Then, During iteration covering columns (0,2), we should have a prefix sum
 * 		array of size 5 representing prefix sum for each rows.
 * 		Say this array is called prefixSumArr. prefixSumArr[1] should have row 2's prefix sum from 0 to 2.
 *
 * 	>	If the problem simply wants the maximum value, we could run Kadane's algorithm, a simple Dynamic Programming algorithm
 * 		to find out maximum sum subarray from 1D array. However, since this problem restrict that our sum must be <= k, we cannot
 * 		directly apply.
 *
 * 		Instead, we kind of apply the same idea to iterate thru the prefix sum array, summing for the "prefix sum of prefix sum"
 * 		The prefix sum of prefix sum will contain the sum of elements within the area. However, we may want to remove some subarray
 * 		to obtain the maximum sum.
 *
 * 		So, we store the prefix sum of prefix sum in each iteration in a sorted container structure -- Binary Search Tree. We are able
 * 		to search for the one subarray which when subtracted from current prefix sum of prefix sum, gives maximum value <= k.
 *
 *
 * 	Leetcode contains the best explaination, and I highly recommend you to read it instead.
 */

class Solution {
public:
	int maxSumSubmatrix(vector<vector<int>>& matrix, int k) {
		const int r = matrix.size(), c = matrix[0].size();
		int res = INT32_MIN;

		//Selects the left bound
		for (int left = 0; left < c; ++left) {
			vector<int> arr(r, 0);

			//Selects the right bound
			for (int right = left; right < c; ++right) {
				//Sum across the column elements
				for (int i = 0; i < r; ++i) arr[i] += matrix[i][right];

				int localRes = bestSumRestricted(arr, k);
				res = max(res, localRes);
			}
		}
		return res;
	}

	
	int bestSumRestricted(vector<int>& arr, int k) {
		set<int> set;
		set.insert(0);

		int res = INT32_MIN;
		int prefixSum = 0;

		for (int i : arr) {
			prefixSum += i;
			auto binSearch = set.lower_bound(prefixSum - k);
		
			if (binSearch != set.end())
				res = max(res, prefixSum - *binSearch);
			set.insert(prefixSum);
		}
		return res;
	}
};