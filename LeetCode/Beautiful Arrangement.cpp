//https://leetcode.com/problems/beautiful-arrangement/
/*
 * 	This is a Backtracking problem (With possible bitmasking technique)
 *
 * 	We can always attempt to insert numbers into the position i, and proceed to position i+1. This continues until
 * 	we reach n+1 which means one beautiful arrangement is formed.
 *
 * 	Instead of generating all possible permutations which takes O(N!) time, we should be checking if the number
 * 	is valid in ith position or not. This eliminates a lot of useless computation already.
 *
 * 	To check if a number is valid in position i or not, either the position i divides n, or n divides i. This means
 * 	either one of the modulo must be 0 (No remainder). Also, the number cannot be used twice (Doesnt exist yet)
 *
 * 	---------------------------------
 *
 * 	To check either if a number is used before, instead of building the actual list, we can use Set or boolean array.
 * 	Since the state size is small, we can even use bitmasking here.
 *
 */


class Solution {
public:
	int countArrangement(int n) {
		bool isUsed[16] = {};
		return recurse(isUsed, 1, n);
	}
	int recurse(bool isUsed[], int i, int n) {
		if (i == n + 1) return 1;

		int res = 0;
		for (int t = 1; t <= n; ++t) {
			if ((!(t % i) || !(i % t)) && !isUsed[t]) {
				isUsed[t] = true;
				res += recurse(isUsed, i + 1, n);
				isUsed[t] = false;
			}
		}
		return res;
	}



	int countArrangement2(int n) {
		int mask = 0;
		return recurse(mask, n);
	}
	int recurse(int& mask, const int& n) {
		int pos = countBits(mask) + 1;
		if (pos == n + 1) return 1;

		int res = 0;
		for (int t = 1; t <= n; ++t) {
			if ((!(t % pos) || !(pos % t)) && !(mask & (1 << t - 1))) {
				mask |= (1 << t - 1);
				res += recurse(mask, n);
				mask ^= (1 << t - 1);
			}
		}
		return res;
	}
	int countBits(int mask) {
		int count = 0;
		while (mask) {
			count += mask & 1;
			mask >>= 1;
		}
		return count;
	}
};