#include <stack>
#include <string>
using namespace std;


//https://leetcode.com/problems/basic-calculator/
/*
 * This is a stack problem. (I have to look at solution to solve. I have to)
 *
 *  There are 5 cases we need to handle (Ignore the spaces!):
 *  Imagine we have an expression without parenthesis. We just need to solve it left to right using 3 variables:
 *  	- res: Result of the expression so far
 *  	- curr: Current number. Used to extract number with multiple digits
 *  	- sign: '+' or '-' can be represented as 1 or -1, which is simply multiplied.
 *
 *  For each character c,
 *  	if c is digit, simply add to curr via formula
 * 		 	curr = curr * 10 + c - '0';
 * 		if c is a plus sign or minus sign, it means the previous number is finished, and we need to see what is the
 *  	previous sign, recorded in the sign variable.
 *  		res += curr * sign;
 *  	Then, depending on character is plus or minus, set sign to 1 or -1.
 *
 *  However, now we have parenthesis. Only the content in parenthesis is evaluated first, then we'll combine
 *  the result outside the parenthesis. We have to 'Go into' the parenthesis.
 *  This is where we'll save the content outside of parenthesis into the Stack first, to be popped later.
 *
 *  If c is '(', save content into stack:
 *  	- Save the result so far into stack
 *  	- Also save the sign BEFORE the parenthesis into the stack, so we'll handle something like -(5+2+3)
 *  	- Reset res to 0, sign to 1.
 *
 *  Else c is ')', then combine contents
 *  	- First, ')' indicates end of previous number. So we do res += curr * sign; first, and reset curr = 0;
 *  	- Combine results ('Jump out' of the parenthesis).
 *  		res = stack.pop() * res + stack.pop();
 *  				^					^
 *  			[ Sign ]			[ Result outside parenthesis ]
 *
 */


class Solution {
public:
	int calculate(string s) {
		stack<int> stack;
		int res = 0;
		int curr = 0;
		int sign = 1;

		for (char c : s) {
			// Case 1: Digit
			if (c >= '0' && c <= '9') {
				curr = curr * 10 + (c - '0');
			}
			// Case 2: '+' sign
			else if (c == '+') {
				res += curr * sign;
				curr = 0;
				sign = 1;
			}
			// Case 3: '-' sign
			else if (c == '-') {
				res += curr * sign;
				curr = 0;
				sign = -1;
			}
			// Case 4: '(' sign
			else if (c == '(') {
				stack.push(res);
				stack.push(sign);
				res = 0;
				sign = 1;
			}
			// Case 5: ')' sign
			else if (c == ')') {
				res += curr * sign;
				curr = 0;
				
				int sign = stack.top(); stack.pop();
				int prev_res = stack.top(); stack.pop();

				res = sign * res + prev_res;
			}
		}
		// The final number haven't been handled yet
		res += curr * sign;
		return res;
	}
};