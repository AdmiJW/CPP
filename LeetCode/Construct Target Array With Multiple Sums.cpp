#include <vector>
#include <queue>
using namespace std;

//https://leetcode.com/problems/construct-target-array-with-multiple-sums/
/*
 * 	This is indeed a HARD, greedy problem. Hard to figure out the strategy if you are not familiar
 *
 * 	Start out with array of 1's, get its sum, and replace one element with the sum. Repeat until
 * 	target array matches.
 * 	Immediately, realize we soon hit the dillema. Which element do we replace with the sum?
 *
 * 	One observation we can make is, the sum is strictly increasing. This deduces that the target elements
 * 	must be formed in ascending order.
 * 	However, this doesn't let us know which element to replace to make up the target next smallest larger element!
 *
 * 	The ingenious idea is, instead of working forwards to form target array, why not work backwards and see if there is
 * 	a way to reduce target array to [1,1,1]!
 *
 *	Starting with target array, pick out the largest element because it must be the most recent replaced element. Try to
 *	calculate the element before replacement of picked out largest element.
 *	If calculated the previous element is negative or 0, it's impossible so immediately return 0.
 *	However if it is valid, put back into the HEAP (which lets us pick out largest element every time), and repeat the
 *	process.
 *
 *	This apporach seems like solution, but fails for cases where it requires large amount of iteration even with
 *	small size like (1,10000000). In this case, the 10000000 repeatedly gets minus by 1, and put back into heap,
 *	repeated 9999999 times!
 *
 *	Instead, find a shortcut via the second largest element in the heap. Ask yourself, how much times I have to reduce
 *	the largest element, so the next time second largest element becomes the largest element? This eliminates the need
 *	to iterate 9999999 times, but instead, just 2 times!
 */

typedef long long int LONG;

class Comparator {
public:
	bool operator()(const LONG& l, const LONG& r) { return l < r; }
};


class Solution {
public:
	bool isPossible(vector<int>& target) {
		//	Edge case. The sum will always be 1
		if (target.size() == 1) return target[0] == 1;

		priority_queue<int, vector<int>, Comparator> heap;
		LONG sum = 0;
		for (int i : target) {
			sum += i;
			heap.push(i);
		}
	
		//	While all elements are still not yet 1, find out maximum element, and try to deduce previous state
		while (heap.top() != 1) {
			int currmax = heap.top(); heap.pop();
			int secondmax = heap.top();
			LONG sumexcluded = sum - currmax;
			int n = (currmax - secondmax) / sumexcluded;
			LONG x = currmax - max(1, n) * sumexcluded;

			if (x < 1) return false;

			//	Since currmax is replaced in imiginary array, sum will minus currmax.
			//	However, it is replaced with the new smaller x value
			sum = sum - currmax + x;
			heap.push((int)x);
		}
		//	All had become 1! Congratulations
		return true;
	}
};