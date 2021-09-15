#include <vector>
using namespace std;

//https://leetcode.com/problems/longest-turbulent-subarray/
/*
 * This is a Array, Dynamic Programming problem.
 *
 * First of all, let's observe from left to right, what we need to do is to simply compare current
 * element with the previous one and see if it is increasing, decreasing or same value.
 *
 * If a subarray is interrupted (Either by same sign or same value), we MUST start a new subarray, there is no
 * other way around. See:
 *
 * 		10,100,20,200,30,300,20
 *
 * At the last 20, I can see it interrupted the turbulent subarray so far, and we are forced to start a new
 * turbulence subarray at [300,20]. No other ways to form a new subarray.
 *
 * Using this, we can use DP technique with the aid of recording some informations:
 * 	-	Previous trend (increasing, still, decreasing)
 * 	-	Largest turbulent subarray length that ends with previous element.
 *
 * We break down the cases:
 * 	-	If current trend is same value, we have to start new turbulent subarray with current element ONLY.
 * 		latestLen = 1
 *
 * 	-	Else, if previous trend is same value, then we can extend the previous turbulent array no matter what
 * 		current trend was.
 * 		Eg:		[8,8,4]
 * 					 ^
 * 		We start a new subarray with [8,4]. latestLen = 2 (OR latestLen++ is also plausible)
 *
 * 	-	Else, if previous trend is same as current trend, subarray is interrupted. We must start a new subrray
 * 		of length 2.
 * 		Eg:		[2,4,8]
 * 					 ^
 * 		We have no choice but to start subarray [4,8], unable to extend previous [2,4]
 *
 * 	-	Else, the trend shift signs, so we can extend previous subarray. ++latestLen;
 *
 * At the end, return the largest latestLen recorded ever.
 */

class Solution {
public:
	int maxTurbulenceSize(vector<int>& arr) {
		const int len = arr.size();
		int res = 1;
		char sign = '~';
		int latestlen = 1;

		for (int i = 1; i < len; ++i) {
			char currsign = arr[i] == arr[i - 1] ? '~' : arr[i] > arr[i - 1] ? '>' : '<';

			if (currsign == '~') latestlen = 1;
			else if (sign != currsign) ++latestlen;
			else latestlen = 2;

			res = max(res, latestlen);
			sign = currsign;
		}
		return res;
	}
};