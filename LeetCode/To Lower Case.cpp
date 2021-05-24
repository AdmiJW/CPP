#include <string>
using namespace std;

//https://leetcode.com/problems/to-lower-case/
/*
 *	Each character is represented in ASCII, which is simply numbers
 *	
 *	From character 'A' to 'Z' is 65 to 90
 *	From character 'a' to 'z' is 97 to 122
 * 
 *	Check each character is between 'A' to 'Z'. If yes, add the difference of 'a' - 'A' to convert it to uppercase.
 *	Then append to result string
 */

class Solution {
public:
	string toLowerCase(string s) {
		string res = "";
		for (char c : s) {
			if (c >= 'A' && c <= 'Z')
				res += c + ('a' - 'A');
			else res += c;
		}
		return res;
	}
};