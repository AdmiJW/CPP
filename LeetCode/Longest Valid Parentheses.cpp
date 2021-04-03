#include <stack>
#include <string>
#include <vector>
using namespace std;

//https://leetcode.com/problems/longest-valid-parentheses/
/*
 * 	This is a DP / Stack / Pure genius idea problem, HARD to come up with solution
 * 	Before anything, notice that
 * 		>	A valid substring must always be even lengthed. Because every ( must have corresponding )
 *
 * 	First and foremost, brute force solution is always available. For each even lengths, attempt iterate every possible start
 * 	indices. Within this length, we also need to check if it is valid or not by stack method.
 *
 * 	Time complexity for this is O(N^3), and may easily time limit exceeded.
 *
 * 	-------------------------------------------------------------------------------
 *
 * 	For dynamic programming is kind of hard to see. How can we use previous computations to determine the answer for current
 * 	state? What exactly is our previous computations?
 *
 * 	Turns out, we have a 1D DP array. At index i indicates the length of valid substring that MUST ends with character at i.
 * 	From this, if character at i is '(', then surely it is not a valid substring, so its DP value must be 0.
 *
 * 	On the other hand, what happens if it is ')'? Let's see:
 *
 * 	>	If the previous character (i-1) is '(', then the sequence goes like " ...() ". So we know it forms a valid subsequence
 * 		of size 2 alreeady. Can it connect to previous subsequence tho? We'll just check dp[i-2] for that!
 *
 * 	>	If the previous character (i-1) is ')', then the sequence goes like " ...)) ".
 * 		For this to be valid subsequence, there must be pattern like " ((...)) " in the string!
 *
 * 		This is quite problematic. First, let's check if the ')' at i-1 is a valid subsequence or not!
 * 		If it is, we can get the length of its valid subsequence, which in turns, means that I can check the character before
 * 		the previous valid subsequence, shown as X:
 * 				X(...))
 * 		Thus, if X is indeed '(', a valid subsequence is formed. HOWEVER, we need to consider if there a valid subsequence
 * 		can be connected before X or not. Therefore the formulae goes like
 *
 * 			dp[i] = 2 + dp[i-1] + dp[i - dp[i-1] - 2] 	IF AND ONLY IF 	previous ) forms valid subsequence, and character
 * 																		before previous valid subsequence is '('
 *
 *
 * 	-----------------------------------------------------------------------------------------------------
 *
 * 	For the Stack solution, the idea is:
 * 	>	Store the indices of the opening parentheses. Once we met a closing parentheses, we essentially consumed that last
 * 		opening parentheses. What's left shall be the index of the latest unmatched opening parentheses on the top of Stack.
 *
 * 	>	There will be a 'base case' in the stack, which is the bottom element, and it is not the index of opening parentheses.
 * 		It is the 'foundation' where to ensure if all opening parentheses is consumed, we still be able to determine the
 * 		length of the valid subsequence
 *
 * 	>	Once the stack goes empty (base case) is consumed, psuh the index of this closing parentheses as base case. This is
 * 		because more closing parenthese had occurred than opening parentheses, it's impossible to extend on previous substring
 * 		anymore
 *
 * 	-----------------------------------------------------------------------------------------------------------
 *
 * 	For two passes is simple once you understand it. Hard part is to figure this solution out
 *
 * 	>	The substring is valid only if no of '(' == no of ')'
 * 	>	Therefore count the parentheses. If ( == ), then record the length because every ( is matched with )
 * 	>	However, if ) becomes more than ( at some point, reset ( and ). This is because with extra ), previous substring
 * 		becomes impossible to extend further.
 *
 * 	>	Not only left to right, but also right to left as well. We need two passes. Consider the case ((). The answer will
 * 		be obtained only on R to L. Opposite case goes for ())
 */


class Solution {
public:

	//	DP solution
	int longestValidParentheses(string s) {
		vector<int>dp(s.size(), 0);
		int res = 0;

		for (int i = 1; i < s.size(); ++i) {
			//	If the character is '(', there is no way this forms a valid substring. So it will remain 0.
			if (s[i] == ')') {
				//	Previous character is actually opening bracket. Valid substring is [???]() where ??? is found out via dp[i-2]
				if (s[i - 1] == '(')
					dp[i] = 2 + dp[i >= 2 ? i - 2 : 0];
				//	Otherwise it is ...)). Check if previous ) is forming valid substring. If yes, and at the start of previous
				//	substring is also (, perfectly form a substring!
				//	No need to consider checking dp[i-1] = 0 because if it is 0, we end up checking the previous character again,
				//	which is character at index i - (0) - 1, the previous character, determined to be ')'.
				else if (i - dp[i - 1] > 0 && s[i - dp[i - 1] - 1] == '(') {
					dp[i] = 2 + dp[i - 1] + (i - dp[i - 1] - 2 >= 0 ? dp[i - dp[i - 1] - 2] : 0);
				}

				res = max(res, dp[i]);
			}
		}
		return res;
	}


	//	Stack solution, harder to think of
	int longestValidParentheses2(string s) {
		stack<int> stack;
		int res = 0;

		stack.push(-1);	//	Base case, so if '()', after the first ( is consumed, index 1 extends to index -1, giving length of 2
	
		for (int i = 0; i < s.size(); ++i) {
			char c = s[i];
			if (c == '(') stack.push(i);		//	Record index of the opening parentheses
			else {
				stack.pop();			//	Consume the last opening bracket to match current closing bracket
			
				if (stack.empty()) stack.push(i);		//	If we've consume the 'base case' where there's actually no closing
														//	bracket, clear the state. Push current index as the base 
				else res = max(res, i - stack.top());	//	Otherwise, the top of stack now is the index of opening bracket
														//	that haven't been matched. Difference of current index and top of 
														//	stack happens to be the length of valid parentheses
			}
		}
		return res;
	}



	//	Two pass, counting solution
	//	Use the fact that in a valid substring, number of opening and number of closing must be equal. Also,
	//	once closing exceeds opening, it is impossible to extend the currently tracked substring anymore
	//
	//	However, if we only do it in one way, cases like (() is not accounted for. Thus we need a reverse iteration as well
	int longestValidParentheses3(string s) {
		int opening = 0, closing = 0;
		int res = 0;

		//	If you want, you can combine 2 iterations into one!
		for (char c : s) {
			if (c == '(') ++opening;
			else ++closing;

			if (opening == closing) res = max(res, opening + closing);
			else if (closing > opening) opening = closing = 0;
		}

		opening = closing = 0;
		for (int i = s.length() - 1; i >= 0; --i) {
			char c = s[i];

			if (c == '(') ++opening;
			else ++closing;

			if (opening == closing) res = max(res, opening + closing);
			else if (opening > closing) opening = closing = 0;
		}
		return res;
	}

};