#include <vector>
#include <unordered_map>
using namespace std;

//https://leetcode.com/problems/beautiful-array/
/*
 * 	This is an unintuitive, medium (HARD) math, array and divide & conquer problem.
 *
 * 	First, notice that if we were to segment the array into two parts:
 * 		| odds | evens |
 *  Then our problem is half solved, because odd+even = odd, which is impossible for 2* nums[k] to equal
 *
 *  So we just need to ensure that in each part |odd| and |even| does not cause inner nums[i] + nums[j] = 2 * nums[k].
 *
 *
 *  In other words, the |odd| and |evens| must be a beautiful array itself, too.
 *  One interesting property that beautiful array poccess, is that even if the array is multiplied by a constant,
 *  it is also beautiful array (Just maybe not a permutation of 1...N anymore) See:
 *
 *  	[ 1, 3, 2, 4 ] * 2 ====> [ 2, 6, 4, 8 ]
 *
 *  Same property holds if the array is added with constant
 *
 *  	[ 1, 3, 2, 4 ] + 1 ====> [ 2, 4, 3, 5 ]
 *
 *  In either cases, the property nums[i] + nums[j] != 2 * nums[k] holds true
 *
 *
 *
 *  In the case where a beautiful array * 2, we see that it creates a nicely even segment for N=8 or N=9!
 *  The same when the beautiful array is (array+1)/2. It creates a nicely odd segment!
 *
 *  That means, once we separated into two segments, find the beautiful array of that size and reverse the formula!
 *  Eg: N=11
 *  		[ odd of size 6 | even of size 5]
 *  Then,
 *  		odd segment will refer to (beautifulArr(6) + 1) / 2
 *  		even segment will refer to (beautifulArr(5) * 2)
 */

class Solution {
public:
	unordered_map<int, vector<int>> memo;

	vector<int> beautifulArray(int n) {
		if (n == 1) return { 1 };
		if (n == 2) return { 1, 2 };

		if (memo.count(n)) return memo[n];

		memo[n] = vector<int>(n, 0);
		vector<int>& res = memo[n];
		vector<int> odds = beautifulArray((n + 1) / 2);
		vector<int> evens = beautifulArray(n / 2);

		for (int i = 0; i < odds.size(); ++i)
			res[i] = (odds[i] * 2) - 1;
		for (int i = 0; i < evens.size(); ++i)
			res[i + odds.size()] = (evens[i] * 2);

		return res;
	}
};