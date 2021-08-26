#include <string>
#include <sstream>
#include <stack>
using namespace std;

//https://leetcode.com/problems/verify-preorder-serialization-of-a-binary-tree/
/*
 * 	This is a Tree, Stack problem.
 *
 * 	Firstly, we could use stack to store the nodes in preorder traversal. When storing the nodes which is
 * 	in range [0,100], we could flip the sign to indicate the node's left subtree has been visited. However,
 * 	we need to +1 to avoid ambiguity of value 0.
 *
 * 	>	For each node,
 * 		- If top of stack is negative, we pop the top of stack, indicate the node is fully occupied
 * 		- Otherwise flip the sign of top element
 * 	>	If stack is empty before push or pop, then it is invalid tree
 *
 * 	Start by pushing a negative value onto the stack, so when first node comes, the initial negative value is
 * 	popped
 *
 *  ----------------------
 *
 *  An O(1) space solution is to count indegrees and outdegrees. In valid tree where we treat null as a node
 *  itself, a valid node provides 2 outdegree and consumes 1 indegree. A null node will consume 1 indegree
 *  and provides no outdegree. At the end, both should cancel each other
 */

class Solution {
public:

    // Stack solution
    bool isValidSerialization(string preorder) {
        stringstream ss(preorder);
        stack<int> stack;
        string temp;

        stack.push(-1);

        while (getline(ss, temp, ',')) {
            if (stack.empty()) return false;

            if (stack.top() > 0) {
                int push = stack.top();
                stack.pop();
                stack.push(-push);
            }
            else stack.pop();

            if (temp != "#")
                stack.push(stoi(temp.c_str()) + 1);
        }
        return stack.empty();
    }

    // Counting Indegree and outdegree solution
    bool isValidSerialization2(string preorder) {
        stringstream ss(preorder);
        int deg = 1;
        string temp;

        while (getline(ss, temp, ',')) {
            deg -= 1;
            if (deg < 0) return false;
            if (temp != "#") deg += 2;
        }
        return deg == 0;
    }
};