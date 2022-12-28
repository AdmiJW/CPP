#include <queue>
#include <vector>
using namespace std;

// https://leetcode.com/problems/remove-stones-to-minimize-the-total/description/
/*
 * This is simply a heap problem.
 *
 * We can use a max heap to store the piles. Since we want to minimize the stones, we will always pick the
 * largest pile to halve it, thus some elements of Greedy algorithm. Do this k times.
 */

class Solution {
public:
    int minStoneSum(vector<int>& piles, int k) {
        // Create a max heap
        priority_queue<int> pq(piles.begin(), piles.end());

        // Halve stone k times
        while (k-- > 0) {
            int cur = pq.top();
            pq.pop();
            pq.push(cur - cur / 2);
        }

        // Return sum
        int sum = 0;
        while (!pq.empty()) {
            sum += pq.top();
            pq.pop();
        }
        return sum;
    }
};


