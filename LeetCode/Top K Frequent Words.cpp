#include <queue>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>
using namespace std;

// https://leetcode.com/problems/top-k-frequent-words/
/*
 * 	This is a min heap problem.
 *
 * 	First, obtain the frequencies of a string in O(N) time using a HashMap.
 *
 * 	Then, we have to sort them based on frequency first in descending order, then ascending with lexicographical.
 * 	That would take O(N log N) time where N is number of unique words.
 *
 * 	Since K can be less than N by, a lot, we can reduce the time complexity to O(N log K) with min heap. The idea is the same:
 * 	The min heap will poll out the least frequency words, then the ones with greater lexicographical. Push all the unique strings
 * 	one by one into the heap, and poll once the size exceeds k.
 *
 * 	At the end, what's left in the heap is most frequent k strings. We can poll them out and reverse the order to get the final
 * 	solution.
 */

class Solution {
public:
    vector<string> topKFrequent(vector<string>& words, int k) {
        unordered_map<string, int> count;

        for (string& s : words) ++count[s];

        // Comparator lambda
        auto Compare = [&count](string& x, string& y) {
            // Pop y first if x is less lexicographically, given frequency is same for x and y
            if (count[x] == count[y]) return y.compare(x) > 0;
            // Less frequency ones goes first, so be popped first
            return count[x] > count[y];
        };

        // Min heap
        priority_queue<string, vector<string>, decltype(Compare)> pq(Compare);

        for (auto& e : count) {
            pq.push(e.first);
            if (pq.size() > k) pq.pop();
        }

        vector<string> res;
        while (!pq.empty()) {
            res.push_back(pq.top());
            pq.pop();
        }
        reverse(res.begin(), res.end());
        return res;
    }
};