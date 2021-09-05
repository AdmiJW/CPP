#include <string>
#include <algorithm>
using namespace std;

//https://leetcode.com/problems/orderly-queue/
/*
 * 	This is a String, Sorting problem which is HARD to obsevre the insight to solve it.
 *
 * 	If k == 1, what we could do is simply take the frontmost character and put it at the back. This
 * 	is essentially string rotation. Therefore for k = 1, we can brute force all rotation and determine
 * 	the lowest lexicographically one. This takes O(N^2) time, but there are better algorithms out there
 *
 *
 * 	However for k >= 2, what we could do is:
 * 		>	String rotation like in k = 1
 * 		>	Fix the first character and rotate the rest of string.
 *
 * 	What the second characteristic help us achieve, is the ability to BUBBLE SORT! We could sort the string
 * 	from backwards. See example:
 *
 * 		"BADC"
 *
 * 	1. We want the first character to be sorted, backwards (D). We could rotate the string until the 'D' is at
 * 		front.
 *
 * 		"DCBA"
 *
 *  2. We want the first two characters to be sorted, backwards (CD). Rotate until C is first.
 *  	"CBAD"
 *     Fix first character and rotate
 *      "CDBA"
 *
 *  3. We want "BCD" to be sorted. Since "CD" is already achieved, start by fixing B to first character
 *  	"BACD"
 *     Fix the 'B' and rotate the rest
 *     	"BCDA"
 *
 *  4. We want "ABCD" to be sorted. "BCD" is achieved, so what's left is simply rotation
 *  	"ABCD"
 */

class Solution {
public:

	string orderlyQueue(string s, int k) {
		// Bubble sort is achived by k>=2
		if (k > 1) {
			sort(s.begin(), s.end());
			return s;
		}
		// Otherwise, find rotation
		string res = s;
		for (int rot = 1; rot < s.length(); ++rot) {
			string r = s.substr(rot) + s.substr(0, rot);

			if (r.compare(res) < 0)
				res = r;
		}
		return res;
	}

};