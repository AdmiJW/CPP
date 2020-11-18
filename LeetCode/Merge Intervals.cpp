#include <vector>
#include <algorithm>
#include <cmath>

//https://leetcode.com/problems/merge-intervals/

/*
 * 	This is a interval arrays problem, which mostly involves sorting
 *
 * 	Given a list of intervals and we have to sort them. First of all, those intervals may be jumbled up, so we
 * 	have to sort them so that from left to right it is easier to see and process
 *
 * 	Sort by the interval start point is enough.
 *
 * 	We will have a pivot interval at all times, which is the interval that has the lowest "local" start point.
 * 	The next intervals may be merged, so we have to check it.
 * 	While the next interval's start point is less than previous interval's end point, the interval may be merged
 * 	and we update the end pointer to be maximum of end pointer itself or the current intervals end point.
 *
 * 	The time when we need to actually proceed to new pointer is when the next interval's start point is greater than
 * 	the recorded end point. Then, push the last recorded interval into result, and proceed to the new interval.
 */

class Solution {
public:
    std::vector< std::vector<int>> merge( std::vector< std::vector<int>>& intervals) {
        const int size = intervals.size();

        std::sort(intervals.begin(), intervals.end(), [](auto x, auto y) -> bool {
            return x[0] - y[0] < 0;
        });

        std::vector< std::vector<int> > res;

        int idx = 1;
        int start = intervals[0][0], end = intervals[0][1];

        while (idx < size) {
            //  If the pivot interval's end value is greater or equal to current start, merged!
            if (end >= intervals[idx][0]) {
                end = std::fmax(intervals[idx][1], end);
            }
            //  Otherwise the start of next one is greater than last end. The last interval push it into vector
            else {
                res.push_back({ start, end });

                start = intervals[idx][0];
                end = intervals[idx][1];
            }
            idx++;
        }

        //  Don't forget the last one
        res.push_back({ start,end });

        return res;
    }
};