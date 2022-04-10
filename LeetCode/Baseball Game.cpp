#include <vector>
#include <stack>
#include <string>
using namespace std;

//https://leetcode.com/problems/baseball-game/
/*
 * A straightforward stack problem, which simulates the exact behavior we are doing in the problem.
 *
 * C - Pop from the stack basically invalidates the previous score
 * D - Add a new integer which is double of previous score (peek)
 * + - Obtain last 2 integers from the stack, sum them up, and add the sum of the 2 into the stack
 * INT - Append to stack
 *
 * Lastly, pop all the elements from the stack and sum them up.
 */


class Solution {
public:
    int calPoints(vector<string>& ops) {
        stack<int> stk;

        for (auto& s : ops) {
            if (s == "D") stk.push(stk.top() * 2);
            else if (s == "C") stk.pop();
            else if (s == "+") {
                int prev = stk.top();
                stk.pop();
                int	score = prev + stk.top();
                stk.push(prev);
                stk.push(score);
            }
            else stk.push( stoi(s) );
        }

        int sum = 0;
        while (!stk.empty()) {
            sum += stk.top();
            stk.pop();
        }

        return sum;
    }
};