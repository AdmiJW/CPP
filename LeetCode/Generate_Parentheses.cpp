#include <vector>
#include <string>
using namespace std;

//https://leetcode.com/problems/generate-parentheses/submissions/
/*
 * 	This is a Backtracking problem / DP problem
 *
 * 	My initial solution is that, given N parentheses, and know that a valid string must start with a opening
 * 	bracket, we could break it down in terms of subproblems. See:
 *
 * 	At the first enclosing bracket, inside the bracket could be a parentheses string consisting from 0 to N-1
 * 	parentheses. Also, after the first enclosing bracket also can be parentheses string, but since some parentheses
 * 	are used up in enclosing bracket, the number of parentheses outside is determined by number of parentheses inside
 * 	the first enclosing bracket.
 *
 *  If confused, see example N=3
 *  Start by opening the first enclosing bracket
 *  	>	(    )
 *
 *  Inside the bracket could be parentheses string of size 0 to N-1. Let P(x) be parentheses string consisting of x parentheses
 *  	>	( P(0) ) P(2)
 *  	>	( P(1) ) P(1)
 *  	>	( P(2) ) P(0)
 *
 *  Therefore in my solution, I just start bottom up, generating all P(x) up until P(N).
 *
 *  ===================================
 *
 *  The official solution is, for my parentheses string, I always had to make a decision to put a opening bracket or a closing
 *  bracket (given after placement, the string will not end up invalid).
 *
 *  This is ok to be done via recursion. Record the number of opening bracket and closing bracket placed so far, and the parentheses
 *  is done when the length of string is equal to 2*N.
 */

class Solution {
public:
	vector<string> generateParenthesis(int n) {
		vector<vector<string>> res(n + 1, vector<string>());
		res[0].push_back("");

        //	To generate every N, it has a recurrence relationship where:
        //	( <from 0 to N-1 parentheses> ) <leftover parentheses>
        for (int p = 1; p <= n; ++p) {
            for (int insideParentheses = 0; insideParentheses < p; ++insideParentheses) {
                int outsideParentheses = p - 1 - insideParentheses;

                for (string& inside : res[insideParentheses])
                    for (string& outside : res[outsideParentheses])
                        res[p].push_back("(" + inside + ")" + outside);
            }
        }
        return res[n];
	}





	//	Backtracking solution (Faster)
	vector<string> generateParenthesis2(int n) {
		vector<string> res;
		string sb = "";
		recurse(n, sb, 0, 0, res);
		return res;
	}

	void recurse(int n, string& s, int opened, int closed, vector<string>& res) {
		if (s.length() == n * 2) {
			res.push_back(s);
			return;
		}

		//	Tries to put a opening bracket
		if (opened < n) {
			s += '(';
			recurse(n, s, opened + 1, closed, res);
			s.pop_back();
		}
		//	Tries to put a closing bracket
		if (opened > closed) {
			s += ')';
			recurse(n, s, opened, closed + 1, res);
			s.pop_back();
		}
	}
};
