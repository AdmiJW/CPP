// https://leetcode.com/problems/rectangle-area/
/*
 * This is a geometry math problem.
 * 
 * Break it down into calculating 2 data:
 *  > The overlapping x length
 *  > The overlapping y length
 * 
 * To calculate the overlapping of one axis, we must handle the cases:
 *  > No overlapping, checked using if statement. The intersection length should be 0
 *  > Partial overlapping. Rect A partially overlaps with Rect B or vice versa. The intersection length should be the smaller of the 2 end points
 *  > Full overlapping. Rect A is contained in Rect B or vice versa. The intersection length should be the length of Rect A or Rect B
 */


#include <vector>



class Solution {
public:
    int computeArea(int ax1, int ay1, int ax2, int ay2, int bx1, int by1, int bx2, int by2) {
        int xIntersection = 0;
        int yIntersection = 0;

        // Case: The x of rectangle B intersects/or contained in rectangle B
        if (bx1 >= ax1 && bx1 <= ax2) {
            xIntersection = min(ax2, bx2) - bx1;
        } 
        else if (ax1 >= bx1 && ax1 <= bx2) {
            xIntersection = min(ax2, bx2) - ax1;
        }

        if (by1 >= ay1 && by1 <= ay2) {
            yIntersection = min(ay2, by2) - by1;
        } 
        else if (ay1 >= by1 && ay1 <= by2) {
            yIntersection = min(ay2, by2) - ay1;
        }

        int area1 = (ax2 - ax1) * (ay2 - ay1);
        int area2 = (bx2 - bx1) * (by2 - by1);
        return area1 + area2 - xIntersection * yIntersection;
    }
};