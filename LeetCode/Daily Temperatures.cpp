#include <vector>
#include <stack>
using namespace std;

//https://leetcode.com/problems/daily-temperatures/
/*
 * 	This is a Monotonic Stack problem.
 *
 * 	Brute force is always the first thought: For each of the days, find the closest day which is warmer. This takes O(N^2)
 * 	time, not applicable to this problem
 *
 * 	-------------------------------------------------------------
 *
 * 	Since each day, what we want is the next closer, warmer day, we could potentially already have the information if we
 * 	are previously already iterated through it. AND in this situation, a monotonic stack could store the days in:
 * 		>	Ascending days
 * 		>	Decending temperatures
 * 	which is very suitable to solve our problem!
 *
 * 	(You can reverse this algorithm)
 * 	Iterate from backwards, for each of the days:
 * 		while the stack is not empty and the top of stack has lower temperature than current day: pop the top element
 *
 * 		if the stack is not empty, that means top of stack has the CLOSEST, but HIGHER temperature than current day.
 * 		Therefore record the days distance.
 *
 * 		Since now stack is either empty or having temperature higher, it is completely valid to push current day into the
 * 		stack. Push the index and temperature into it.
 *
 * 	------------------------------------------------------------------
 *
 * 	If we are already iterating backwards, we basically has access to the next day's temperature and next day's answer to
 * 	closest higher temperature. Think what this allows us to do:
 *
 *		If temp[i] < temp[i+1], then the answer is direct: the next day is already temperature higher.
 *
 *		Else temp[i] >= temp[i+1], we don't know when the temperature will going to be higher, but at least we can skip
 *		days by deriving from answer[i+1]. We can always skip days.
 *
 *	This idea is kind of resembling DP but not exactly. Regardless, O(2N) time complexity and O(1) space if you don't count
 *	in the solution space
 */

class Solution {
public:
	vector<int> dailyTemperatures(vector<int>& temperatures) {
		const int len = temperatures.size();
		vector<int> res(len, 0);
		// Records in { temp, index }
		stack<pair<int, int>> monotonicStack;

		monotonicStack.push({0, 0});

		for (int i = len - 1; i >= 0; --i) {
			while (!monotonicStack.empty() && monotonicStack.top().first <= temperatures[i])
				monotonicStack.pop();

			if (!monotonicStack.empty())
				res[i] = monotonicStack.top().second - i;

			monotonicStack.push({temperatures[i], i});
		}

		return res;
	}




	vector<int> dailyTemperatures2(vector<int>& temperatures) {
		const int len = temperatures.size();
		vector<int> res(len, 0);

		for (int i = len - 2; i >= 0; --i) {
			// Direct solution - Next day is already higher
			if (temperatures[i] < temperatures[i + 1]) {
				res[i] = 1;
				continue;
			}

			// Indirect - We have to locate, but skip some days
			int pt = i + 1;
			while (temperatures[i] >= temperatures[pt] && res[pt] != 0)
				pt = pt + res[pt];

			res[i] = temperatures[i] >= temperatures[pt] ? 0 : pt - i;
		}

		return res;
	}
};