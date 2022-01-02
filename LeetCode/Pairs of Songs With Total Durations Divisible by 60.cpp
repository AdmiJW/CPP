#include <vector>
using namespace std;

//https://leetcode.com/problems/pairs-of-songs-with-total-durations-divisible-by-60/

/*
 * 	This is an array problem.
 *
 * 	The time itself is not so important. WHat's important is the remainder of it when divided by 60, and the
 * 	60 - remainder (Amount of minutes needed again to add up to multiple of 60)
 *
 * 	Each element, we just have to consider this problem:
 * 		How much minute i still have to add to make this form a pair divisible by 60?
 * 	If we have a frequency table keeping track of previous counts of contribution minutes, this problem can
 * 	be solved easily.
 *
 * 	Contribution minutes is the extra minutes obtained (remainder) when the time is divided by 60. How much
 * 	the time itself can contribute to the other pair of time to make up to 60.
 *
 * 	Eg: time of 59 minute can contribute 59 minutes to other pair, which is 1, 61 etc...
 */

class Solution {
public:
	int numPairsDivisibleBy60(vector<int>& time) {
		int bucket[60] = {}; 
		int res = 0;

		for (int n : time) {
			int remainder = n % 60;
			res += bucket[ (60 - remainder) % 60 ];
			++bucket[remainder];
		}
		return res;
	}
};