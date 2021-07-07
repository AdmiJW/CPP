#include <vector>
#include <queue>
using namespace std;

//https://leetcode.com/problems/kth-smallest-element-in-a-sorted-matrix/
/*
 *  This is a Heap problem / Binary Search problem.
 *
 *  For heap problem, we need to realize some property in the matrix: At a given grid [i,j], it is guaranteed that the diagonal
 *  element [i+1, j+1] must be >= the element at [i,j]. However, we cannot guarantee that [i+1, j] is greater than or equal to
 *  [i, j+1] or vice versa, as seen in this example
 *  		1, 3
 *  		2, 3
 *
 *  Therefore, we know the smallest element is at (0,0), but which one can be the next smallest? We have two choices here: go
 *  right or go below. Therefore, if we can have a data structure that help sort this out for us, it would be nice, and that is
 *  heap!
 *
 *  Using idea of BFS, we can actually push the coordinates into the heap, and the heap will sort by the matrix element size.
 *  Once we had eliminated k-1 smallest elements from the heap, we know the next element will be the answer we are looking for.
 *
 *  Time is O(K log K), space O(N^2). Worst case is K=N^2, in this case O(N^2 log N^2), no better than brute force.
 *
 *  ===================================================
 *
 *  There is another way to approach this in heap: Remember merge sort's merging process? Given 2 arrays, we use two pointers
 *  to merge them into single one.
 *  Now, the problem is simply we have N sorted arrays. How do we merge them? Use heap!
 *
 *  ===================================================
 *
 *  For binary search, we perform binary search on the element range. We know smallest element is at index (0,0) and largest
 *  at index (n-1, n-1). We estimate a mid value from the range, and check how many elements is smaller than the estimate mid
 *  value.
 *
 *  Sounds easy. How does we count how many elements smaller? Start from the first row, and initialize the pointer to point
 *  at column N-1. If the element at column N-1 is greater than mid, decrease column, repeat until element at column N-1 is
 *  no longer > mid. Then, the elements in this row, from 0th column to the pointer is smaller than mid. Add that to the count.
 *  Repeat until all rows covered (We can use this approach because columns is also sorted).
 *
 *  Time taken is O(log(maxElem-minElem) * 2N). Space is O(1), much better
 */

class Solution {
public:

	// Breadth first search approach (PriorityQueue), O(K log K) time, worst case O(N^2 log N^2) - Still brute force
	int kthSmallest(vector<vector<int>>& matrix, int k) {
		const int l = matrix.size();

		vector<vector<bool>> visited(l, vector<bool>(l, 0));
		
		auto comp = [&matrix](pair<int, int>& l, pair<int, int>& r) {
			return matrix[l.first][l.second] > matrix[r.first][r.second];
		};
		priority_queue< pair<int, int>, vector<pair<int, int>>, decltype(comp) > pq(comp);

		pq.push({0, 0});

		while (!pq.empty()) {
			auto loc = pq.top(); pq.pop();
			int i = loc.first, j = loc.second;
			--k;

			if (k == 0) return matrix[i][j];

			// Add right side and below, if not visited before
			if (i + 1 < l && !visited[i + 1][j]) {
				visited[i + 1][j] = true;
				pq.push({i + 1, j});
			}
			if (j + 1 < l && !visited[i][j + 1]) {
				visited[i][j + 1] = true;
				pq.push({i, j + 1});
			}
		}
		return -1;
	}


	// Binary search approach - Approximate the mid
	// Binary search take O(maxElem - minElem), and within each iteration we take O(2N) time at max.
	int kthSmallest2(vector<vector<int>>& matrix, int k) {
		const int l = matrix.size();
		int left = matrix[0][0], right = matrix[l - 1][l - 1];

		while (left < right) {
			int mid = left + (right - left) / 2;
			int approxK = 0;
			int rightBound = l - 1;

			//Count how many elements are <= K in the matrix
			for (int r = 0; r < l; ++r) {
				while (rightBound >= 0 && matrix[r][rightBound] > mid)
					--rightBound;

				approxK += rightBound + 1;
			}

			if (approxK < k) left = mid + 1;
			else right = mid;
		}
		return left;
	}
};