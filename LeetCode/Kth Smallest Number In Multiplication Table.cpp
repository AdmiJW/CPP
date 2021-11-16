#include <string>
using namespace std;


class Solution {
public:
    int findKthNumber(int m, int n, int k) {
		int left = 1, right = m * n;

		while (left < right) {
			int mid = left + (right - left) / 2;
			int count = 0;

			// Run a N scan to count number of elements smaller or equal to mid
			for (int i = 1; i <= m; ++i) {
				int rightBound = min(n, mid / i);	// <- Remember, we only have n columns. mid/i can go beyond

				if (rightBound == 0) break;
				count += rightBound;
			}

			// There will be cases of overcounting - Like when k=4, where e=3.
			// However, if m = n = 3, we will count to 5.
			// The way of narrowing below, will ensure that we don't eliminate the e during an overcounting
			// case
			if (count < k)
				left = mid + 1;
			else
				right = mid;
		}

		return left;
    }
};