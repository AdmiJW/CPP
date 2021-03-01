#include <unordered_set>
#include <vector>
#include <algorithm>
using namespace std;

//https://leetcode.com/problems/distribute-candies/solution/
/*
 *	This is a greedy / HashSet, sorting problem
 *
 * 	Alice wants to eat all the candy variations. We will fulfill her request by trying to give all the
 * 	variations to her, avoiding same eaten types as much as possible, in other words, always give her
 * 	the never seen before candy type whenever possible!
 *
 * 	This is done via HashSet! By putting all candies into Set, it will only keep those unique type of
 * 	candies! At the end, check whoever is smaller:
 * 		>	Limit set by doctor: n / 2
 * 		>	Number of types of candies
 *
 * 	and return as answer. Time is O(N) as well as space
 *
 * 	-------------------------------------------------------
 *
 * 	Can we eliminate extra space? Yes. Essentially we just need a way to know if a candy has been seen before
 * 	or not!
 *
 * 	By sorting in place, all the identical candy types are group together, and we can use this property to
 * 	make single iteration to count how many types are there. At the end, check whether doctor's limit or
 * 	type of candies are smaller, like above!
 *
 * 	Time is increased to O(N log N) but space is reduced to O(1)
 *
 */

class Solution {
public:
	int distributeCandies(vector<int>& candyType) {
		unordered_set<int> candies(candyType.begin(), candyType.end());
		return min(candies.size(), candyType.size() / 2);
	}





	int distributeCandies2(vector<int>& candyType) {
		sort(candyType.begin(), candyType.end());
		int type = 1;
		for (int i = 1; i < candyType.size(); ++i)
			if (candyType[i] != candyType[i - 1]) ++type;
		return fmin(type, candyType.size() / 2);
	}
};