#include <vector>
#include <unordered_map>
using namespace std;


//https://leetcode.com/problems/subarray-sum-equals-k/
/*
*   This is a prefix sum, hash map problem.
* 
*   We have to find out how many subarray in the original array that sums up to k. To solve this, we can use the following idea:
*   > For each index i, we find out how many subarrays that ends at index i, and sum to k can be formed
* 
*   Indeed, it is very easy to get the sum of elements from index [0,i] - That is the prefix sum! If we iterate from left to right,
*   having prefix sum is extremely easy.
* 
*   Now, to determine how many subarrays can be formed, consider that the prefix sum is now S. To form subarrays of sum k, we have to
*   eliminate some subarrays on the left of i, that is, for some index j such that j < i, [0,j] has to be eliminated so that (j, i] sums
*   to k
* 
*   Eg:   [1,2,3,4,5]
*   If k = 12, and we are now at index 4 (element 5). Prefix sum is now 15.
*   To reach k = 12, we have to eliminate some subarray that is having sum = (15 - k) = (15 - 12) = 3.
*   
*   Indeed, the subarray [1,2] sum is 3, by eliminating that, we are left with [3,4,5] which is 12!
* 
*   -------------------------------------------------
* 
*   Therefore, we need ways to record the sums of the subarrays that spans [0, j] such that j < i. Additionally, since there may be
*   repetitions where some number can be formed by multiple subarrays, like:
* 
*       [1,2,-2]. If we are looking for 1, then it can be formed by: [1] or [1,2,-2]!
* 
*   Therefore, we have to record both <sum, frequency>, and map is the perfect candidate for this.
*/



class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        // Maps (subarray_sum -> count)
        unordered_map<int, int> count;
        int res = 0;

        count[0] = 1;

        int prefixSum = 0;
        for (int i : nums) {
            prefixSum += i;

            // Find how many subarray to k can be formed
            int other = prefixSum - k;
            if (count.count(other)) res += count[other];

            // Record the prefixSum
            ++count[prefixSum];
        }
        return res;
    }
};