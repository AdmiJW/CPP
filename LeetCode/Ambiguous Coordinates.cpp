#include <vector>
#include <string>
using namespace std;

//https://leetcode.com/problems/ambiguous-coordinates/
/*
 * 	This is a Brute Force, String problem.
 *
 * 	For initial string, remove parenthesis first. Then, try to partition the numbers into x and y value.
 *
 * 	Then, for the x and y values, try to insert decimal points and check if it is valid or not. Turns out,
 * 	the condition was:
 * 		>	For the whole number to be valid, it cannot pad with 0
 * 		>	For the form 0.xxx.., it cannot trailing with 0
 * 		>	For other cases like xx.xxx.., it cannot pad with 0, and not trail with 0
 *
 * 	Once both valid values are returned as a list, perform cartesian product (Combination).
 *
 *	Time complexity are considered as O(N^4)
 */

class Solution {
public:
	vector<string> ambiguousCoordinates(const string& s) {
		const int len = s.size();
		const string str = s.substr(1, len - 2);
		vector<string> res;
		for (int l = 1; l < len - 2; ++l)
			cartesianProduct(str.substr(0, l), str.substr(l), res);
		return res;
	}

	void cartesianProduct(const string& l, const string& r, vector<string>& res) {
		vector<string> lval = generatePossibleValues(l);
		vector<string> rval = generatePossibleValues(r);
		for (string& ls : lval)
			for (string& rs : rval)
				res.push_back("(" + ls + ", " + rs + ")");
	}

	vector<string> generatePossibleValues(const string& s) {
		const int len = s.size();
		vector<string> res;
		//	Full, no decimal.
		if (len == 1 || !(s[0] == '0')) res.push_back(s);
		//	x.xxx or 0.xxx. case. Must not trail with 0
		if (len >= 2 && !(s[len - 1] == '0')) res.push_back(s.substr(0, 1) + '.' + s.substr(1));
		//	Other cases: xx.xxx...
		//	Condition: Cannot start with '0'. Cannot trail with 0
		if (len >= 3 && !(s[0] == '0') && !(s[len - 1] == '0')) {
			for (int loc = 2; loc < len; ++loc)
				res.push_back(s.substr(0, loc) + '.' + s.substr(loc));
		}
		return res;
	}
};