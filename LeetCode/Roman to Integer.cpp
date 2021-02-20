#include <unordered_map>
#include <string>
using namespace std;

//https://leetcode.com/problems/roman-to-integer/
/*
 * 	This is a HashMap, String problem.
 *
 * 	A roman numeral convert to integer is quite an easy task. For each of the roman characters,
 * 	simply get its respective value and add to our result variable. It can be done via HashMap
 *
 * 	One challenges faced is those special '4' and '9's like IV, IX, XL, XC, CD and CM, which are
 * 	4,9,40,90,400,900 respectively. How do we face this?
 *
 * 	We can actually check two characters at once to see if there is said pair existing in the string.
 * 	However, it can be quite tedious to implement.
 *
 * 	Instead, observe: Those IV, IX..., the front character is smaller than that of the one behind. Take
 * 	advantage of this characteristic!
 *
 * 	Keep a previous value variable, which tracks the value of the roman character in last iteration. Now,
 * 	if current value is larger than the previous one, that means it must be one of special characters!
 * 	Since previous is already added to result in previous iteration, now we subtract two times of that!
 * 	That's it! Solved
 */

class Solution {
public:

	static const unordered_map<char, int> val;

	int romanToInt(string s) {
		int prev = INT32_MAX;
		int sum = 0;

		for (const char c : s) {
			int v = val.at(c);
			sum += v;
			if (prev < v) sum -= 2 * prev;
			prev = v;
		}
		return sum;
	}
};

const unordered_map<char, int> Solution::val = {
	{'I', 1},
	{'V',5},
	{'X',10},
	{'L',50},
	{'C',100},
	{'D',500},
	{'M',1000}
};