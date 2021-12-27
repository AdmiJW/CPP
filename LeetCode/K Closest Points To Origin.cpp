#include <vector>
#include <queue>
#include <cmath>
using namespace std;

//https://leetcode.com/problems/k-closest-points-to-origin/
/*
 * 	This is a sorting problem, with variations of heap / binary search / heap
 *
 *
 * 	The sorting is straightforward - Sort the array based on distance to origin, and select the front K points
 * 	as the answer. Time is O(N log N)
 *
 * 	However, if K is small, we could optimize by maintaining only a K sized heap. The heap will also keep data
 * 	in sorted order, but since K is small, each insert, removal of elements in heap is log K. Therefore final
 * 	time complexity is O(N log K)
 */


struct compare {
public:
    bool operator()(const vector<int>& l, const vector<int>& r) {
        return distance(l) > distance(r);
    }

    double distance(const vector<int>& point) {
        return sqrt(point[0] * point[0] + point[1] * point[1]);
    }
};


class Solution {
public:
    // Heap solution - O(N + K log K)
    vector<vector<int>> kClosest(vector<vector<int>>& points, int k) {
        priority_queue<vector<int>, vector<vector<int>>, compare> pq;

        // Maintain a heap of size K
        for (auto& p : points) {
            pq.push(p);

            if (pq.size() > k) pq.pop();
        }

        // Result
        vector<vector<int>> ans;
        for (int i = 0; i < k; ++i) {
            ans.push_back(pq.top());
            pq.pop();
        }
        return ans;
    }

};