#include <vector>
#include <deque>

using namespace std;
//https://leetcode.com/problems/sliding-window-maximum/
/*
 * 	This is a Monotonic Deque Sliding Window problem / Heap problem / Dynamic Programming Problem
 *
 * 	The most common solution to come up with is by heap. We will push everything in the sliding window into the
 * 	heap, and as we slide the window, we remove the tail element and add the head element into the heap.
 *
 * 	As we all know, heap allows us to retrieve the maximum element in O(1) time, however heapify process due to
 * 	insertion takes O(log N) time. And even worse in Java, heap's delete operation will take O(N) time as it iterates
 * 	the whole array to find the element for deletion.
 *
 * 	-------------------------------------------------------------------------
 *
 * 	A Monotonic deque is a data structure that:
 * 		>	Allows access to both ends element
 * 		>	Either non-increasing or non-decreasing / Increasing or Decreasing only
 * 	which is very useful in determining the max and min number, as seen in Kth maximum/ Kth minimum number problems.
 * 	It can be applied here too!
 *
 * 	Basically when we try to push element, we push it at the back. And as long as the deque's end element is smaller, it means
 * 	that the smaller element is REDUNDANT (Meaning, if current updated element is already bigger, why bother the smaller ones?)
 * 	Therefore keep popping until finally it is bigger than current element, then push it in.
 *
 * 	When we try to find the maximum element, just peek the queue's front element. It represents the largest element.
 *
 * 	Then when we move the sliding window by 1 step, we check if queue's front element is the one that get popped. If it is,
 * 	then poll the front element, and proceed. The second element should be the 2nd largest element in sliding window now.
 *
 * 	This algorithm is good as it takes O(N) time and O(k) space.
 *
 * 	-----------------------------------------------------------------------------
 *
 * 	The Dynamic Programming solution is ingenious. First, we have to generate an array where each grid stores the maximum value
 * 	from left to right.
 *
 * 			Eg: [3,1,4,5,3]  => [3,3,4,5,5] (Strictly increasing)
 *
 * 	And the same with right to left.
 * 	However, the array need to be partitioned by the window size K. Once we hit the partition boundary, maximum is reset to minimum
 * 	and we start over. Assume K = 3, then
 *
 * 			Eg: [3,5,2,2,1]		=>	[3,5,5 | 2,2]		See that it reset after every 3 elements.
 *
 * 	Then in the end, in the result array, at index i (which the window covers i until i+k element), we just take the maximum
 * 	of the RtoL[i] and LtoR[i + k]
 *
 * 	Since the maximum is most possibly at right side of the LtoR array, we take the head of the sliding window (i+k)
 * 	Since the maximum is most possibly at left side of the RtoL array, we take the tail of the sliding window (i)
 *
 * 	The resetting is to ensure that the elements that are popped and possibly be the maximum element don't get counted into
 * 	the evaluation. The rest of maximum element should be covered by the array of other direction
 *
 * 			Eg: [3,1,2,0,4]
 *
 * 			LtoR: [3,3,3 | 0, 4]
 * 			RtoL: [3,2,2 | 4, 4]
 *
 * 			At i = 1 (Window [1,3]), The LtoR is taking index 3, which checks the maximum after the partition,
 * 									 while RtoL is taking index 1, which checks the maximum before partition, excluding the popped element
 *
 */

class Solution {
public:
	vector<int> maxSlidingWindow(vector<int>& nums, int k) {
		const int len = nums.size();
		const int resSize = len - k + 1;
		vector<int> res(resSize, 0);
		deque<int> deque(resSize);

		for (int i = 0; i < k; i++) {
			while (!deque.empty() && nums[i] > deque.back())
				deque.pop_back();
			deque.push_back(nums[i]);
		}
		res[0] = deque.front();

		for (int i = k; i < len; i++) {
			if (nums[i - k] == deque.front())
				deque.pop_front();
			while (!deque.empty() && nums[i] > deque.back())
				deque.pop_back();
			deque.push_back(nums[i]);
			
			res[i - k + 1] = deque.front();
		}
		return res;
	}


	vector<int> maxSlidingWindowDP(vector<int>nums, int k) {
		const int len = nums.size();
		const int resSize = len - k + 1;
		int* LtoRMax = new int[len];
		int* RtoLMax = new int[len];

		int max = INT32_MIN;

		for (int i = 0; i < len; i++) {
			if (!(i % k)) max = INT32_MIN;
			max = fmax(nums[i], max);
			LtoRMax[i] = max;
		}

		for (int i = len - 1; i >= 0; i--) {
			if (!(i % k)) max = INT32_MIN;
			max = fmax(nums[i], max);
			RtoLMax[i] = max;
		}

		vector<int> res(resSize, 0);
		for (int i = 0; i < resSize; i++) {
			res[i] = fmax(LtoRMax[i + k - 1], RtoLMax[i]);
		}
		delete[] LtoRMax;
		delete[] RtoLMax;
		return res;
	}
};