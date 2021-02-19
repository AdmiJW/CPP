#include <string>
using namespace std;

///https://leetcode.com/problems/minimum-remove-to-make-valid-parentheses/
/*
 * 	This is a Stack / Two pointers solution.
 *
 * 	For each of the opening parenthesis that we meet, it would need a corresponding closing parenthesis to be valid. Otherwise,
 * 	that opening parenthesis need to be discarded.
 *
 * 	To use Stack, we push all the indexes of the '(' into the stack, and pop the top when see one ')'. If the stack is empty when
 * 	we see a ')', that means for a unmatched ')', so record that as well in some appriopriate data structure.
 *
 * 	-----------------------------
 *
 * 	Instead of using Stack, we can further reduce the space complexity.
 * 	Observe that for each opening parenthesis, we would want to be greedy and use the closest closing parenthesis to the right.
 * 	Next time another opening parenthesis is met, we would continue searching for the next closing parenthesis wihtout
 * 	repeating checking. This method utilizes two pointers.
 *
 * 	Keep track of how many valid closing parenthesis is used, so when we met ')', we know if we can put that closing parenthesis
 * 	or not.
 *
 * 	Time O(N) and space of O(1) if not consider stringBuilder as extra space.
 */

class Solution {
public:
	string minRemoveToMakeValid(string s) {
		const int len = s.length();
		string res;
		int explorer = 0;
		int closeCnt = 0;

		for (int i = 0; i < len; ++i) {
			char c = s[i];
			if (c == '(') {
				explorer = max(explorer, i) + 1;
				while (explorer < len && s[explorer] != ')')
					++explorer;
				if (explorer < len && s[explorer] == ')') {
					res += c;
					++closeCnt;
				}
			}
			else if (c == ')') {
				if (closeCnt <= 0) continue;
				res += c;
				--closeCnt;
			}
			else res += c;
		}
		return res;
	}
};