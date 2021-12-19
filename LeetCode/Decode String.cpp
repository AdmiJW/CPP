#include <string>
#include <cctype>
using namespace std;

//https://leetcode.com/problems/decode-string/

/*
 * 	This is a Depth First Search / Stack problem
 *
 * 	A string may have several parts that have to be repeated. We essentially have to find out those parts, and
 * 	decode them first before joining back into the 'outer' string
 *
 * 	This makes us think about recursion. A recursive function can take in a string, perform its function to decode
 * 	it, as soon as it encounters a repetition part, call upon another recursion, then at last, return the decoded string
 *
 * 	First attempt, is when detected a digit, then it will go through the subsequent part of string to find the ending
 * 	bracket. Then, pass the substring enclosed into the recursion call to be decoded and returned as a string.
 * 	This approach does solve the problem, but in the worst case, when the brackets start very early and end at the tail
 * 	of the string, this solution will iterate over the string repeatedly and result in almost O(N^2) time.
 *
 * 	Is there a one pass solution?
 *
 * 	---------------------------------------------------------------------------------------
 *
 * 	Actually, we don't have to find the ending bracket at all. As soon as we hit a opening bracket, we go deep one level
 * 	into recursion, and when we encounter a ending bracket, we should have been at the same level as the opening bracket!
 *
 * 	Therefore, having a global index pointer ensures that we are only iterating only one pass through the string.
 * 	When we encounter a opening bracket, go deep one level of recursion which will decode the string anew. When it encounters
 * 	a ending bracket, it means the decoding of equivalent level is done, and it should return the decoded string up one level
 * 	to be processed.
 *
 * 	The entire process relies on the global index pointer so that it is ensured one pass solution
 *
 * 	----------------------------------------------------------------------------------------
 *
 * 	How to implement it iteratively? In the recursive solution, we essentially store the last traced string state, and
 * 	start anew when we encounter a opening bracket. When it is done, we return the decoded string, and continue with the
 * 	last traced string state and append the decoded string to it.
 *
 * 	Same can be done using Stack to store the last traced string state. When we encounter a opening bracket, we store the
 * 	current traced string into Stack, then create a new string to start the decoding process of inner string.
 * 	Once we encounter the ending bracket, we know the inner string is done decoded, so we pop out the upper traced string
 * 	from stack, and append the decoded result to it.
 */




class Solution {
public:
	// class variable 'pointer' to maintain pointer state across recursion calls
	int pointer = 0;

	// Decodes and return the string starting at the class variable 'pointer'
	string decodeString(string s) {
		string res = "";

		while (pointer < s.length()) {
			// Case 1 - Alphabet ==> Just append to the result and move on
			if (isalpha(s[pointer]))
				res += s[pointer];
			// Case 2 - Digit ==> Consume all digits, and what follows is a [. Consume [ and recurse to obtain nested string.
			else if (isdigit(s[pointer])) {
				// Consume digits
				int repeat = 0;
				while (isdigit(s[pointer]))
					repeat = (repeat * 10) + (s[pointer++] - '0');
				// Consume [
				++pointer;
				
				// Recursion
				string nested = decodeString(s);
				// Append the nested string N times
				for (int i = 0; i < repeat; ++i)
					res += nested;
			}
			// Case 3 - Ending bracket ]. Return res immediately
			else return res;

			++pointer;
		}
		return res;
	}
};