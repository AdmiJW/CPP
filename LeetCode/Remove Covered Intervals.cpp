#include <vector>
#include <algorithm>
using namespace std;

//https://leetcode.com/problems/remove-covered-intervals/

/*
 * 	This is a greedy, sorting problem.
 *
 * 	Given intervals, we need to find the number of intervals which are fully covered by another larger (or equal) size interval.
 *
 * 	Eg: 	------			<- This interval could be eliminated because it is covered by the interval below it
 * 		----------------
 *
 * 	Eg:	-------
 * 		-------			<- This interval could also be eliminated. It is also covered by another
 *
 * 	Eg:	-----
 * 		 -----		<-	This case however none of intervals could be eliminated. No interval are fully intersected.
 *
 *
 * 	The solution is to sort the intervals using a custom comparator:
 * 		>	Sort in ascending order based on interval starting point
 * 		>	If the starting point is same, then sort the ending point BY DESCENDING ORDER, so that given intervals of same starting point,
 * 			the largest ending point (Largest among them all) is at the front
 *
 * 	We need to realize one point of the intervals now:
 * 	For each interval, the next interval must have starting point greater than or equal to the current interval.
 * 	If the starting point are equal, the ending point of it must be lesser then the current one.
 *
 * 	Therefore, since I know next interval starting point must be covered by current interval's starting, we just have to check if the
 * 	next interval's ending point is covered by the current interval's ending point.
 *
 * 	If next end < current end, then we can eliminate this 'next' interval, since it is basically 'smaller' than current interval
 * 	Otherwise, next interval is not covered by current interval. Now we shift the current interval to the next interval
 *
 * 	We just have to keep a variable recording the current interval's ending point. When the variable's end point is greater than the
 * 	next interval, eliminate it. Otherwise, set the ending point to the next interval's ending point.
 */



class Solution {
public:
    int removeCoveredIntervals(vector<vector<int>>& intervals) {
		int len = intervals.size();
		

		sort(intervals.begin(), intervals.end(), [](auto& a, auto& b)-> bool {
			if (a[0] == b[0]) {
				return b[1] < a[1];
			}
			return a[0] < b[0];
		});

		int removed = 0;
		int end = intervals[0][1];

		for (int i = 1; i < len; i++) {
			auto& arr = intervals[i];

			if (end >= arr[1]) {
				removed++;
				continue;
			}
			else end = arr[1];
		}

		return len - removed;		//	It wants the remaining length, not the eliminated count
    }
};