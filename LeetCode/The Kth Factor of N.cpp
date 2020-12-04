#include <vector>
#include <cmath>
using namespace std;

//https://leetcode.com/problems/the-kth-factor-of-n/

/*
 * 	This is just a Mathematics question. Find out the Kth factor of N when the factors are sorted in ascending order
 *
 * 	The brute force algorithm is OK. Just iterate from 1 to n. counting the numbers of factors encountered when modulo
 * 	is 0. If the counter hits k, return the value immediately.
 * 	Of course, time complexity is O(N) with space O(1)
 *
 * 	-----------------------------------------------------------------------
 *
 * 	Notice the following fact: A factor of a number N means there is two integers such that (x1)(x2) = N.
 * 	By finding out (x1), we can already determine (x2) easily.
 * 	Next question is, what is maximum value of x1, if x1 cannot be larger than x2?
 * 	Answer is sqrt(N). This is because, say the N is perfect square, then the best factor is already sqrt(N) * sqrt(N).
 * 	If we were to increase x1 further, x2 has to decrease to multiply to N!
 *
 * 	Therefore with this fact in mind, it is like 'Reflection'.
 * 	Generate all the x1, and based on K value, find whether we are looking for x1 (factors less than sqrt(N) ), or x2
 * 	(factors larger than sqrt(N)), which is found from dividing n by respective x1.
 *
 * 	If we do generate and store it, then the time complexity is O(sqrt(N)) and space O(sqrt(N))
 *
 * 	Do watch out for edge cases where N is perfect square. In that case, if we were to find reflection, there may be
 * 	2 same values! Eg: 16 -> [1,2,4,4,8,16]. The two occurrences of 4 is not allowed
 *
 * 	---------------------------------------------------------------------------
 *
 * 	Notice: we can use k as counter. As soon as k is not zero, we are still looking. Thus, first go in forward direction
 * 	generating the x1, decrementing k as we encounter a factor. As soon as k hits 0, return i immediately.
 *
 * 	To avoid the edge case where N is perfect square, we iterate with sqrt(N) exclusively (The sqrt(N) shall not be included
 * 	in both two loops, only 1)
 *
 * 	If k is not yet 0, go in backward direction to find x2. Same, start from sqrt(N) until 1, as soon as we hit factor,
 * 	decrement k. But if k hits 0, return n / i instead since we are looking at x2 now.
 */

class Solution {
public:
	
	//	Brute force Time Complexity O(N), space O(1)
	int kthFactor(int n, int k) {
		int count = 0;

		for (int i = 1; i <= n; i++) {
			if (!(n % i)) count++;

			if (count == k) return i;
		}
		return -1;
	}


	//	O(sqrt(N)) time complexity, space O(sqrt(N)) solution
	int kthFactor2(int n, int k) {
		vector<int> li;
		double sqrt = std::sqrt(n);

		for (int i = 1; i <= sqrt; i++) {
			if (!(n % i)) li.push_back(i);
		}

		bool isLastSame = (fmod(sqrt, 1) == 0);
		const int len = li.size();
		const int final_len = isLastSame ? 2 * len - 1 : 2 * len;

		if (k > final_len) return -1;
		if (k <= len) return li[k - 1];
		if (isLastSame)
			return n / li[len - (k % len + 1)];
		else
			return n / li[len - 1 - ((k - 1) % len)];
	}


	//	O(2 sqrt(N)) time, O(1) space
	int kthFactor3(int n, int k) {
		int sqrt = std::sqrt(n);

		for (int i = 1; i <= sqrt; i++) {
			if (!(n % i) && !--k) return i;
		}

		sqrt = sqrt * sqrt == n ? sqrt - 1 : sqrt;

		for (int i = sqrt; i > 0; i--) {
			if (!(n % i) && !--k) return n / i;
		}
		return -1;
	}
};