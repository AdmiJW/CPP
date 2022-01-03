#include <vector>
#include <unordered_map>
#include <vector>
using namespace std;

//https://leetcode.com/explore/challenge/card/may-leetcoding-challenge/535/week-2-may-8th-may-14th/3325/
/*
 *	The problem is a graph theory problem, where the judge should have 0 Outgoing edges, and exactly N-1 incoming edges
 *	Even better, every time a person trusts a person, we simply decrement it by 1, and when a person get trusted, increment it by one
 *	Lastly use a linear search to check if there is a person (judge) which value is exactly N-1
 */

class Solution {
public:
    int findJudge(int n, vector<vector<int>>& trust) {
        vector<int> indegree(n + 1, 0);

        // If a trusts another person, a cannot be the judge
        // If b is being trusted, b's in-degree increase
        for (auto& t : trust) {
            indegree[t[0]] = INT32_MIN;
            ++indegree[t[1]];
        }

        // Linear search if any node is N-1 in-degree
        for (int i = 1; i <= n; ++i)
            if (indegree[i] == n - 1) return i;
        return -1;
    }
};