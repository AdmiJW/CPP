#include <algorithm>
#include <vector>
using namespace std;



// https://leetcode.com/problems/maximum-bags-with-full-capacity-of-rocks
/*
 * This is a greedy, sorting problem.
 *
 * From capacity[] and rocks[] array, derive an array of left[] which indicates the spaces left for rocks in each bag
 * Then sort the left[] array. The greedy idea is that if I have limited number of additional rocks, I should fill
 * in the bags with the least spaces left first, and then the second least, and so on.
 */

class Solution {
public:
    int maximumBags(vector<int>& capacity, vector<int>& rocks, int additionalRocks) {
        const int n = capacity.size();
        vector<int> left(n, 0);

        for (int i = 0; i < n; i++)
            left[i] = capacity[i] - rocks[i];

        sort(left.begin(), left.end());

        int res = 0;
        for (int i = 0; i < n; i++) {
            if (left[i] > additionalRocks) break;

            additionalRocks -= left[i];
            ++res;
        }

        return res;
    }
};