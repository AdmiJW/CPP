#include <string>
#include <stack>

using namespace std;

//https://leetcode.com/problems/score-of-parentheses/
/*
 * 	One idea about parenthesis is, it can be represented with Tree Data structures. The parent parenthesis can enclose
 * 	other parentheses. In this question, each parentheses score will be sum of child parentheses multiplied by 2, except the
 * 	base case ().
 * 	Dealing with trees, we may have to use recursion. Each recursion will find out the score of inner parentheses. This is the
 * 	idea, and is not the optimal solution
 *
 * 	---------------------------------------------
 *
 * 	Each parentheses have a stack associated with it. We need to record it, and what's better at that job than Stack?
 * 	Initially we push a 0 into the stack. That bottom 0 will be the final score as we keep adding scores to it.
 *
 * 	Now, everytime we see a (, we push a new 0 into the stack. If otherwise it is ), then we know the top of the stack
 * 	(latest opening parentheses) is closed. Pop it out, multiply by 2, and see if it is base case (), then make it 1.
 * 	Now, the top of stack will have it scores added by the above calculation. This is how the Stack will work
 *
 * 	Eg: (())
 *
 * 	First char: Stack [0,0]
 * 	Second char: Stack [0,0,0]
 * 	Third char: Stack [0,1] as top 0 popped, *2, made 1, added to top of stack
 * 	Fourth char: Stack [2] as top 1 popped, *2 become 2, added to top of stack
 *
 *	--------------------------------------------
 *
 *	Observe:
 *		() has a score of 1.
 *		(A) has score depending on the core. The core keeps getting multiplied by 2 every outer layer
 *
 *	So, we count how many layers we are getting into. Once we detect a core, only we add the corresponding score to the
 *	result!
 *
 *	Eg: (()(()))
 *
 *		There are 2 cores - ( (THIS) ( (THIS) ) )
 *
 *	The first 'THIS' is depth 2, so it has score of 2^1 = 2
 *	The second 'THIS' is depth 3, so it has score of 2^2 = 4
 *	Total score is then 2+4 = 6
 *
 *	Fast way is use left shift, equivalent to multiply 2
 */

class Solution {
public:
	int scoreOfParentheses(string s) {
		stack<int> scores;
		scores.push(0);

		for (char c : s) {
			if (c == '(')
				scores.push(0);
			else {
				int score = scores.top(); scores.pop();
				scores.top() += max(1, score * 2);
			}
		}
		return scores.top();
	}



	int scoreOfParentheses2(string s) {
		int res = 0, layer = 0;

		for (int i = 0; i < s.length(); ++i) {
			if (s[i] == '(') ++layer;
			else {
				--layer;
				if (s[i - 1] == '(')		//	Core
					res += 1 << layer;
			}
		}
		return res;
	}
};