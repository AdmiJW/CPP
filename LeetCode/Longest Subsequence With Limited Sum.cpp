#include <algorithm>
#include <vector>
using namespace std;

// https://leetcode.com/problems/longest-subsequence-with-limited-sum
/*
 *  This is a binary search, greedy sorting prefix sum problem.
 *
 *  Since we are asked to find the longest SUBSEQUENCE, it means we can basically take any elements from the array
 *  to form our desired subsequence, and if we want to include as many elements as possible, we should take the
 *  smaller elements first, thus be greedy.
 *
 *  So, the problem is reduced to: For each queries[i], how many elements can we take from the array, and how
 *  we would approach it is by always taking the smallest element first, and then the second smallest, and so on.
 *
 *  So, sort the nums array, then make it into prefix sum array. Then, for each queries[i], we can use binary search
 *  to find the index of the largest number that is less than or equal to the query.
 *
 *  The time complexity is O(N logN + M log N), where N is the length of nums, and M is the length of queries.
 *  The space complexity is O(N + M), since we need to store the prefix sum array and the answer array.
 */


class Solution {
public:
    vector<int> answerQueries(vector<int>& nums, vector<int>& queries) {
        const int n = nums.size();
        const int m = queries.size();

        // Sort the nums by its value
        sort(nums.begin(), nums.end());
        // Make it into prefix sum array
        for (int i = 1; i < n; i++)
            nums[i] += nums[i - 1];

        // Then, each query's answer is the index of the largest number that is less than or equal to the query
        vector<int> ans(m, 0);

        for (int i = 0; i < m; i++) {
            int x = queries[i];
            int l = 0, r = n;

            while (l < r) {
                int mid = l + (r - l) / 2;

                if (nums[mid] <= x) l = mid + 1;
                else r = mid;
            }

            ans[i] = l;
        }

        return ans;
    }
};