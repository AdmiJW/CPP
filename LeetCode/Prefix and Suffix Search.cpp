#include <string>
#include <vector>
using namespace std;

//https://leetcode.com/problems/prefix-and-suffix-search/
/*
 * 	This is a advanced Trie problem.
 *
 * 	For searching of words, Trie might be a good solution especially if our dictionary consists a lot of repeating
 * 	prefixes and suffixes, since they will be sharing the same data.
 *
 *
 * 	---------------------------------------------
 *
 * 	If thinking about tries, we might have an idea of using 2 tries in this problem. One for prefix, and one for
 * 	suffix. Once we query, we obtain two set of possible indices for both prefix and suffix.
 * 	Then, to get a set of VALID indices, intersect the two sets, and return the maximum of them.
 *
 * 	However, this solution results in time limit exceeded, due to the size of sets may be large
 *
 * 	-----------------------------------------------
 *
 * 	Another suggested idea is to create a Pair Trie. Essentially, instead of travelling in the trie for one character
 * 	at a time, we query for prefix and suffix. Eg:
 * 		"Apple",
 * 	Then when creating trie, we put(a,e), then (p,l), then (p,p), then (l,p), then (e,a)
 *
 * 	This is good for equal length queries, like ("ap", "le"). However, we have to also consider vary length
 * 	queries, like ("app", "e")
 *
 * 	For this, we need to increase complexity. For each possible prefixes, generate all wildcard suffixes. Like
 * 	prefix = "ap", we need to consider
 * 			("ap, "apple")
 * 			("ap, "#pple")
 * 			("ap, "##ple")
 * 			("ap, "###le")
 * 			("ap, "####e") where # means missing suffixes, a wildcard
 * 	The same goes for missing prefixes. In the end, creating the trie is not so easy after all!
 *
 * 	-------------------------------------------------------
 *
 * 	A more easier to implement solution, is to put words in trie in <suffixes><sep><word> form.
 * 	Eg: "apple"
 * 			put "e{apple"
 * 				"le{apple"
 * 				"ple{apple"
 * 				"pple{apple"
 * 				"apple{apple"
 *
 * 	When querying like ("app", "le"), we query the trie in form of <suffix><sep><prefix>, so in this case,
 * 	query "le{app"
 * 	As we can see, the example case 2 will get queries, (but not until finish).
 * 	Since at the end it is a valid node, we can easily retrieve the index!
 *
 * 	As for index assigning, we always put the latest index, since the index is always increasing, it remains valid
 * 	if we overwrite the previous recorded index!
 */

struct TrieNode {
	//	Index 27 for special separator
	vector<TrieNode*> next = vector<TrieNode*>(27, nullptr);
	int idx = -1;

	~TrieNode() {
		for (auto n : next)
			if (n) delete n;
	}
};


class WordFilter {
public:
	TrieNode* trie = new TrieNode;

	WordFilter(vector<string>& words) {
		//	Create Trie
		for (int i = 0; i < words.size(); ++i) {
			//	For each possible suffix, insert <suf>#<word> into trie
			string& s = words[i];
			for (int e = s.length() - 1; e >= 0; --e) {
				TrieNode* t = trie;
				//	Suffix
				for (int suf = e; suf < s.length(); ++suf) {
					int c = s[suf] - 'a';
					if (!t->next[c]) t->next[c] = new TrieNode;
					t = t->next[c];
				}
				//	Separator
				if (!t->next[26]) t->next[26] = new TrieNode;
				t = t->next[26];
				//	Prefix
				for (char c : s) {
					if (!t->next[c - 'a']) t->next[c - 'a'] = new TrieNode;
					t = t->next[c - 'a'];
					t->idx = i;
				}
			}
		}
	}

	int f(string prefix, string suffix) {
		TrieNode* t = trie;
		//	Use { as separator because { is after 'z'
		string query = suffix + '{' + prefix;

		for (char c : query) {
			if (!t->next[c - 'a']) return -1;
			t = t->next[c - 'a'];
		}
		return t->idx;
	}
};