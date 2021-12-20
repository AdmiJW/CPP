#include <vector>
#include <algorithm>
using namespace std;

//https://leetcode.com/problems/minimum-absolute-difference/
/*
 *  This is a Sorting Array problem.
 *
 *  If the array is already sorted, then the neighboring elements will yield the local minimum absolute difference.
 *
 *  That is, if we have elements in the sorted array [a,b,c,d,e...], for the element c, the minimum absolute difference
 *  it can produce with one other element, is either abs(b-c) or abs(d-c), which is both its neighbors.
 *
 *  Therefore, sort the array, and compare each adjacent elements for their absolute difference, and take only those who
 *  are globally minimum absolute difference
 */


class Solution {
public:

    vector<vector<int>> minimumAbsDifference(vector<int>& arr) {
        sort(arr.begin(), arr.end());

        // First pass - Determine minimum absolute difference (To correctly allocate capacity)
        int minAbs = INT32_MAX;
        int count = 0;

        for (int i = 1; i < arr.size(); ++i) {
            int diff = abs(arr[i] - arr[i - 1]);
            // Update abs and reset counter
            if (diff < minAbs) {
                minAbs = diff;
                count = 0;
            }

            if (diff == minAbs) ++count;
        }

        vector<vector<int>> res;
        res.reserve(count);

        // Second pass - Populate the result array
        for (int i = 1; i < arr.size(); ++i) {
            int diff = abs(arr[i] - arr[i - 1]);

            if (diff == minAbs)
                res.push_back({ arr[i - 1], arr[i] });
        }

        return res;
    }

};