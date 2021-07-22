#include <vector>
#include <queue>
using namespace std;

//https://leetcode.com/problems/partition-array-into-disjoint-intervals/
/*
 * This is an array problem.
 *
 * The core concept of the problem is we have to partition the array such that:
 * 		The maximum element in left partition <= The minimum element in the right partition.
 *
 * To come up with a solution that isn't brute force, we must have a way to obtain the max/min of either side in better time
 * complexity than to linear scan it.
 *
 * One way is to use heap. The heap represents all the elements in the right partition. Then, we run a linear iteration
 * from left to right, recording maximum element in the left partition, while checking the heap for the minimum element in
 * right partition.
 *
 * However, the better solution is to preprocess the array such that at any index i, we already know the minimum element
 * from [i+1, n].
 *
 *
 * Finally, the optimal solution will simply iterate through the array once. For each element, if the current element
 * is less than the max element in left partition, that means the left partition MUST be extended until current element.
 */

class Solution {
public:
	// Heap solution, O(N log N) time and O(N) space
	int partitionDisjoint(vector<int>& nums) {
		const int len = nums.size();

		// Heap stores entries in [value, index]
		auto comp = [](pair<int, int>& a, pair<int, int>& b) { return a.first > b.first; };
		priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(comp)> pq(comp);
	
		// Initialization - fill all elements into the pq
		for (int i = 0; i < len; ++i)
			pq.push({nums[i], i});

		int leftMax = INT32_MIN;
		for (int i = 0; i < len; ++i) {
			// Update left partition maximum value
			leftMax = max(leftMax, nums[i]);
			// While whatever remains in the top of heap is out of index, remove
			while (!pq.empty() && pq.top().second <= i)
				pq.pop();

			// If the maximum value in left partition is lower or equal to the minimum value in right partition, return
			if (leftMax <= pq.top().first)
				return i + 1;
		}
		return -1;
	}


	// Array solution - O(N) time and space
	int partitionDisjoint2(vector<int>& nums) {
		const int len = nums.size();
		vector<int> minRight(len, 0);		// minRight[i] means min elem from [i+1, n-1]

		// Fill maxRight[]
		for (int i = len - 1, temp = INT32_MAX; i >= 0; --i) {
			minRight[i] = temp;
			temp = min(temp, nums[i]);
		}

		// From left side, record max value while checking minRight[]
		for (int i = 0, temp = INT32_MIN; i < len; ++i) {
			temp = max(nums[i], temp);
			if (temp <= minRight[i]) return i + 1;
		}
		return -1;
	}



	// One pass solution O(1) space
	int partitionDisjoint3(vector<int>& nums) {
		const int len = nums.size();
		int disjoint = 0;
		int leftMax = nums[0], currentMax = nums[0];

		for (int i = 0; i < len; ++i) {
			currentMax = max(nums[i], currentMax);
			// Discovered a smaller element than the maximum element in left partition
			if (leftMax > nums[i]) {
				disjoint = i;				// The left partition must cover until this index
				leftMax = currentMax;		// Since the left partition is dragged until here, its maximum becomes whatever maximum we seen
			}
		}
		return disjoint + 1;
	}
};