#include <string>
#include <array>
using namespace std;

//https://leetcode.com/problems/longest-substring-with-at-least-k-repeating-characters/

/*
 * 	This is a Sliding window / Divide & Conquer / Recursion problem
 *
 * 	Before we start off with approaches, we can think how we can know if the characters in the substring is
 * 	all with at least K frequency?
 * 	We could make a frequency table of 26 in size, and iterate it over every step. Can we do better?
 *
 * 	In addition with frequency table, we could have a counter called UNSOLVED. This unsolved will keep track of
 * 	how many characters in the substring is still below k frequency.
 *
 * 	Now, when we extend the substring by one character, if the frequency in table is first found to be 0, the
 * 	number of characters just increased, therefore unsolved ++. On the other hand, if the frequency found to be
 * 	K after adding, it is no longer below K, thus unsolved --.
 * 	The reverse goes for the same when removing a character
 *
 * 	At the end of each action, if the unsolved count is 0, we have a valid string, thus update the result
 * 	by using max function
 *
 * 	-----------------------------------------------------------------------------------
 *
 * 	For the brute force, we just try all possible substring - Try all starting points, and all ending points.
 * 	Using the above method, it can be made a bit faster by without having to iterate 26 times each time.
 *
 * 	------------------------------------------------------------------------------------
 *
 * 	This problem can be solved using Divide and Conquer by recursion method in O(26N) time.
 *
 * 	The intuition is this: Every recursion will return the length of the longest substring with at least K repeating
 * 	characters.
 *
 * 	On first pass, we first iterate through the string and find out the frequency counts of each character.
 * 	Then on the second pass, as soon as we detect one character which is below k, we immediately know that this
 * 	character will NOT be in the final substring no matter what. It is called a INVALID character or the seperator
 *  of substring.
 *
 * 	In this case, we will call upon 2 recursions, the very same function but on the
 * 		>	substring to left of this INVALID character
 * 		>	substring to right of this INVALID character
 * 	Then just return the maximum return value out of 2 of them
 *
 * 	If no such INVALID character is found, it means that the whole string is valid. Every character is over K
 * 	frequency therefore the string is of maximum length already.
 *
 * 	You might ask how is this O(26N)? Notice that we have at most 26 characters. Each recursion call will split
 * 	the string into two or mroe parts. However, no matter how split, the string can always combine back into 1 string
 * 	of length N.
 * 	Then, we have at most 26 characters, thus the deepmost recursion stack is only of 26 layer, therefore
 * 		O( 26 characters * N iteration each layer )
 *
 * 	----------------------------------------------------------------------------------
 *
 * 	Then we have the optimized sliding window with a ingenious idea - Using property that we have 26 unique
 * 	characters as CONSTANT
 *
 * 	First, count the number of unique characters in the string, say U. Then we know that in the solution, the
 * 	substring can possibly have 1 until U characters in it.
 *
 * 	Therefore, attempt each unique counts, which at most iterate 26 times only.
 * 	In each iteration, we will use a sliding window. When the sliding window has that fixed unqiue number of characters
 * 	of the iteration count, and have no unsolved characters (characters frequency all >= K), then we can update
 * 	the result
 *
 * 	The sliding window moves as so:
 * 		>	If unqiue character is below or equal to K, expand window by 1
 * 		>	Else, shrink the window.
 */

class Solution {
public:
	int longestSubstring(string s, int k) {
		const int len = s.length();
		int res = 0;

		for (int st = 0; st < len; st++) {
			int unsolved = 0;
			int freq[26] = {};

			for (int end = st; end < len; end++) {
				int idx = s[end] - 'a';

				freq[idx] ++;
				if (freq[idx] == 1) unsolved++;
				if (freq[idx] == k) unsolved--;

				if (unsolved == 0) res = max(res, end - st + 1);
			}
		}
		return res;
	}


	int longestSubstring2(string s, int k) {
		const int len = s.length();
		int freq[26] = {};

		for (char c : s)
			freq[c - 'a']++;

		for (int i = 0; i < len; i++) {
			char c = s[i] - 'a';
			if (freq[c] < k) {
				return max(
					longestSubstring2(s.substr(0,i), k),
					longestSubstring2(s.substr(i + 1, string::npos), k)
				);
			}
		}
		return len;
	}


	int longestSubstring3(string s, int k) {
		const int len = s.length();
		int res = 0;
		int uniques = 0;

		int count[26] = {};

		for (char c : s) {
			if (!count[c - 'a']) uniques++;
			count[c - 'a']++;
		}

		for (int u = 1; u <= uniques; u++) {
			int window[26] = {};
			int unsolved = 0;
			int unique = 0;
			int left = 0, right = 0;

			while (left < len) {
				if (unique <= u && right < len) {
					int idx = s[right++] - 'a';

					if (!window[idx]) {
						unique++;
						unsolved++;
					}
					window[idx]++;
					if (window[idx] == k) unsolved--;
				}
				else {
					int idx = s[left++] - 'a';

					if (window[idx] == k) unsolved++;
					window[idx] --;
					if (!window[idx]) {
						unique--;
						unsolved--;
					}
				}

				if (unique == u && !unsolved)
					res = max(res, right - left);
			}
		}
		return res >= k ? res : 0;
	}
};