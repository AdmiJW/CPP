#include <string>
#include <vector>
using namespace std;

//https://leetcode.com/problems/shifting-letters/
/*
 * 	This is a string problem.
 *
 * 	For the shifts, notice it is actually a cycle. So if shift=26, it is same as shift=0.
 * 	If shift=27, then it is same as shift=1
 *
 * 	Also, it says that the number of times that character at i position needs to be shifted is
 * 	shift[i] + shift[i+1]... + shift[n].
 *  We could perform a backward prefix sum to aggregate the actual shift needed for character at position i.
 */

class Solution {
public:
    string shiftingLetters(string s, vector<int>& shifts) {
		const int len = s.size();
		// Combine shifts by prefix sum
		for (int i = len - 2; i >= 0; --i)
			shifts[i] = (shifts[i] + shifts[i + 1]) % 26;

		// Shifting characters
		for (int i = 0; i < len; ++i)
			s[i] = shift(s[i], shifts[i]);
		return s;
    }

	// This function assumes that the shifts is already in [0,25].
	char shift(char c, int shifts) {
		// Normalize character to 0-25, then shift, then handle overflow, then convert back to ASCII
		return (c - 'a' + shifts) % 26 + 'a';
	}
};