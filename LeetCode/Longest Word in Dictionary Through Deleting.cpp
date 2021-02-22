#include <string>
#include <queue>
#include <vector>
using namespace std;

//	https://leetcode.com/problems/longest-word-in-dictionary-through-deleting/
/*
 * 	This is a String, sorting problem, or Queue, Trie-like idea problem.
 *
 * 	The real brute force way to solve this is to generate all the possible subsequences of string s
 * 	and check if that subsequence is in dictionary. Of course, this would not pass the test cases.
 *
 * 	-------------------------------------------------------------
 *
 * 	Instead of finding all subsequences, one might come up with a O(N^2) solution by checking each word
 * 	in dictionary. FOr each word in dictionary, iterate through s to see if the word is indeed a subsequence.
 * 	Actual time complexity is actually O(NM), N is number of words in dictionary, M is length of S, or average length
 * 	of the word, depends.
 *
 * 	Now, to make earlier terminations, one can sort the dictionary words first, so that we check the longest one first.
 * 	If same length, sort by lexicographically. However in the worst case, time complexity still doesn't change
 *
 * 	--------------------------------------------------------------
 *
 * 	One solution that derives from Trie concept is, since all are lowercase letters, we will have 26 buckets, containing
 * 	'progresses' of words in the dictionary. All the buckets will contain a Pair of <Word, position>. Each bucket represents
 * 	a character, from a to z, and it contains all the searches that need to be continued.
 *
 * 	Say we have dictionary word 'abe'. We are looking for 'a' first, so put the index and position 0 into the bucket 'a'.
 *  So, when iterating string s, if met 'a', then we take it out from bucket 'a', increment position, and put into next
 *  character bucket 'b'. If later we met 'b', then take it out, increment position, and put in bucket 'e'. If once again
 *  'e' is found, then we know whole word is found, only then we update the result.
 *
 *  Here we use O(N) space where N is number of words. Each word we only storing a pair of <word index, position>
 *  Time complexity however, is also O(NM) as above. For each char in string s, we potentially has to iterate through
 *  all the words in dictionary if all matches!
 */

class Solution {
public:
	string findLongestWord(string s, vector<string>& d) {
		const int len = d.size();
		queue<pair<int, int>> pending[26];
		string res = "";

		//	Initialize all the dictionary words
		for (int i = 0; i < len; ++i)
			pending[d[i][0] - 'a'].emplace(make_pair<>(i,0));
	
		//	Now iterate through the string s. All pendings will be updated
		for (char c : s) {
			auto& list = pending[c - 'a'];

			for (int i = list.size(); i > 0; --i) {
				auto pair = list.front(); list.pop();
				string& word = d[pair.first];
				if (++pair.second >= word.length()) {
					//	Update only if same length but lexicographically smaller, or longer length
					if ((word.length() == res.length() && word.compare(res) < 0) || word.length() > res.length())
						res = word;
				}
				//	Otherwise the word is not yet complete. Push it to respective pending
				else {
					pending[word[pair.second] - 'a'].push(pair);
				}
			}
		}
		return res;
	}
};