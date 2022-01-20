#include <vector>
using namespace std;

//https://leetcode.com/problems/koko-eating-bananas/
/*
 * 	This is a binary search problem.
 *
 * 	Let k be the minimum eating rate of Koko to eat bananas.
 *
 * 	First of all, the maximum eating rate, M should only be k = max(piles). Given the constraint that h must
 * 	be >= piles.length, Koko can finish the bananas in piles.length time.
 *
 * 	Eg: [30,20,30,30], then the maximum k to search for is 30, taking h = 4.
 *
 *
 * 	Now, provided a k value, I can calculate the time taken to finish all the bananas in O(N) time.
 *
 * 	Therefore, one solution is to brute force all the possible k values. From the minimum k possible (1), calculate
 * 	the sum of hours that needs to be taken. Since we are brute force from minimum k, we can return as soon as we
 * 	found a workable hour.
 * 	In the worst case, it is going to take O(MN) time complexity, where M is the maximum eating rate possible.
 *
 * 	--------------------------------
 *
 * 	Instead, the solution space can very easily be binary searched:
 * 	Starting from solution space [1.. M]
 *
 * 	if selected k value results in sum of hours exceeding h:
 * 		>	Koko is eating too slow. Set left pointer to mid + 1.
 * 	Else:
 * 		>	The k value results in "possible" sum of hours. But we want to be greedy and try slower eating rate.
 * 			Set right pointer = mid.
 */


class Solution {
public:
	int minEatingSpeed(vector<int>& piles, int h) {
		int l = 1, r = h;

		// Obtain max pile in piles[], in case if max(piles) > h
		for (int p : piles) r = max(p, r);

		// Attempt at every possible values of k using binary search
		while (l < r) {
			int m = l + (r - l) / 2;		// mid value as k
			int sum = 0;

			for (int p : piles) {
				sum += ceil((double)p / m);
				if (sum > h) break;
			}

			if (sum > h) l = m + 1;
			else r = m;
		}

		return l;
	}
};