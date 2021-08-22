#include <vector>
#include <algorithm>
using namespace std;


//https://leetcode.com/problems/rectangle-area-ii/
//https://github.com/ryancheunggit/leetcode/blob/rise/code/850_solution.py
/*
 * 	This is a Hard line sweep problem.
 *
 * 	The line sweep algorithm is a computational geometry algorithm which may simulate a sweep across of
 * 	points in O(N^2 log N) time (at least, in this case)
 *
 * 	We can simulate a vertical line of infinite length sweeping across the 2D plane, and event triggers
 * 	whenever we touch an opening or closing point of rectangle.
 *
 * 	Each and every rectangle can be decomposed into 2 events:
 * 		>	Opening event ( At point x, an vertical interval of y1, y2 is opened by the rectangle)
 * 		>	Closing event ( At point x, an vertical interval of y1, y2 is closed by the rectangle)
 *
 * 	Therefore, we can first preprocess the rectangles by iterating through each and every rectangle, converting
 * 	them into closing and opening Events.
 * 	Note that to account for overlapping, the events in the end, must be sorted so that position of x is
 * 	non-decreasing.
 *
 * 	Now, we will need a data structure to store currently active intervals (Rectangles) that are within range
 * 	of the rectangles.
 * 	On every event, we will first calculate the area covered by the active intervals. Once again, this can be
 * 	thought as another line sweep, as we need to traverse from bottom to top of the intervals using an infinite
 * 	horizontal line. Therefore, we have to sort the active intervals before each line sweep.
 */


typedef long long int LONG;

class Solution {
public:

	// Line Sweep Solution in O(N^2 log N) time
	int rectangleArea(vector<vector<int>>& rectangles) {
		const int MOD = 1000000007;
		const int OPEN = 0, CLOSE = 1;

		// Events stored in { x_pos, open/close, lower_y, upper_y }
		vector<vector<int>> events;
		for (vector<int>& rect : rectangles) {
			events.push_back({ rect[0], OPEN, rect[1], rect[3] });
			events.push_back({ rect[2], CLOSE, rect[1], rect[3] });
		}

		// Sort the events
		sort(events.begin(), events.end(), [](auto& x, auto& y)-> bool { return x[0] < y[0]; });

		// Active events
		vector<vector<int>> activeIntervals;
		LONG res = 0;
		int prev_x = events[0][0];

		// Iterate through each event points
		// 	>	Calculate area of active events
		//	>	Check event type to see if add to active intervals or remove
		for (auto& e : events) {
			int x_pos = e[0];
			bool isOpen = e[1] == OPEN;
			int lower_y = e[2];
			int upper_y = e[3];

			// Calculate area of active events
			res += calcActiveRectangles(x_pos - prev_x, activeIntervals);
			prev_x = x_pos;

			// Check event type
			if (isOpen) {
				activeIntervals.push_back({ lower_y, upper_y });
				sort(activeIntervals.begin(), activeIntervals.end(), [](auto& x, auto& y)-> bool { return x[0] < y[0]; });
			}
			else {
				// This part can be improved instead of linear scan
				for (auto it = activeIntervals.begin(); it != activeIntervals.end(); ++it) {
					if ((*it)[0] == lower_y && (*it)[1] == upper_y) {
						activeIntervals.erase(it);
						break;
					}
				}
			}
		}

		return (int)(res % MOD);
	}


	// Helper function to calculate active intervals area
	LONG calcActiveRectangles(int x_dist, vector<vector<int>>& activeIntervals) {
		if (activeIntervals.empty()) return 0;

		LONG res = 0;
		int prev_y = INT32_MIN;

		for (auto& interval : activeIntervals) {
			int begin_y = max(prev_y, interval[0]);
			res += max(0, interval[1] - begin_y);
			prev_y = max(prev_y, interval[1]);
		}

		return res * x_dist;
	}
};