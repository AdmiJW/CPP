#include <string>
#include <unordered_map>
using namespace std;

//https://leetcode.com/problems/determine-if-two-strings-are-close/

/*
 * 	My proposed solution is as follows:
 *
 * 	Let's think what each of the operation actually mean - Given each operation can be performed infinite times
 *
 *	#1 - You are allowed to swap characters
 *		(This means the position of the characters doesn't matter. As long as the frequency of each unique character
 *		in both string matches, there must be a way to swap until match)
 *
 *	#2 - You can mass swap between two unique characters. Eg: aaaabb -> bbaaaa
 *		(This means the frequency of one unique character can be swapped with another frequency of another
 *		unique character!
 *		In example above, { a: 4, b: 2 } got swapped to { a: 2, b: 4 }
 *
 *	With both things in mind, we can construct some conditions:
 *
 *	>	If there is a non existent character that is in str2, but not in str1, its impossible!
 *	>	Since frequency of unique characters can swap, the frequency of frequency (YES) matters. Character now
 *		doesn't matter
 *	>	if both strings has the same frequency of frequency pattern, then yes it can be said to be close string!
 *		Return true
 */


class Solution {
	
	bool closeStrings(string word1, string word2) {
		if (word1.length() != word2.length()) return false;

		//	Frequency of characters
		int freq1[26] = {};
		int freq2[26] = {};

		//	Filling in frequency of characters
		for (char c : word1) ++freq1[c - 'a'];
		for (char c : word2) {
			if (!freq1[c - 'a']) return false;	//	Non existant character in str1 found in str2
			++freq2[c - 'a'];
		}

		//	Frequency of frequencies
		unordered_map<int, int> freqFreq1;
		unordered_map<int, int> freqFreq2;

		for (int i = 0; i < 26; ++i) {
			if (freq1[i]) ++freqFreq1[ freq1[i] ];
			if (freq2[i]) ++freqFreq2[ freq2[i] ]; 
		}

		//	Frequencies don't match, then impossible
		for (auto i : freqFreq1) {
			if (!freqFreq2.count(i.first) || freqFreq2[i] != i.second)
				return false;
		}

		return true;
	}

};