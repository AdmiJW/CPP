
#include <string>
#include <cctype>
#include <stack>
using namespace std;

//https://leetcode.com/problems/basic-calculator-ii/
/*
 *	This is a String Manipulation / Stack Problem
 *
 * 	Given an expression of +-/* and without parenthesis (All operations same layer), how would you calculate
 * 	final answer?
 *
 * 	One intuition is to do a two pass iteration. On the first pass, we reduce the multiply and division operations
 * 	into one single value, therefore the whole equation becomes only + and - only, which is simple to evaluate
 * 	in the second iteration.
 *
 * 	---------------------------------------------------------------------------------------
 *
 * 	With the Stack solution which is similar in a fashion to two pass string solution, we must notice two things:
 * 		>	When a + or - sign is met, the second operand may be a multiplication or division, which is of
 * 			higher precedence and be evaluated first. Therefore the first operand must be stored first and
 * 			be taken out to calculate once the second operand side is evaluated.
 *
 * 		>	When a * or / sign is met, we can immediately evaluate using first and second operand, since no
 * 			parenthesis exists.
 *
 * 	THe proposed solution is we store the OPERATOR and OPERANDS that we met before, keeping track of current operand
 * 	,and once we met the next operator or hit the end of string, we know we already have the previous and tracked
 * 	operand before this newest operator. Now, what will we do on the past 2 operands?
 *
 * 			Eg: 		2 + 5 * ...
 * 							  ^
 * 			We will hit this. We know past operator is + and past operand is 2, current operand is 5
 *
 *
 * 		>	+ and - : Since the next operand may be higher precedence of * or /, we therefore store the current tracked
 * 			operand, and continue. Note that -x is equivalent to +(-x) thus push -x into Stack instead
 *
 * 		>	* and / : Immediately perform the operation of two past operands together, push result back into
 * 			Stack, then continue with next operand
 *
 * 	In the end, the Stack that we store operands on are the ones that we need to sum it up. Return the sum of Stack
 *
 * 	===============================================================================================
 *
 * 	Notice the pattern that the Stack may be redundant after all. With one extra variable, we can store the sum
 *	of the stack easily.
 *
 *	Therefore we will basically have 3 variables:
 *
 *			Res		Prev	Curr
 *			( )		( )		( )
 *
 *	Prev represents the top of Stack, and Res is the sum of all elements underneath the top of Stack.
 *	Therefore the algorithm:
 *
 *		>	+ and - : The previous operand is guaranteed safe from multiplication and division. Sum into Res
 *			and put current tracked number into Prev
 *
 *		>	* and / : Take prev and current tracked number to multiply / divide. Then put back into prev
 *
 *
 *	At the end, return Res + Prev;
*/

class Solution {
public:
	int calculate(string s) {
		int len = s.size();
		int token = 0;
		string sb = "";

		for (int i = 0; i < len; i++) {
			char c = s[i];

			if (c == ' ') continue;

			if (isdigit(c))
				token = token * 10 + c - '0';
			else if (c == '*' || c == '/') {
				int token2 = 0;

				while (++i < len) {
					char n2 = s[i];
					if (n2 == ' ') continue;
					else if (isdigit(n2)) token2 = token2 * 10 + n2 - '0';
					else break;
				}
				i--;

				if (c == '*') token *= token2;
				else token /= token2;
			}
			else {
				sb += to_string(token);
				sb += c;
				token = 0;
			}
		}
		sb.append(to_string(token));

		len = sb.length();
		int res = 0;

		for (int i = 0; i < len; i++) {
			char c = sb[i];

			if (isdigit(c)) {
				res = res * 10 + c - '0';
			}
			else {
				int operand2 = 0;

				while (++i < len && isdigit(sb[i]))
					operand2 = operand2 * 10 + sb[i] - '0';

				i--;

				if (c == '+') res += operand2;
				else res -= operand2;
			}
		}
		return res;
	}



	int calculate2(string s) {
		stack<int> stack;
		const int len = s.length();
		int curr = 0;
		char currOperand = '+';

		for (int i = 0; i < len; i++) {
			char c = s[i];

			if (isdigit(c)) {
				curr = curr * 10 + (c - '0');
			}
			if (!isdigit(c) && !(c == ' ') || i == len - 1) {
				if (currOperand == '+') stack.push(curr);
				else if (currOperand == '-') stack.push(-curr);
				else {
					int top = stack.top();
					stack.pop();
					if (currOperand == '*') stack.push(top * curr);
					else if (currOperand == '/') stack.push(top / curr);
				}

				currOperand = c;
				curr = 0;
			}
		}

		int res = 0;
		while (!stack.empty()) {
			res += stack.top();
			stack.pop();
		}
		return res;
	}


	int calculate3(string s) {
		int res = 0;
		int prev = 0;
		const int len = s.length();
		int curr = 0;
		char currOperand = '+';

		for (int i = 0; i < len; i++) {
			char c = s[i];

			if (isdigit(c)) {
				curr = curr * 10 + (c - '0');
			}
			if (!isdigit(c) && !(c == ' ') || i == len - 1) {
				if (currOperand == '+') {
					res += prev;
					prev = curr;
				}
				else if (currOperand == '-') {
					res += prev;
					prev = -curr;
				}
				else if (currOperand == '*') prev *= curr;
				else prev /= curr;

				currOperand = c;
				curr = 0;
			}
		}

		return res + prev;
	}
};