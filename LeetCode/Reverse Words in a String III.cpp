#include <string>
#include <stack>
using namespace std;

//https://leetcode.com/problems/reverse-words-in-a-string-iii/
/*
 * This is a String, optinally Stack problem.
 *
 * Stack is known for its properties to reverse anything, including this case.
 * Traverse through string s, pushing non-space characters into the stack.
 * If we did encounter a space ' ', empty the stack's content into result string, and don't forget the space character too.
 *
 * Another way of dealing with this problem with better space optimization is to simply use two pointers, one pointing at
 * the start of a word, and one at the end of word. Reverse everything between the two pointers
 */


class Solution {
public:
    string reverseWords(string s) {
		string res = "";
		stack<char> stk;

		for (char c : s) {
			if (c != ' ') stk.push(c);
			else {
				while (!stk.empty()) {
					res += stk.top();
					stk.pop();
				}
				res += c;
			}
		}

		while (!stk.empty()) {
			res += stk.top();
			stk.pop();
		}

		return res;
    }


    string reverseWords2(string s) {
		const int len = s.length();
		string res = "";
		int l = 0, r = 0;

		while (l < len) {
			// Fix left pointer.
			while (l < len && s[l] == ' ') ++l;
			// Fix right pointer. It should point at ' ' or len+1 at the end.
			r = l + 1;
			while (r < len && s[r] != ' ') ++r;

			for (int i = r - 1; i >= l; --i) res += s[i];
			if (r < len) res += ' ';

			l = r + 1;
		}


		return res;
    }
};