#include <string>
using namespace std;

//https://leetcode.com/problems/break-a-palindrome/
/*
 * This is a greedy string problem - The changes we made are always optimal to the problem.
 *
 * First let's identify the base case - Any string of length 1 is always palindrome no matter how we change it.
 * In a palindrome string, changing any character EXCEPT FOR THE MIDDLE CHARACTER IN A ODD LENGTH PALINDROME will
 * always break the palindrome.
 * This is where we'll be greedy: Iterate through the string, if any character (except mid one) is not 'a', we can simply
 * change it to 'a' and solve the problem already.
 *
 * However, if the whole string is full of 'a', we have no choice but to change the last 'a' to 'b'
 */

class Solution {
public:
	string breakPalindrome(string palindrome) {
		const int len = palindrome.length();
		int mid = len / 2;
		// Edge case - Length 1 always palindrome
		if (len <= 1) return "";

		for (int i = 0; i < len; ++i) {
			// Ignore the middle character if this is odd. Changing middle char does not make it palindrome
			if (len % 2 != 0 && i == mid) continue;
			if (palindrome[i] == 'a') continue;
			
			// Located a non 'a' character. Change it to 'a' and job is done
			palindrome[i] = 'a';
			return palindrome;
			
		}
		// String full of 'a'. Change last 'a' to 'b'
		palindrome[len - 1] = 'b';
		return palindrome;
	}
};