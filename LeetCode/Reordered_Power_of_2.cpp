#include <vector>
#include <array>
#include <algorithm>
#include <string>
using namespace std;

//https://leetcode.com/problems/reordered-power-of-2/
/*
 *	This is a mathematical problem, testing you what approach you take to solve problem
 *
 * 	First approach would be to do exactly what the problem asks: To generate each permutation of the digit and check
 * 	each case if it is a power of 2 or not.
 * 	Permutations can be generated via backtracking algorithm with recursion. However this approach is costly. Since the
 * 	upper limit is N = 1000000000, there are 10 digits, and 10! would be 3628800. Quite costly isn't it?
 *
 * 	Note that via bit manipulation, a power of 2 can be checked easily by looking if the whole binary string contains only
 * 	1 '1' bit and other is 0 only.
 *
 * 	==========================================================
 *
 * 	ABout permutations, we can simply count the frequencies of digits. For given N, count the number of 0...9 inside that
 * 	number. Then, we could prepare a list of power of 2 digit frequencies, and compare them individually. Once match, simply
 * 	return true.
 *
 * 	This approach is much better. For LIMIT N, we only need to store log2(N) permutations. Then, When checking if a number can
 * 	be rearranged to power of 2 or not, also takes log2(N) time.
 *
 * 	For all possible power of 2 digit counts, you can either do it at runtime at every function call, or cache it if it is called
 * 	frequently. Here I used the cache method
 *
 * 	(Apart from counting in array, we can also use sort method)
 */


class Solution {
public:
	static const int LIMIT = 1000000000;
	static const vector<array<int, 10>> perms;

	bool reorderedPowerOf2(int N) {
		return isPowerOf2(N);
	}

private:

	//	Checks if i's digit frequency is any match to that of the cached power of 2's
	static bool isPowerOf2(int i) {
		array<int, 10> freq = {};
		for (char c : to_string(i))
			++freq[c - '0'];

		for (auto& perm : perms) {
			auto isMatch = mismatch(perm.begin(), perm.end(), freq.begin());
			if (isMatch.first == perm.end() && isMatch.second == freq.end()) return true;
		}
		return false;
	}
};


//	Static initializer for the power of 2 digit frequencies
const vector<array<int, 10>> Solution::perms = [] {
	vector<array<int, 10>> res;
	for (int i = 1; i <= Solution::LIMIT; i <<= 1) {
		array<int, 10> freqs = {};
		for (char c : to_string(i))
			++freqs[c - '0'];
		res.push_back(freqs);
	}
	return res;
}();