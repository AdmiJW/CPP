#include <vector>
#include <string>
using namespace std;


class Solution {
public:
	int numDecodings(string& s) {
		const int len = s.length();
		if (!len || s[0] == '0') return 0;

		// Index 0 to put 1. Index 1 is no of ways to decode for substring until 1st char inclusiv, which is 1
		// Think this DP as 1-indexed
		vector<int> dp(len + 1, 1);

		for (int i = 1; i < len; ++i) {
			int v0 = (s[i - 1] - '0') * 10;
			int v1 = (s[i] - '0');

			if (v0 + v1 == 0) return 0;

			int alone = v1 ? dp[i] : 0;
			int pair = (v0 + v1 > 26 || !v0) ? 0 : dp[i - 1];

			dp[i + 1] = alone + pair;
		}
		return dp[len];
	}



	int numDecodings2(string& s) {
		const int len = s.length();
		if (!len || s[0] == '0') return 0;

		int dp[2] = { 1,1 };

		for (int i = 1; i < len; ++i) {
			int v0 = (s[i - 1] - '0') * 10;
			int v1 = (s[i] - '0');

			if (v0 + v1 == 0) return 0;

			int alone = v1 ? dp[1] : 0;
			int pair = (v0 + v1 > 26 || !v0) ? 0 : dp[0];

			dp[0] = dp[1];
			dp[1] = alone + pair;
		}
		return dp[1];
	}
};