#include <vector>
using namespace std;


//https://leetcode.com/problems/gray-code/
/*
 * 	This is a Backtracking / Bit Manipulation problem.
 *
 * 	For me, I solved using bit manipulation, which is easier to do because it is the nature of problem.
 * 	At every move, I can toggle a single bit, and I need to do this until i generated a full sequence
 * 	which loops back to 0.
 *
 * 	As long as I keep a record of the previously generated codes, I can ensure that I will not loop back into
 * 	previous generated code and always generate a newly, unique code. That is the first idea.
 * 	This idea can be implemented using array of size 1<<N, because N bits can have 2^N unique codes using permutation maths.
 *
 * 	Then, how do I generate a new code? The concept is that XORing a bit with 1, toggles it.
 * 	0 XOR 1 will be 1
 * 	1 XOR 1 will be 0
 * 	Therefore, I will attempt to toggle each single bit up to N bits, and check if it is previously generated. If it is not,
 * 	then a new code is created and ready to be recorded into our result list.
 *
 * 	It turns out that we will never hit a deadend. Given a code, I can always generate a unique code given that generated code
 * 	so far is less than 2^N. Sounds like pigeonhole principle?
 */

class Solution {
public:
	vector<int> grayCode(int n) {
		vector<bool> visited(1 << n, false);
		vector<int> res(1, 0);
		
		visited[0] = true;
		int curr = 0;

        while (res.size() != 1 << n) {
            for (int i = 0; i < n; ++i) {
                int attempt = curr ^ (1 << i);
                if (visited[attempt]) continue;
                visited[attempt] = true;
                res.push_back(attempt);
                curr = attempt;
                break;
            }
        }
        return res;
	}
};