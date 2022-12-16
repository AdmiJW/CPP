#include <stack>
using namespace std;

// https://leetcode.com/problems/implement-queue-using-stacks
/*
 * This is a stack and queue problem.
 * Stack is known to be LIFO and the application to reverse elements.
 *
 * Therefore if we have a queue and we push all of them into a stack, the element will be reversed,
 * and if reverse the stack again, the element will be in the same order as the queue.
 *
 * When adding a new element, push all elements of queue stack into temp stack, then push the new element into queue stack,
 * then push all elements of temp stack into queue stack.
 *
 * O(n) time for push, O(1) time for pop, peek and empty.
 */


class MyQueue {
public:
    stack<int> temp;
    stack<int> queue;

    void push(int x) {
        // Move all elements of queue into temp
        while (!queue.empty()) {
            temp.push(queue.top());
            queue.pop();
        }

        // Push x into queue
        queue.push(x);

        // Push everything back to queue
        while (!temp.empty()) {
            queue.push(temp.top());
            temp.pop();
        }
    }

    int pop() {
        int top = queue.top();
        queue.pop();
        return top;
    }

    int peek() {
        return queue.top();
    }

    bool empty() {
        return queue.empty();
    }
};