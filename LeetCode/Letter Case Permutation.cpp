#include <vector>
#include <list>
#include <string>
#include <cctype>
using namespace std;

//https://leetcode.com/problems/letter-case-permutation/
/*
 * 	This is obviously a backtracking problem. No other way around it.
 *
 * 	For each character, if it is digit, it only has 1 permutation so push it in stringbuilder, and continue recursion
 * 	into next character
 * 	Otherwise if it is a alphabet, it can be uppercase or lowercase. Thus, first append it uppercase, recurse into it,
 * 	then replace it with lowercase, recurse into it, and lastly, don't forget to delete the character since the upper
 * 	recursin call may also be alphabet and need to put uppercase and lowercase
 *
 * 	------------------------------------------
 *
 * 	Notice the repeated computations. We could actually generate permutations using more space. This way, each character
 * 	we need to iterate through the possible permutations, and push all current character's variation into it
 * 	A Linked List or Deque is perfect for this job: Removing from front, adding to back - Exactly queue!
 */

class Solution {
public:
	vector<string> letterCasePermutation(string S) {
		vector<string> res;
		string s;
		generate(S, 0, s, res);
		return res;
	}

	void generate(string& s, int index, string& sb, vector<string>& res) {
		if (index > s.length()) res.emplace_back(sb);
		else {
			char c = s[index];
			if (isalpha(c)) {
				sb += tolower(c);
				generate(s, index + 1, sb, res);
				sb[index] = toupper(c);
				generate(s, index + 1, sb, res);
				sb.pop_back();
			}
			else {
				sb += c;
				generate(s, index + 1, sb, res);
				sb.pop_back();
			}
		}
	}





	vector<string> letterCasePermutation2(string S) {
		if (!S.length()) return vector<string>();
		list<string> queue;
		queue.emplace_back("");

		for (char c : S) {
			if (isalpha(c)) {
				for (int i = queue.size(); i > 0; --i) {
					string s = queue.front(); queue.pop_front();
					queue.emplace_back(s + (char)tolower(c));
					queue.emplace_back(s + (char)toupper(c));
				}
			}
			else {
				for (int i = queue.size(); i > 0; --i) {
					string s = queue.front(); queue.pop_front();
					queue.emplace_back(s + c);
				}
			}
		}

		return vector<string>(queue.begin(), queue.end());
	}
};