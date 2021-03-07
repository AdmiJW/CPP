#include <unordered_map>
#include <vector>
#include <string>
using namespace std;

//https://leetcode.com/problems/short-encoding-of-words/
/*
 * 	This is a Suffix / Trie problem
 *
 * 	Notice that every string s in the array of strings, we will try to traverse as far as we can go into the trie.
 *
 * 	The trie will be a suffix tree, due to the fact that if A is a suffix of B, like A = "le" and B = "apple", A
 * 	will not count towards the result count, due to it being inclusive in app"le"
 *
 *  Once we stop at one point where we can't continue due to non-existent trie node, or exhausted the string itself, it can
 * 	be reduced to following cases:
 *
 * 		>	String itself is exhausted. That means the string is entirely a suffix of another string. Do nothing
 * 		>	Ended at a node which don't have any child nodes. That means we will be simply extending the current string.
 * 			Eg: Trie contains "le" and we trying to insert "apple". In this case just add 3 to result, due to prior to
 * 				this, le# is already counted.
 *
 * 		>	Ended at a node which have child nodes. In that case the matched string is for entirely different string,
 * 			Eg: "idle" and we are trying to insert "apple". In this case, "apple" cannot be included in "idle", thus
 * 				we need to create a entirely new part for this string, resulting in
 * 				"idle#apple#
 */


class Node {
public:
	unordered_map<int, Node*> next;
};


class Solution {
public:
	int minimumLengthEncoding(vector<string>& words) {
		Node root;
		int res = 0;

		for (string& s : words) {
			int idx = s.length() - 1;
			Node* curr = &root;

			while (idx >= 0) {
				int ascii = s[idx] - 'a';
				if (!curr->next.count(ascii)) break;

				curr = curr->next[ascii];
				--idx;
			}

			if (idx >= 0) {
				//	Branched
				if (curr->next.size() > 0 || curr == &root)
					res += s.length() + 1;
				//	Non-branched - simply extend
				else
					res += idx + 1;

				//	Insert the rest of the string
				while (idx >= 0) {
					int ascii = s[idx] - 'a';
					curr->next[ascii] = new Node();
					curr = curr->next[ascii];
					--idx;
				}
			}
		}
		return res;
	}
};