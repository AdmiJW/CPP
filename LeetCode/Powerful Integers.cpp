#include <vector>
#include <unordered_set>
using namespace std;


//https://leetcode.com/problems/powerful-integers/
/*
 * 	The problem is actually solved best using brute force?
 *
 * 	Given base integers x and y, we have to find out sums that are less than bound.
 * 	First, the results store in Set, so that at the end, no duplicate answers are present.
 *
 * 	Given x, we run a outer loop which goes over all possible power of x, from 1 onwards.
 * 	The same goes for y.
 * 	However, be careful if the base is 1, since 1 to power of anything remains 1, it easily causes
 * 	infinite loop.
 *
 * 	Instead of this approach, you may also determine the BOUNDS of power of x and y, via logarithms
 *
 * 	Since x increases at multiplying rate, outer loop takes logarithmic time. Inner loop for y is
 * 	same, so complexity is approximately
 * 		O(logx(bound) x logy(bound) )
 */

class Solution {
public:
	vector<int> powerfulIntegers(int x, int y, int bound) {
		unordered_set<int> res;

		for (int i = 1; i < bound; i *= x) {
			for (int j = 1; j < bound; j *= y) {
				if (i + j <= bound) res.insert(i + j);
				if (y == 1)break;
			}
			if (x == 1) break;
		}

		return vector<int>(res.begin(), res.end());
	}
};