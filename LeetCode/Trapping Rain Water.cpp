#include <stack>
#include <vector>
using namespace std;

//https://leetcode.com/problems/trapping-rain-water/
/*
 * 	This is a (HARD to come up with idea) Dynamic Programming, Monotonic Stack problem
 *
 * 	==================================================================
 *
 * 	In brute force, we check what is the height of water that can be on top of each element.
 * 	For example, in array [5,2,3] and at the element '2', the height of water that can be stored on top of it is 1 level only due
 * 	to the '3' on the right of it.
 *
 * 	Therefore, the approach is for each element, find the maximum heights on the left and right side of the current element. Then
 * 	take the difference of the minimum of the two with the current element height.
 *
 * 	Due to this, the time complexity is O(N^2) albeit with O(1) space.
 *
 * 	====================================================================
 *
 * 	From above brute force, we simply come up with a min DP and max DP array which records the max element to the left and max element
 * 	to the right of each element.
 *
 * 	This utilizes O(N) extra space, but reduces the time complexity to linear O(N)
 *
 * 	=====================================================================
 *
 * 	For Monotonic stacks (coming from similar Histogram problem), the idea is for each of the bars, if we know on the left
 * 	that there is shorter bars, then surely water will accumulate between them. see:
 *
 * 	[10, 8, 6, 10]
 *
 * 	When we are at last element of '10', we need to know on the left, '6', '8', and '10' are present to calculate the water
 * 	accumulated between current bar and the current '10' bar.
 *	Somehow, we need to calculate:
 *		>	(Distance between '6' and '10') * (10 - 6)
 *		>	(Distance between '8' and '10') * (8 - 6)
 *		>	(Distance between '10' and '10') * (10 - 8)
 *
 *  As you might figure out, a monotonic stack is suitable for this job, which stores bars in non-increasing order:
 *	While current bar is higher than previous one, start calculating the water that will accumulate between them
 *
 *	=====================================================================
 *
 * 	The most ingenious solution - Two pointers approach, shares the same strategy as that in DP.
 *
 * 	Keep two pointers, left and right initialized to both ends of array, as well as leftMax and rightMax which records the
 * 	maximum bar to the left of left pointer and maximum bar to the right of right pointer respectively.
 *
 * 	Every iteration (while left < right), select the one pointer between left and right where the height is smaller.
 * 	Now, say the left pointer is smaller. We check the bar on this pointer can have water on top of it or not:
 *
 * 		>	If the current pointer height is larger or equal to that of leftMax, surely water cannot be hold.
 * 			So simply update leftMax to current bar.
 *		>	However, if current bar is lower than leftMax. We know immediately that water can be trapped on top of current bar,
 *			due to the fact:
 *				>	The fact that we chosen left bar over right bar, is because RIGHT BAR IS EVEN HIGHER THAN LEFTMAX (Otherwise,
 *					right bar will be chosen and move instead)
 *				>	Of course, leftMax is higher than current bar.
 *
 *			Thus the total volume of water that will be trapped, will be limited by leftMax. See:
 *					RIGHTBAR > LeftMax > currentBar
 *
 *	The same approach goes for right pointer as well.
 */


class Solution {
public:

	// My own monotonic stack solution (Not Optimal)
	int trap(vector<int>& height) {
		const int len = height.size();
		int res = 0;
		stack<pair<int, int>> stack;		// {height, index}

		for (int i = 0; i < len; ++i) {
			int h = height[i];

			// Push into Stack if the stack is empty, or when the current height is lower than previously met wall
			if (stack.empty() || h < stack.top().first)
				stack.push({h, i});
			// Same height. Overwrite the wall because the previous one has no uses already (Blocked by most recent)
			else if (stack.top().first == h)
				stack.top().second = i;
			// Otherwise current wall is higher than previous wall. Start calculating the volume of water
			else {
				int lastHeight = stack.top().first;
				stack.pop();

				// Keep calculating as long as the stack haven't emptied and the left wall still lower or equal the current wall
				while (!stack.empty() && stack.top().first <= h) {
					pair<int,int> left = stack.top();
					stack.pop();
					res += (left.first - lastHeight) * (i - left.second - 1);
					lastHeight = left.first;
				}

				// At the end, the stack can either be empty, or the left side wall is higher than current wall.
				// If the latter, we need to calculate once more but this time, left wall is higher
				if (lastHeight < h && !stack.empty() && stack.top().first > h)
					res += (h - lastHeight) * (i - stack.top().second - 1);
				// Either case, push the wall into stack
				stack.push({h, i});
			}
		}
		return res;
	}


	// Official DP solution
	int trap2(vector<int>& height) {
		const int len = height.size();
		if (len == 0) return 0;

		vector<int> maxLeft(len, 0);
		vector<int> maxRight(len, 0);
		int res = 0;

		maxLeft[0] = height[0];
		maxRight[len - 1] = height[len - 1];

		for (int i = 1; i < len; ++i)
			maxLeft[i] = max(height[i], maxLeft[i - 1]);
		for (int i = len - 2; i >= 0; --i)
			maxRight[i] = max(height[i], maxRight[i + 1]);

		// Remember: first and last element couldn't possibly has water on it
		for (int i = 1; i < len - 1; ++i)
			res += max(0, min(maxLeft[i - 1], maxRight[i + 1]) - height[i]);

		return res;
	}


	// Official Stack solution
	int trap3(vector<int>& height) {
		const int len = height.size();
		stack<int> stack;
		int res = 0;

		for (int i = 0; i < len; ++i) {
			int h = height[i];
			// While stack is not empty, and the bar at top of stack is shorter, we need to calculate accumulated water
			while (!stack.empty() && height[stack.top()] < h) {
				int base = stack.top();
				stack.pop();

				// No previous bar already to accumulate water. The case does not hold
				if (stack.empty())
					break;

				// Distance between current bar and the previous bar to hold water
				int dist = i - stack.top() - 1;
				// The height difference to store water
				int heightDiff = min(h, height[stack.top()]) - height[base];

				res += dist * heightDiff;
			}
			stack.push(i);
		}
		return res;
	}

	// Official Two Pointers solution
	int trap4(vector<int>& height) {
		const int len = height.size();
		int res = 0;

		int leftPt = 0, rightPt = len - 1;
		int leftMax = 0, rightMax = 0;

		while (leftPt < rightPt) {
			// Left Pointer's height is smaller
			if (height[leftPt] < height[rightPt]) {
				// Height >= leftMax
				if (height[leftPt] >= leftMax)
					leftMax = height[leftPt];
				else
					res += leftMax - height[leftPt];
				++leftPt;
			}
			// Right Pointer's height is smaller
			else {
				// Height >= rightMax
				if (height[rightPt] >= rightMax)
					rightMax = height[rightPt];
				else
					res += rightMax - height[rightPt];
				--rightPt;
			}
		}

		return res;
	}

};