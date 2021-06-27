#include <vector>
using namespace std;

//https://leetcode.com/problems/candy/solution/
/*
 * This is a Array greedy problem. HARD to get the idea with solution
 *
 * When distributing candies, we always try to give as little candy as possible.
 * One such method is two pass.
 * First pass is from left to right, which we keep comparing the current child with the
 * previous one, and give extra candy whenever current child has higher rating than the previous
 *
 * It is important to initialize the candies distributed to each children as 1, as the minimum candies each children can have
 * is 1.
 *
 * After left to right, we also need to check each child relative to i+1 child. Using the previous candy distribution, put it as
 * max( candy[i], candy[i+1] + 1) whenever rating of ith child is greater than i+1 child.
 * This is because candy[i+1] + 1 might still be lower than candy[i] obtained from left to right iteration even after adding one
 * extra candy to it.
 */

class Solution {
public:
	int candy(vector<int>& ratings) {
		const int len = ratings.size();
		vector<int> resultArr(len, 1);
		int res = 0;

		//	First pass - left to right
		for (int i = 1; i < len; ++i)
			if (ratings[i] > ratings[i - 1]) resultArr[i] = resultArr[i - 1] + 1;

		//	Second pass - right to left
		for (int i = len - 2; i >= 0; --i) {
			if (ratings[i] > ratings[i + 1]) {
				resultArr[i] = max(resultArr[i], resultArr[i + 1] + 1);
			}
			res += resultArr[i];
		}

		return res + resultArr[len - 1];
	}
};