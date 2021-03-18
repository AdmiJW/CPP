#include <cstdlib>
#include <cmath>
#include <vector>
using namespace std;

//https://leetcode.com/problems/generate-random-point-in-a-circle/
/*
 * 	This is simply math probabilistic problem
 *
 * 	You might immediately come up with a solution that just uses random() on both x and y, or
 * 	you might be more clever to simulate the circle process, by generating random angle and length.
 * 	However, those will fail to give random points distributed normally on the circle
 *
 * 	What the question wants, is that the points generated to be preferrably equidistant from other
 * 	close points. When view the circle, the points should look uniform, and not clustered on one place
 *
 * 	Why using pure random fails? Recall that the further the circle is from the center, the larger the
 * 	circumference. You might flatten the circumference into a straight line. Now, To have a uniformly
 * 	plotted points, the further away the circle, the more points has to be plotted!
 *
 * 	Thus, if we can't use pure random(), what can we do? Recall square root function! In square root
 * 	of 0 to 1, The distribution starts out sparse, then only getting more frequent when approaching 1.
 *
 * 	Normal random: * * * * * * * * * * * * * * * *
 * 	Sqrt random:   *     *     *   *   * * * * * *
 *
 * 	Thus, we can use that property on our side to generate less points close to circle's center, and more
 * 	points near the outside of the circle!
 */

class Solution {
public:
	double radius, x_center, y_center;

	Solution(double radius, double x_center, double y_center): radius(radius), x_center(x_center), y_center(y_center) {}

	vector<double> randPoint() {
		double length = sqrt(static_cast<double>(rand() ) / RAND_MAX) * radius;
		double angle = (static_cast<double>(rand()) / RAND_MAX) * 4 * acos(0.0);

		double xoffset = length * cos(angle);
		double yoffset = length * sin(angle);

		return { x_center + xoffset, y_center + yoffset };
	}
};