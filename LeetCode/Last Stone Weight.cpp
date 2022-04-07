#include <queue>
using namespace std;

//https://leetcode.com/problems/last-stone-weight/
/*
 * This is a Heap (Priority queue) problem.
 * Simply simulate the process of taking the 2 most heaviest stones from the existing stones and
 * crash them together. To obtain the 2 most heaviest stones, we use heap which retrieves them in O(log N) time.
 */


class Solution {
public:
    int lastStoneWeight(vector<int>& stones) {
        priority_queue<int> heap(stones.begin(), stones.end());

        while (heap.size() > 1) {
            int i = heap.top(); heap.pop();
            int j = heap.top(); heap.pop();
            if (i != j) heap.push(i - j);
        }

        return heap.size() == 0 ? 0 : heap.top();
    }
};