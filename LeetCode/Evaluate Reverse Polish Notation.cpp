#include <string>
#include <stack>

#include <functional>			//	Allows us to store functions like variables, very very easily, instead of function pointers
#include <unordered_map>
using namespace std;

//https://leetcode.com/problems/evaluate-reverse-polish-notation/
/*
 * 	This is a Stack problem. If you've learnt or even implemented a calculator app or some sort, then this
 * 	will be quite easy for you
 *
 * 	Reverse polish notation is: (left expr) - (right expr) - (operator)
 *
 * 	Thus, we push each of the numbers we see into the stack. Once we are met with a operator, pop the top 2 items
 * 	out from the stack. The first popped will be the right expr, the second popped will be the left expr, and you
 * 	perform the operation. Don't forget to push the result back into the stack!
 *
 * 	At the end, the result will be the last lone item in the Stack.
 */

class Solution {
public:

    int evalRPN(vector<string>& tokens) {
        unordered_map<string, function<int(int, int)>> operation = {
            {"+", [](int a, int b)-> int {return a + b; }},
            {"-", [](int a, int b)-> int {return a - b; }},
            {"*", [](int a, int b)-> int {return a * b; }},
            {"/", [](int a, int b)-> int {return a / b; }}
        };
        stack<int> stack;
        for (string& s : tokens) {
            if (operation.count(s)) {
                int rOperand = stack.top(); stack.pop();
                int lOperand = stack.top(); stack.pop();
                stack.push(operation[s](lOperand, rOperand));
            }
            else
                stack.push(stoi(s));
        }
        return stack.top();
    }

};