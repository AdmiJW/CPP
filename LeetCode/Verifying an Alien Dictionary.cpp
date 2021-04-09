#include <string>
#include <vector>
using namespace std;

//https://leetcode.com/problems/verifying-an-alien-dictionary/
/*
 * 	This is a HashMap String problem
 *
 * 	If the lexicographical order of alphabets are messed up, we can simply create a map to
 * 	map alien alphabet order back to normal alphabet
 *
 * 	Say we have '123' as normal order and '213' as alien order, then we can:
 * 	>	{ 1->2, 2->1, 3->3 }			--> 2 is lexicographicall smallest, followed by 1 then 3
 *
 *
 * 	Also, to ensure an array is sorted, we simply need to compare each element with its previous element to ensure
 * 	current element is greater than previous. This builds up to global conclusion that the array is indeed sorted.
 *
 * 	For this problem, we have the choice:
 *	For each 2 pair of words curr and prev:
 *
 *		>	Compare characters that prev shall be lesser than curr. if match, compare length

	OR

		>	Build the words back into original alphabet, then use built in compareTo() function
 */

class Solution {
public:
	bool isAlienSorted(vector<string>& words, string order) {
		int idx[26];

		//	Index table. Maps characters to its lexicographical rank
		for (int i = 0; i < order.size(); ++i)
			idx[order[i] - 'a'] = i;

		for (int i = 1; i < words.size(); ++i) {
			string& curr = words[i], &prev = words[i - 1];

			if (!isGreater(prev, curr, idx)) return false;
		}
		return true;
	}

	bool isGreater(string& s1, string& s2, int idx[]) {
		for (int j = 0; j < min(s1.size(), s2.size()); ++j) {
			int c1 = s1[j] - 'a';
			int c2 = s2[j] - 'a';

			if (idx[c1] > idx[c2]) return false;	//	Previous str is lexicographically greater than current str
			if (idx[c1] < idx[c2]) return true;		//		Immediately, current str is lexicographically greater 
		}
		//	Strings match until whoever shorter. Compare length
		return s1.size() <= s2.size();
	}
};