#include <vector>
#include <queue>
using namespace std;


//https://leetcode.com/problems/find-median-from-data-stream/
/*
 * This is a Hard (but once you realize, it is easier hard) Heap problem.
 *
 * To design a MedianFinder where I can keep adding numbers and retrieve median of the sorted list of numbers,
 * think how we can approach it?
 *
 * Median is essentially the middle value of sorted numbers. Say we have already an array of sorted numbers and median
 * value already pinned down. Now I will add a number into the list. What will happen (Ignoring the even length case where
 * we take the mean of 2 middle values)
 * What we may think is the median value may get shifted, either:
 * 	>	If insert number is smaller, the number go to left side of list. Median value would shift to left as well.
 * 	>	If insert number is larger, the number go to right side of list. Median value would shift to right as well.
 *
 * Intuitively, now we have the feeling that adding a number would shift the median by one value only. Then, how do we have
 * access to those value quickly?
 *
 * The solution is to have 2 Heap, representing each half of the sorted array. See:
 *
 * 	[    Left     ] X [    Larger     ]
 *
 * For the left heap, we want to be able to retrieve the largest element quickly, thus a max heap. Similarly, the right heap
 * we want to be able to retrieve the smallest element quickly, thus a min heap.
 *
 * When we add a number, we add it to one of the suitable heaps. However, to keep our position to be middle, we will balance
 * the heap by moving one elements from the heap with more elements to the another heap with lesser element. Then, the peek
 * value for both heaps will be perfectly middle!
 */

class MedianFinder {
public:
	// Left PQ must be able to retrieve the largest element quickly. Similarly, right PQ must be able to
	// retrieve the smallest element quickly
	priority_queue<int> leftPQ;
	priority_queue<int, vector<int>, greater<int>> rightPQ;

	MedianFinder() {}

	void addNum(int num) {
		if (!rightPQ.empty() && num > rightPQ.top()) {
			leftPQ.push(rightPQ.top());
			rightPQ.pop();
			rightPQ.push(num);
		}
		else
			leftPQ.push(num);

		// Balancing
		if (leftPQ.size() == rightPQ.size() + 2) {
			rightPQ.push(leftPQ.top());
			leftPQ.pop();
		}
	}

	double findMedian() {
		// Case 1: Odd sizes: 1/3/5... Since our PQ is bias to left, the leftPQ has the answer
		if (leftPQ.size() > rightPQ.size())
			return leftPQ.top();
		return (leftPQ.top() + rightPQ.top()) / 2.0;
	}
};