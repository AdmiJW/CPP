#include <vector>
#include <algorithm>
using namespace std;

//https://www.youtube.com/watch?v=zzNEKy4xquw
/*
 * 	A really brute force solution would be checking every possible combination of people going to city A or B. This way would be very
 * 	inefficient and results in time	limit exceeded.
 *
 * 	An O(n log n) -greedy sorting solution would be to sort every individual differences of going to city A compared to B. In other words, how
 * 	much would I save if I go to city A compared to B?
 * 	Now if the solution is sorted in descending, money saved if this person goes to city A instead of B, and we know exactly N person need to
 * 	go to city A, we would take the first half of the array to A, and the other half to B!
 */

class Solution {
public:
    int twoCitySchedCost(vector<vector<int>>& costs) {
        const int l = costs.size() / 2;
        
        // Sort the costs based on their difference
        sort(costs.begin(), costs.end(), [](auto& l, auto& r)-> bool {
            return abs(l[0] - l[1]) > abs(r[0] - r[1]);
        });

        int res = 0;
        int aCount = 0, bCount = 0;

        for (auto& c : costs) {
            // Going to city A is cheap, and not yet exceed N
            if (c[0] <= c[1] && aCount != l) {
                ++aCount;
                res += c[0];
            }
            // Going to city B is cheap, and not yet exceed N
            else if (c[1] <= c[0] && bCount != l) {
                ++bCount;
                res += c[1];
            }
            // Else one of A or B capacity is filled.
            else {
                if (aCount == l) res += c[1];
                else res += c[0];
            }
        }
        return res;
    }
};