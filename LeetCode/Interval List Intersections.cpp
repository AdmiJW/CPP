#include <vector>
using namespace std;

//https://leetcode.com/problems/interval-list-intersections/
/*
 * 	Although not very obvious, it is a two pointers question
 *
 * 	At any iteration i, we would need to compare two intervals, one from A and one from B, done by having two pointers
 * 	pointing at one interval in A and B respectively.
 * 	In each iteration, we will update either A and B pointer, to be compared in next iteration.
 *
 *
 * 	The basic, intuitive algorithm here is:
 * 		1.	Loop the indices of A or B until there is a valid intersection
 * 		2.	Determine the intersection and add it to results
 * 		3.	Increment either one of the A or B index
 * 		4. 	Repeat step 1-3 until the indices ran out of bound
 *
 * 	However step 1 can be simplified without checking:
 * 		Since every intersection requires us to take the maximum of the lows, and minimum of the highs, we could simply just do it,
 * 		but a valid intersection between A and B is that, the intersection's low must be less than the intersection's high, if this
 * 		rule is broken, that means A and B has no intersection at all!
 *
 * 	To determine step 3, check:
 * 		-	If A's high is greater than B's high, then proceed B
 * 		-	If B's high is greater than A's high, then proceed A
 */

class Solution {
public:
    vector<vector<int>> intervalIntersection(vector<vector<int>>& firstList, vector<vector<int>>& secondList) {
        const int alen = firstList.size();
        const int blen = secondList.size();
        int a = 0, b = 0;
        vector<vector<int>> res;

        // While we have 2 intervals to compare
        while (a < alen && b < blen) {
            // 1 - Compare interval
            // For left, take the maximum out of the two
            // For right, take the minimum out of the two
            int left = max(firstList[a][0], secondList[b][0]);
            int right = min(firstList[a][1], secondList[b][1]);

            // It is valid intersection only if left <= right
            if (left <= right) res.push_back({ left, right });

            // Move either a pointer or b pointer, based on whoever has smaller right value
            if (firstList[a][1] < secondList[b][1]) ++a;
            else ++b;
        }

        return res;
    }
};