#include <vector>
#include <algorithm>
using namespace std;

//https://leetcode.com/problems/largest-divisible-subset/

/*
 * 	This is a Dynamic Programming, Sorting problem
 * 	The intuition is from the DP question Largest Increasing Subsequence (LIS).
 *
 * 	Let's derive some mathematic properties first in order to solve this problem:
 * 	In order for two numbers a and b to divide properly, it must be this condition:
 *
 * 		a = nb		(a is n times of b)
 *
 * 	Therefore, according to the problem, a set of numbers which every two number a and b must be able to divide each other,
 * 	must all be multiples of one another! See:
 * 		{ 1, 4, 8, 32, 128 }...
 * 	128 is four times 32, which is also four times 8, which is two times 4, which is four times 1
 *
 * 	This lead us to one conclusion: If we already have such valid divisible set, then to determine whether a new element e
 * 	can fit inside this set or not:
 * 	>	We simply take the largest element from the set, and check if it is divisible or not. IF YES, then we can safely
 * 		insert new element e into the set, which is proved to be multiple of any number in the set.
 *
 * 	Taking example from previous: { 1, 4, 8, 32, 128 }
 *
 * 	Can 256 fit inside? We check the largest element: 128. 256 is divisible by 128. OK it is valid!
 * 	Can 192 fit inside? We check the largest element: 128. 192 is NOT divisible by 128. NO we cannot!
 *
 * 	However, this means we always need to access the largest element in the set quickly, and also process the numbers
 * 	in ascending order.
 * 	(Could be not required, but makes job easier as there's no need for comparing larger element)
 *
 * 	=====================================================================================
 *
 * 	Therefore, we first sort the array.
 * 	For each of the element e, it could possibly pair with any past elements, which may already belong in a subset.
 *
 * 	DP[i] records two things:
 * 		{
 * 			The previous index of element that is also in the same largest subset as this element,
 * 			The maximum length of subset it belongs to
 * 		}
 *
 * 	For each of the element e, initially it can form a subset by itself. Therefore the dp = {-1, 1}.
 *
 * 	-1 means there is no previous index of element that is also in largest subset. 1 is the length of subset, which is formed
 * 	by e itself.
 *
 * 	Then, traverse backwards to find the maximum length subset, which:
 * 		- num[i] % num[j] == 0										(Divisible)
 * 		- dp[j].lengthOfSubset + 1 > dp[i].lengthOfSubset			(When added to that subset, will create larger subset)
 * 	Record the optimal value in dp.
 *
 * 	At the end , you should have the index of the tail element in the largest subset. Since parent element index is recorded,
 * 	we can follow the path to retrieve the subset itself.
 */

class Solution {
public:

    vector<int> largestDivisibleSubset(vector<int>& nums) {
        const int len = nums.size();
        vector<pair<int, int>> dp(len);
        int maxIndex = -1;
        int maxLength = 0;

        // 1 - Sort to process the numbers from smallest to largest
        sort(nums.begin(), nums.end());

        // 2 - For each number, find largest subset it can belong to, and record in dp
        for (int i = 0; i < len; ++i) {
            dp[i] = { -1, 1 };

            // Traverse backwards to find the dp solution for this iteration
            for (int j = i - 1; j != -1; --j) {
                if (nums[i] % nums[j] == 0 && dp[j].second + 1 > dp[i].second)
                    dp[i] = { j, dp[j].second + 1 };
            }

            // Update max
            if (dp[i].second > maxLength) {
                maxIndex = i;
                maxLength = dp[i].second;
            }
        }


        // 3 - Construct result
        vector<int> res;
        for (int i = maxIndex; i != -1; i = dp[i].first)
            res.push_back(nums[i]);
        return res;
    }

};