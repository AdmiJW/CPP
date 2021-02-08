#include <vector>
#include <string>
#include <queue>
using namespace std;

//https://leetcode.com/problems/shortest-distance-to-a-character/
/*
 * 	This is a Array problem, potentially usage of Queue, but optimized solution don't use it
 *
 * 	-------------------------------------------------------------
 *
 * 	For each character in string, the closest character c may come from the left, or the right. Therefore, we
 * 	need this information for efficient processing.
 *
 * 	To obtain this information, notice this: We have to discard away indices that are already far away from current
 * 	position. Data structures like stack and queue immediately comes to mind.
 *
 * 	Therefore, first iteration records the indices of character c into the queue. Then, in second iteration, we hold
 * 	a previous indice of character c, and keep comparing with top of queue. If right side character is closer (top of
 * 	queue), we poll (update) and discard away the left index of character c.
 *
 * 	Worst case space complexity is O(N) if the string is entirely character c.
 *
 * 	-----------------------------------------------------------------
 *
 * 	As said, character c may come from left or right. Therefore, split the problem into smaller ,easier to solve
 * 	subproblems:
 *
 * 		>	Shortest distance to a character STRICTLY FROM LEFT SIDE ONLY
 * 		>	Shortest distance to a character STRICTLY FROM RIGHT SIDE ONLY
 *
 * 	Take the minimum from these 2 solutions, we will get global solution.
 */

class Solution {
public:

    //	Using Queue - Two Passes
    vector<int> shortestToChar(string s, char c) {
        const int len = s.length();
        vector<int> res(len);
        queue<int> queue;

        for (int i = 0; i < len; ++i)
            if (s[i] == c) queue.push(i);
        queue.push(INT32_MAX);          //	To avoid having to check if queue empty
            
        int curr = queue.front(); queue.pop();  //	Pop the closest from left

        for (int i = 0; i < len; ++i) {
            if (abs(i - curr) > abs(queue.front() - i)) {
                curr = queue.front();
                queue.pop();
            }
            res[i] = abs(i - curr);
        }

        return res;
    }



    //	Two pass solution : L to R and R to L
    vector<int> shortestToChar2(string s, char c) {
        const int len = s.length();
        vector<int> res(len);

        int curr = INT32_MIN / 2;
        for (int i = 0; i < len; ++i) {
            if (s[i] == c) curr = i;
            res[i] = abs(i - curr);
        }

        curr = INT32_MAX / 2;
        for (int i = len - 1; i >= 0; --i) {
            if (s[i] == c) curr = i;
            res[i] = min(res[i], abs(curr - i));
        }

        return res;
    }
};