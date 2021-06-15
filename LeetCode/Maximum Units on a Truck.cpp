#include <vector>
#include <algorithm>
using namespace std;

//https://leetcode.com/problems/maximum-units-on-a-truck/
/*
 * 	This is a introductory greedy, sorting problem.
 *
 * 	If we can load certain amount of boxes only, of course we will be picking the boxes with large unit as priority!
 * 	If we sort the boxes beforehand by descending units, then it is ensured the boxes we first encounter is the best
 * 	box to take.
 *
 * 	For a O(N) runtime, observe that units can only goes up until 1000. This enables counting sort, which records
 * 	how many such boxes have i units. At the end, iterate i from largest until smallest while loading the truck
 */

class Solution {
public:

	//	boxTypes -> { number of such boxes, units per box }
	int maximumUnits(vector<vector<int>>& boxTypes, int truckSize) {
		int res = 0;
		sort(boxTypes.begin(), boxTypes.end(), [](auto& l, auto& r) -> {
			return l[1] > r[1];
		});

		for (auto& boxes : boxTypes) {
			if (!truckSize) return res;

			res += min(truckSize, boxes[0]) * boxes[1];
			truckSize -= min(truckSize, boxes[0]);
		}
		return res;
	}


	//	Counting sort because values of max box per unit only goes up to 1000
	int maximumUnits2(vector<vector<int>>& boxTypes, int truckSize) {
		//	Unit -> Number of such boxes
		int freqs[1001] = {};
		for (auto& boxes : boxTypes)
			freqs[boxes[1]] += boxes[0];

		int res = 0;
		for (int i = 1000; i > 0 && truckSize; --i) {
			res += min(truckSize, freqs[i]) * i;
			truckSize -= min(truckSize, freqs[i]);
		}
		return res;
	}

};
