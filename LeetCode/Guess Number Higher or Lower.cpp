using namespace std;

//https://leetcode.com/problems/guess-number-higher-or-lower
/*
 * 	A pure binary search problem.
 * 	If we were to perform search by linear scan, we would have to iterate 2^31 times. However with binary search, we only need
 *  to search 31 iterations. Sped
 */


 /**
  * Forward declaration of guess API.
  * @param  num   your guess
  * @return 	     -1 if num is lower than the guess number
  *			      1 if num is higher than the guess number
  *               otherwise return 0
  * int guess(int num);
  */


class Solution {
public:
	int guessNumber(int n) {
		int l = 1, r = n;
		while (l != r) {
			int mid = l + (r - l) / 2;
			int g = guess(mid);
			if (g == 0) return mid;
			else if (g == -1) r = mid - 1;
			else l = mid + 1;
		}
		return l;
	}


	int guess(int num) { return 0; }
};