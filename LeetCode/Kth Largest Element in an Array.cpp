#include <vector>
#include <algorithm>
#include <queue>
using namespace std;


//https://leetcode.com/problems/kth-largest-element-in-an-array/
/*
 * 	This is a Heap problem / Quick Partition (Divide and Conquer) problem
 *
 * 	The easiest solution is just sort it and return the element at that position. O(N log N)
 *
 * 	------------------------------------------------------------
 *
 * 	We can also use the priority queue method which is a heap. Since it asks for the maximum kth element, what we
 * 	mostly don't want is small elements, therefore we would use a MIN HEAP, to allow us to discard any minimum elements
 * 	immediately once the heap exceed the size of K.
 *
 * 	The remaining elements in the heap will consists of first K maximum elements. When we are done iteration, the top of the
 * 	heap is immediately our answer.
 *
 * 	Heap's insertion and heapify is O(log K) therefore taking overall time complexity O(N log K) and space O(K)
 *
 * 	--------------------------------------------------------------
 *
 * 	One ingenious solution is to using the partition algorithm in quick sort method. The partition algorithm allows us to
 * 	find out the position of one single pivot element as if it is in a sorted array.
 *
 * 	Since we are finding the Kth maximum element, if it is found that the index of pivot is exactly match, immediately return
 * 	the pivot as we had found the answer
 *
 * 	If it is not, it's nevermind as we can immediately narrow down the range. Since hopefully the pivot element is exactly in
 * 	middle of the array, then we can cut half the range that we are searching.
 *
 * 	Let I be the index of pivot. If the supposed index is greater than I, then just recurse on the right side of the array.
 * 	Otherwise, just recurse on the left side.
 *
 * 	On worst case where pivot element is always at end, it should be O(N^2) time. Otherwise it can go to O(N) time in best case with
 * 	proven (Find online)
 */


class Solution {
public:

	//	Simple Sort solution - Won't let you pass an interview
	int findKthLargest(vector<int>& nums, int k) {
		sort(nums.begin(), nums.end());

		return nums[nums.size() - k];
	}


	//	K-Sized Heap method.	
	//	A Comparator class is required with the () operator overloaded to compare 2 values. This is needed in the template
	//	when initializing the priority queue
	class MinComparator {
	public:
		bool operator() (const int& n1, const int& n2) {
			return n1 > n2;
		}
	};
	int findKthLargest2(vector<int>& nums, int k) {
		auto comp = []( int x, int y) -> bool { return x > y; };
		
		priority_queue<int, vector<int>, MinComparator> pq;

		for (int i : nums) {
			pq.push(i);

			if (pq.size() > k) pq.pop();
		}

		return pq.top();
	}



	//	Ingenious Quicksort Partitioning Method
	int findKthLargest3(vector<int>& nums, int k) {
		const int len = nums.size();
		//	Remember: The to represents our pivot since our partitioning function takes the last element in range
		int from = 0, to = len - 1;

		while (from < to) {
			int rank = partition(nums, from, to);

			if (len - rank == k) return nums[rank];
			else if (len - rank > k)
				from = rank + 1;
			else
				to = rank - 1;
		}
		return nums[from];
	}
	int partition(vector<int>& arr, int from, int to) {
		if (from == to) return from;

		int slow = from, fast = from;
		int pivot = arr[to];

		while (fast < to) {
			if (arr[fast] < pivot) {
				int temp = arr[slow];
				arr[slow] = arr[fast];
				arr[fast] = temp;
				++slow;
			}
			++fast;
		}

		int temp = arr[to];
		arr[to] = arr[slow];
		arr[slow] = temp;

		return slow;
	}
};