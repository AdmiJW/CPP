#include <queue>
#include <vector>
using namespace std;

//https://leetcode.com/problems/kth-largest-element-in-a-stream/
/*
 * 	To consistently obtain the kth largest element in an array where the elements are keep added, Heap data
 * 	structure is the best choice.
 *
 * 	Given that we need the kth largest element, we will maintain a min heap of maximum size k. If the heap already
 * 	contains exactly k elements, then the element that we peek will be the kth maximum element!
 */


class KthLargest {
public:
    const int limit;
    priority_queue<int, vector<int>, greater<int>> heap;

    KthLargest(int k, vector<int>& nums): limit(k)
    {
        for (int i : nums) add(i);
    }

    int add(int val) {
        heap.push(val);
        if (heap.size() > limit) heap.pop();
        return heap.top();
    }
};