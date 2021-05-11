#include <vector>
using namespace std;

//https://leetcode.com/contest/weekly-contest-186/problems/maximum-points-you-can-obtain-from-cards
/*
 * 	This is an array problem
 *
 * 	Since the cards are all positive, I would want to use up all k available moves to get maximum score.
 * 	However, how many cards from left side and how many from right side is the problem
 *
 * 	Let's try to obtain all cards from left side first. One by one, I will get one card from right side while
 * 	discarding the leftmost card from left section. Compare the scores to see what maximum score I can get.
 */

class Solution {
public:
	int maxScore(vector<int>& cardPoints, int k) {
		//	Convert cardpoints into running sum array
		const int len = cardPoints.size();

		for (int i = 1; i < len; ++i)
			cardPoints[i] += cardPoints[i - 1];

		int res = 0;
		//	Iterate the number of cards i take from left side. The rest of card will be taken from
		//	right side then
		for (int i = 1; i <= k; ++i) {
			int right = k - i;
			res = max(res, cardPoints[i-1] + cardPoints[len-1] - cardPoints[len-1-right]);
		}
		//	Also consider if i take none from left side. I will take k cards from right then
		res = max(res, len == k ? cardPoints[len-1] : cardPoints[len-1] - cardPoints[len-1-k]);
		return res;
	}
};