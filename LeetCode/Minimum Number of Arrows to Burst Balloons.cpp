#include <algorithm>
#include <vector>
using namespace std;

//https://leetcode.com/problems/minimum-number-of-arrows-to-burst-balloons/
/*
 * 	This is a Greedy sort Interval problem.
 *
 * 	Given a list of balloon intervals. Find the least number of arrow required to pop them all.
 *
 * 	In greedy approach, let's sort the intervals first. In my solution, I sorted them mainly based on starting point.
 * 	Therefore in the sorted array, for each selected balloon, the starting point must STRICTLY ONLY BE GREATER THAN OR
 * 	EQUAL to the current balloon.
 *
 * 	Now, how do we know if multiple balloon can be shot down in a single arrow? We will first keep a End pointer.
 * 	this end pointer points to the ending point of the last balloon. If the NEXT BALLOON'S STARTING POINT is GREATER THAN
 *  the range pointed by end pointer, then it means the balloon cannot be shot down along with the last balloon!
 *
 *  In the case where current balloon's starting point greater than the end pointer:
 *  	>	Increase a arrow
 *  	>	Update the end pointer to point to the current balloon's end point
 *
 *  Otherwise, the balloon's starting point is less than or equal to end pointer, means it can be shot down along with last
 *  balloon:
 *  	>	Update the end pointer, to point to MINIMUM of the two: (end pointer) OR (current balloon's ending point)
 *
 *  This is because we only know that this balloon can be shot down along with last balloon. What we don't know is that
 *  whether this balloon or last balloon end point is greater. Optimally, we shall choose the one with shortest ending point,
 * 	because when the next balloon comes, we ensure to check if the last arrow which shot down both 2 balloons, can also shot
 * 	down the current balloon as well. If not, then we will need to use a new arrow.
 *
 *  ===========================================================================================================
 *
 *  For optimization, we actually don't have to sort by starting point. We immediately sort by ending point.
 *  Then SINCE EVERY NEXT BALLOON HAS ENDING POINT STRICTLY GREATER THAN OR EQUAL THAN THE CURRENT BALLLOON,
 *  we don't have to compare each time again in the for loop.
 *
 *  Meaning, The ending point of the balloons are initally as minimum as possible.
 *
 *  If the next balloon starting point is greater, then it requires an arrow and ending point extends as usual.
 *
 *  However, if the balloon can be shot down along with last balloon, NO NEED TO UPDATE ANYTHING. This is because this
 *  ending point is greater than or equal to last ending point. We want the MINIMUM, so it must be last balloon's ending
 *  point!
 */



class Solution {
public:

    // Sorting and iteration solution
    int findMinArrowShots(vector<vector<int>>& points) {
        int res = 0;

        // Sort by start point. 
        sort(points.begin(), points.end(), [](auto& l, auto& r)-> bool {
            if (l[0] == r[0]) return l[1] < r[1];
            return l[0] < r[0];
        });

        int end = points[0][1];

        for (auto& p : points) {
            if (p[0] > end) {
                ++res;
                end = p[1];
            }
            else
                end = min(p[1], end);
        }

        return res + 1;
    }
};