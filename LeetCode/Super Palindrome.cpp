#include <vector>
#include <string>
using namespace std;

typedef long long int LONG;

//https://leetcode.com/problems/super-palindromes/
/*
 * 	This is a palindrome problem
 *
 * 	My approach is, first notice the range is at top 10^18, which when square root, is only 10^9 (Still large)
 *
 * 	Therefore, instead of finding a number and checking if the square root is also palindrome, I find square root
 * 	and check its square is also palindrome or not.
 *
 * 	We cannot iterate from 1 to 10^9. Therefore, I only will iterate those who are palindromes itself, and check
 * 	if the square is palindrome or not, and whether it falls in range.
 *
 * 	I cached all the palindrome of various lengths. The cached size will have 222220 entries, which is still in
 * 	reasonable size.
 *
 * 	To generate such palindrome, I consider the fact that all palindrome has following property:
 * 		>	First and last digit same
 * 		>	Middle must be palindrome
 * 	Using previously cached palindromes, i can generate palindromes for current length palindromes. However you must
 * 	consider also "000" etc, because later the larger palindrome might use this one in their generation
 *
 * 	--------------------------
 *
 * 	Another idea is that, the largest num is 10^9. But using the fact that other half is simply reflection of current
 * 	one, one can simply iterate until 10^5, while generating the other half algorithmicly.
 */




class Solution {
public:
	static vector<vector<string>> cache;
	static bool helper;

	int superpalindromesInRange(string left, string right) {
		LONG l = stoll(left), r = stoll(right);
		int low = min(9, (int)to_string((int)floor(sqrt(l))).size() );
		int hi = min(9, (int)to_string((int)floor(sqrt(r))).size());
		
		int res = 0;
		for (int len = low; len <= hi; ++len) {
			for (string& s : cache[len]) {
				LONG n = stoll(s);
				LONG n2 = n * n;
				if (isPalindrome(n2) && n2 >= l && n2 <= r) ++res;
			}
		}
		return res;
	}

	bool isPalindrome(LONG n) {
		string s = to_string(n);
		const int l = s.size();
		for (int i = 0; i < l / 2; ++i)
			if (s[i] != s[l - i - 1]) return false;
		return true;
	}
};




bool init() {
	Solution::cache.push_back({ "" });
	Solution::cache.push_back({ "0","1","2","3","4","5","6","7","8","9" });

	for (int places = 2; places < 10; ++places) {
		Solution::cache.push_back(vector<string>() );
		for (char d = '0'; d <= '9'; ++d) {
			for (string& s : Solution::cache[places-2]) {
				Solution::cache[places].push_back(d + s + d);
			}
		}
	}
	return true;
}
vector<vector<string>> Solution::cache = {};
bool Solution::helper = init();