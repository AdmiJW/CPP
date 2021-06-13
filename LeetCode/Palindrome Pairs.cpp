#include <vector>
#include <string>
using namespace std;

//https://leetcode.com/problems/palindrome-pairs/
/*
 * 	This is a Trie problem.
 *
 * 	A palindrome has some prefix p, and suffix s that is reflection of prefix p. How can we find out pairs of palindromes
 * 	from an array of string?
 *
 * 	For Brute force, it is to basically select each string, then in nested loop, iterate all strings and check whether their
 * 	concatenated string is a palindrome or not. Time taken is O(N^2 * K) where N is number of strings, K is avg length of strings
 *
 * 	However, possible candidates of second string can majority be eliminated if we compare their suffix with the selected
 * 	string's prefix. Eg: For selected string "abc", we only consider:
 * 		>	Exact string ""
 * 		>	Exact string "a" (Although it is not palindrome, cases like "aaa" and "a" needs checking)
 * 		>	Exact string "ba"
 * 		>	Exact string "cba"
 * 		>	Any other string that ends with "cba"
 *
 * 	For this job, a Trie structure is suitable. We'll construct a SUFFIX tree, and if the particular node represents a
 * 	complete word, instead of storing the string, we store the index of that word inside the array.
 */

class TrieNode {
public:
	TrieNode* next[26] = {};
	int index = -1;
	~TrieNode() {
		for (TrieNode* n : next)
			if (n) delete n;
	}
};


class Solution {
public:
	vector<vector<int>> palindromePairs(vector<string>& words) {
		const int len = words.size();
		vector<vector<int>> res;
		TrieNode root;

		//	Construct the TrieNode first
		for (int i = 0; i < len; ++i) {
			string& s = words[i];
			TrieNode* curr = &root;
			for (int idx = s.length() - 1; idx >= 0; --idx) {
				int c = s[idx] - 'a';
				if (!(curr->next[c])) curr->next[c] = new TrieNode();
				curr = curr->next[c];
			}
			curr->index = i;
		}

		//	For each of the words, find the possible palindrome strings from the Trie
		for (int i = 0; i < len; ++i) {
			search(words, i, &root, 0, res);
		}
		return res;
	}


	void search(vector<string>& words, int left, TrieNode* right, int leftIdx, vector<vector<int>>& res) {
		if (right->index != -1 && left != right->index) {
			string concat = words[left] + words[right->index];
			if (isPalindrome(concat))
				res.push_back({ left, right->index });
		}
			

		//	Left string haven't get exhausted yet
		if (words[left].length() > leftIdx) {
			int c = words[left][leftIdx] - 'a';
			if (!(right->next[c])) return;

			search(words, left, right->next[c], leftIdx + 1, res);
		}
		//	Left string is exhausted. Search for any word possible
		else {
			for (TrieNode* t : right->next)
				if (t) search(words, left, t, leftIdx, res);
		}
	}


	bool isPalindrome(string& s) {
		int l = 0, r = s.length() - 1;
		while (l < r) {
			if (s[l] != s[r]) return false;
			++l; --r;
		}
		return true;
	}
};