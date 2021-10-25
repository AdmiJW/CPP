#include <stack>
using namespace std;

//https://leetcode.com/problems/min-stack/
/*
 * This is a Stack problem, which you can implement also using linked list.
 *
 * The idea is to have more information in addition to the values being added. See;
 * In a stack, we pop only the latest element.
 * Therefore, for each and every node, we could easily save 1 more information: What is the minimum element in the stack
 * when this node is at the top of the stack?
 *
 * In my implementation, I have 2 stacks: One for storing normal values, and one for storing minimum element.
 * When I push a value, what I'll do on minElem stack is to determine what is the minimum value in the stack when current
 * element is on the top of the stack, which is determined by
 *
 * 		min( minElem.peek, currElem )
 */

class MinStack {
public:
    stack<int> minElem;
    stack<int> stack;

    void push(int val) {
        stack.push(val);
        minElem.push(minElem.empty() ? val : min(minElem.top(), val));
    }

    void pop() {
        stack.pop();
        minElem.pop();
    }

    int top() {
        return stack.top();
    }

    int getMin() {
        return minElem.top();
    }
};