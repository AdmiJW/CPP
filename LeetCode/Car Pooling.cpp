#include <vector>
#include <algorithm>
using namespace std;


//https://leetcode.com/problems/car-pooling/
/*
 * 	This is considered a greedy problem.
 *
 * 	For this problem, one way to sort it is by sorting the whole schedule. First, we have to split the trip details into two:
 * 		>	The pickup
 * 		>	The drop off
 * 	This 2 details has to be split into 2 seperate events. Then, in a list of those events, we have to sort those events so it
 * 	follows the time flowing pattern.
 * 	The thing we actually need to keep track of is the number of passengers on the car. Therefore, those pickup and drop off events
 * 	can be represented as Change In Number Of Passengers, delta passengers in that time.
 *
 * 	After sorting those events by time, we could just simply iterate through the list and apply those changes in number of passengers
 * 	in a single variable, and check every time, if the number of passengers exceed the capacity, then just return false.
 *
 * 	This solution takes O(n log n) time and O(N) space, as we split the events into two seperate events and group them in a new
 * 	data structure (We could use TREEMAP, sorted key is the station -> value is change in passenger).
 *
 * 	ADVANTAGE:	> No need to loop through each possible stations. Stations not included is skipped
 * 	DISADVANTAGE: > Sorting algorithm is N log N.
 *
 * 	============================================================================================================
 *
 * 	We will use the fact that stations are at max 1000 only.
 * 	Sorting may be time consuming. If we first pass through the list, recording those station changes in a HashMap, then iterating
 * 	fully through the stations from 0 to 1000 (or whatever is maximum), this will be solved in O(N) time.
 *
 * 	This technique is called Bucket Sort. We are able to use this technique due to the fact that station is known.
 * 	If the maximum number of stations is very high, this would end up in very expensive, space consuming solution, even though
 * 	possibly the stations in the middle may not contain any pick up or drop off. Consider this trip of 1 pick up and drop off only:
 *
 * 	Pick up: 1
 * 	Drop off: 10000000
 *
 * 	Then even though we only got 1 pick up and drop off, we still need to iterate 10000000 times! Expensive time and space in this case!
 */


class Solution {
public:


	// Array of distances (up to 1000, as in problem constraints) (Bucket sort) solution
	bool carPooling(vector<vector<int>>& trips, int capacity) {
		vector<int> pickup(1001, 0);
		vector<int> dropOff(1001, 0);

		for (auto& t : trips) {
			pickup[t[1]] += t[0];
			dropOff[t[2]] += t[0];
		}

		for (int i = 0, curr = 0; i < 1001; ++i) {
			curr += pickup[i] - dropOff[i];
			if (curr > capacity) return false;
		}
		return true;
	}
};