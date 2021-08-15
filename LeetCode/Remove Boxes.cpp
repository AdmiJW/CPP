#include <vector>
using namespace std;

//https://leetcode.com/problems/remove-boxes/

// Reference: https://www.youtube.com/watch?v=wT7aS5fHZhs
/*
 * 	This is a HARD 3 Dimensional Dynamic Programming problem.
 * 	Of course I cannot solve it alone.
 *
 * 	The naive solution would be to have a 2D DP array where dp[i][j] indicates
 * 	the maximum score that can be obtained from eliminating boxes from index [i] to [j].
 *
 * 	The transition function is to consider all splitting points in range of i to j, and combine solutions to subproblem.
 * 	For example i=0 and j=3, we will consider splitting to (0,0)+(1,3), (0,1)+(2,3), (0,2)+(3,3) etc.
 *
 *	However, that is not sufficient for this problem. We are unable to combine the same color boxes if they are apart, like
 *	case in "ABA", the case where B is eliminated first is not counted.
 *
 *	======================================
 *
 *	Instead we use 3Dimensional DP array, dp[i][j][k]. The i and j still holds the same meaning of maximum score in range
 *	index i to j. However, k means "the number of boxes that holds the same color as the box at index j". See:
 *
 *		"ABACCAAA" -> Say i=0, j=2. box[j] = A. Now, k would be 3 since there are 3 'A's after index 2 (j).
 *
 *	Initially, our problem is to find out dp[0][len-1][0]. Now within the subproblem, what we could do is:
 *
 *		>	Eliminate the last element, along with the k boxes that follow it. (We assume that the non same color boxes after
 *			j is elimated).
 *
 *				dp( "ABACCAA", "A") <- The last "A" is eliminated. The rest is computed in dp(i, len-2, 0)
 *
 *		>	For each intermediate element that is same value as jth box, that is a potential splitting point. We do
 *
 *				dp(i, j-1, k+1) + dp(j+1, r-1, 0)
 *
 *			The k+1 is to take account that the rightmost element is included.
 *
 *	This problem is hard and confusing. See reference for more details
 */

class Solution {
public:
	int removeBoxes(vector<int>& boxes) {
		const int len = boxes.size();
		vector<vector<vector<int>>> dp(len, vector<vector<int>>(len, vector<int>(len, 0)));
		return memo(0, len - 1, 0, boxes, dp);
	}

	int memo(int l, int r, int k, vector<int>& boxes, vector<vector<vector<int>>>& dp) {
		if (l > r) return 0;
		if (dp[l][r][k] != 0) return dp[l][r][k];

		// Action 1: Eliminate the k boxes along with rightmost element
		dp[l][r][k] = memo(l, r - 1, 0, boxes, dp) + (k + 1) * (k + 1);

		// Action 2: Find intermediate elements with same value as rightmost element, and attempt to join it with k boxes
		for (int i = l; i < r; ++i) {
			if (boxes[i] == boxes[r])
				dp[l][r][k] = max(
					dp[l][r][k],
					memo(l, i, k + 1, boxes, dp) + memo(i + 1, r - 1, 0, boxes, dp)
				);
		}
		return dp[l][r][k];
	}
};