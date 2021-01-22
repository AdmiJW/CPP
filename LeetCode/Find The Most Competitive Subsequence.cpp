#include <vector>
#include <queue>
using namespace std;

//https://leetcode.com/problems/find-the-most-competitive-subsequence/
/*
 * 	This is a Greedy + Stack problem. Although solution based on Heap is possible
 *
 *  Using a Monotonic Stack, we can store the elements we encountered. For every element, if the element is
 *  small, we would want to make it as front as possible in subsequence!
 *
 *  So, check the top of the Stack. If top of stack is larger, and the elements remaining in the list is still
 *  enough to fill up the k array, then why not?
 *  Pop all elements greater than current element while elements remaining still allow, and that's the intuition!
 *
 *  ---------------------------------------------------------
 *
 *  For priority Queue, we would want a heap having only minimum elements of size k. Remember that elements left
 *  in the array matters too so we don't overpop the elements.
 *
 *  At last, since it is subsequence, the values has to be sorted by index. Only then it wll return the array
 *  in	correct order
 */

class Solution {
public:

	//	Brute force solution.
	//	Easily Time Limit Exceeded
	vector<int> mostCompetitive(vector<int>& nums, int k) {
		const int len = nums.size();
		vector<int> res(k, 0);
		int pt = 0; 
		int startingP = 0;

		for (int i = 0; i < k; ++i) {
			startingP = findMinInRange(nums, startingP, len - k + i);
			res[pt++] = nums[startingP];
			++startingP;
		}

		return res;
	}
	int findMinInRange(vector<int>& nums, int start, int end) {
		int minIdx = start;

		for (int i = start; i <= end; ++i)
			if (nums[i] < nums[minIdx]) minIdx = i;

		return minIdx;
	}



	//	Heap Solution - Keep a Heap of size K. At the end sort them by index and return
	class comparator1 {
	public:
		bool operator() (const pair<int, int>& l, const pair<int, int>& r) {
			return (l.first < r.first);
		}
	};
	vector<int> mostCompetitive(vector<int>& nums, int k) {
		const int len = nums.size();
		priority_queue< pair<int, int>, vector<pair<int, int>>, comparator1 > heap;

		for (int i = 0; i < len; ++i) {
			int n = nums[i];

			while (!heap.empty() && heap.top().first > n && k - heap.size() + 1 <= len - i)
				heap.pop();

			if (heap.size() < k) heap.emplace(make_pair<>(n, i));
		}

		vector< pair<int, int>> li(k);
		for (int i = 0; i < k; ++i) {
			li[i] = heap.top();
			heap.pop();
		}
		sort(li.begin(), li.end(), [](auto x, auto y)-> bool {
			return x.second < y.second;
			});
		vector<int> res(k);
		for (int i = 0; i < k; ++i) res[i] = li[i].first;

		return res;
	}


	//	Stack based solution - Implementation using array and pointer
	vector<int> mostCompetitive3(vector<int>& nums, int k) {
		const int len = nums.size();
		vector<int> res(k);
		int pt = 0;

		for (int i = 0; i < len; ++i) {
			int n = nums[i];

			//	While there still elements in Stack, the top element is greater, and
			//	The element required to fill res array after popping is less than or equal to elements
			//	left in array
			while (pt > 0 && res[pt - 1] > n && k - pt + 1 <= len - i)
				--pt;

			//	If after popping there is available space, push to Stack
			if (pt < k) res[pt++] = n;
		}

		return res;
	}
};