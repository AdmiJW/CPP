#include <vector>
#include <string>
using namespace std;

//https://leetcode.com/problems/check-if-two-string-arrays-are-equivalent/
/*
 * 	This is a String, which is an Array problem, since strings are essentially character arrays
 *
 * 	The Brute force but workable way is to simply append all the strings. If the end result are equal then yes.
 *
 * 	--------------------------------
 *
 * 	However the above solution is space consuming, since
 * 		>	Strings are immutable. Each string is a instance of its own. Appending causes new instance to be created
 * 		>	We have to store 2 new strings, which is already exist in the parameter passed in
 *
 * 	To check whether two strings are equal or not, we just have to ensure each character equals, and is of same length
 * 	We can use 2 pointers technique in this one
 * 	Since it is an array of strings, think of it as 2D jagged array. Index i points to a string, index j points to a
 * 	character in the string.
 *
 * 	In this sense, we need 4 pointers. 2 pointing to strings in word1 and word2 respectively, another 2 pointing to
 * 	character in the string pointed by the prior two pointers.
 *
 * 	Each iteration, check if the character pointers are out of range. If yes, proceed the string pointer and reset char
 * 	pointer to 0.
 *
 * 	Also check for string pointer. If out of range, check if other one does as well.
 * 	>	If Yes, it means all the characters matched and we reach the end of both strings. Return true
 * 	>	Otherwise one string ended earlier while other has not. Return false.
 *
 * 	Check if the characters pointed are equal. If not, immediately return false.
 */

class Solution {
public:

	//	Brute force-y way: Using StringBuilder to append Strings and lastly compare
	bool arrayStringsAreEqual(vector<string>& word1, vector<string>& word2) {
		string s1; 
		s1.reserve(1000);
		string s2;
		s2.reserve(1000);

		for (string& s : word1) s1.append(s);
		for (string& s : word2) s2.append(s);

		return !s1.compare(s2);
	}

	//	Optimize way: Using position pointers to prevent O(N) space complexity
	bool arrayStringsAreEqual2(vector<string>& word1, vector<string>& word2) {
		const int len1 = word1.size();
		const int len2 = word2.size();

		unsigned int str1 = 0;
		unsigned int str2 = 0;
		unsigned int char1 = 0;
		unsigned int char2 = 0;

		while (1) {
			//	End of the current string in word1 array
			if (char1 >= word1[str1].size()) {
				++str1;
				char1 = 0;
			}
			//	End of the current string in word2 array
			if (char2 >= word2[str2].length()) {
				++str2;
				char2 = 0;
			}

			//	If we are at end of word1 array, check if we are also in end of word2 array
			if (str1 == len1) return str2 == len2;
			//	Since the prior already false, then word1 hasn't finished if this is the case. Return false
			if (str2 == len2) return false;

			//	Character not equal
			if (word1[str1][char1] != word2[str2][char2]) return false;
			
			//	Proceed the pointers
			++char1;
			++char2;
		}
	}

};