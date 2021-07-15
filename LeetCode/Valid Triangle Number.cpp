#include <vector>
#include <algorithm>
using namespace std;

//https://leetcode.com/problems/valid-triangle-number/
/*
 *	This is a two pointer, greedy, sorting problem.
 * 	(I kinda failed to come up with a plausible solution except for brute force one)
 *
 *	For brute force is straightforward. Consider all possible i, j and k and check for the three conditions for triangle.
 *	That is, for {i,j,k},
 *		i + j > k
 *		i + k > j
 *		j + k > i
 *	Time complexity for this one is O(N^3). Even for input size of 1000 can be quite time consuming.
 *
 *	========================================================
 *
 *	The best solution does it in O(N^2) time, similar to how the problem (THREE SUM) does it.
 *
 *	First of all, if the array is sorted, let's see one particularly interesting property:
 *	For indices i, j and k, where i < j < k, then surely in sorted array:
 *		nums[i] <= nums[j] <= nums[k]
 *	What this enables us, is that we only need to check one condition for triangle only! Since k is the largest element,
 *		i + k must > j
 *		j + k must > i
 *	Then we only need to check whether i + j > k
 *
 *	We essentially will first fix our i value, from left to right. Then, we will have two pointers j and k.
 *	Pointer j is our second side length, which starts from i+1 to the end, left to right. However, because the elements
 *	increase from left to right, as j increases, we no need to start k from j+1 because nums[j] had increased, increasing
 *	the likelyhood of i+j > k!
 *	Once i and j are fixed, iterate the k pointer as long as i + j > k. Then, the elements between j and k will be the possible
 *	values of k. Add that to the result
 */

class Solution {
public:
    int triangleNumber(vector<int>& nums) {
        const int len = nums.size();
        int res = 0;

        sort(nums.begin(), nums.end());

        for (int i = 0; i < len; ++i) {
            int k = i + 2;
            for (int j = i + 1; j < len - 1 && nums[i] != 0; ++j) {
                while (k < len && nums[i] + nums[j] > nums[k])
                    ++k;
                res += k - j - 1;
            }
        }
        return res;
    }
};