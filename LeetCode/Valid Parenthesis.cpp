#include <stack>
#include <vector>
#include <string>
using namespace std;

//https://leetcode.com/problems/valid-parentheses/
/*
 * 	This is a Stack problem.
 *
 * 	The stack will store the seen opening brackets (, { or [
 * 	The top of the stack will be the most recent seen opening bracket.
 *
 * 	If we encounter a closing bracket, it must be matching the most recent
 * 	opening bracket for the parenthesis string to be valid
 */


class Solution {
public:
	bool isValid(string s) {
		stack<char> stack;

		for (char c : s ) {
			if (c == '(' || c == '{' || c == '[')
				stack.push(c);
			else {
				if (stack.empty()) return false;
				char p = stack.top(); stack.pop();
				if (c == ')' && p != '('
					|| c == '}' && p != '{'
					|| c == ']' && p != '[')
					return false;
			}
		}
		return stack.empty();
	}
};