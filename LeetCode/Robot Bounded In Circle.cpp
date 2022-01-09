#include <string>
using namespace std;


//https://leetcode.com/problems/robot-bounded-in-circle/
/*
 * 	This is more of a mathematical and thinking/ figuring out problem.
 *
 * 	Given a robot that can turn 90 degrees left and right, and go straight in the direction it is facing. How do we know that
 * 	this series of instruction will cause it to move in a loop?
 *
 * 	First of all, every set of moves can be think of as a transformation. We don't care actually how it moves, but instead we only
 * 	care about the final displacement of the robot from the origin. This is easily represented by 2 variables both signifying the
 * 	X and Y displacement.
 *
 * 	Also, due to the nature of the instructions, we have to keep track of the direction which the robot is currently facing.
 * 	This can be represented by 4 numbers, Here I will use the actual degree itself. 0 deg means North
 *
 * 	For the robot to actually move in the cycle, the most straightforward case is that the robot, after going through the
 * 	instructions one time, ends up back at the origin.
 * 	In transformation matrix, this would be seen as (0,0). In this case, no matter what direction the robot is facing, the
 * 	transformation is 0 in both X and Y. So this is one way that the robot can end up in cycle.
 *
 * 	Another way is: WHEN THE ROBOT, IN THE END OF THE INSTRUCTIONS, DOES NOT FACE THE SAME DIRECTION AS INTIIALLY.
 * 	To understand, by rotating, we are essentially causing one of, if not both of the X and Y displament of the transformation matrix
 * 	to inverse (Eg: 3 will become -3)
 *
 * 	>	See: Say the displacement is (3, 5).
 * 		If at the end robot ƒ¢ƒÆ is 180deg from origin angle, the next move will cause displacement of (-3, -5)
 *
 * 		If at the end robot ƒ¢ƒÆ is 90deg from origin angle (turned left or right), the next move will cause displacement of
 * 		(3, -5) or (-3, 5)
 *
 * 		To easier visualize this, we could further split it down into the 1D dimension, let's say X axis
 *
 * 		Say x displacement is 5. At the end, robot will be facing ƒ¢ƒÆ of 90deg.
 *
 * 		Transformation matrix consisting of x component only will end up with:
 * 			(5)	->	(0)	->	(-5)	->	(0)
 *
 * 		Of course this would work differently in the 2D transformation. But the core idea is, after in maximum 2 moves, the transformation
 *		applied in the prior 2 moves, will be reverted back in the next 2 subsequent moves. This way, after either 2 or 4 moves,
 *		it will end up back in the original position.
 *
 *	Therefore simply, check if the transformation matrix is (0,0), or the robot end up not in same direction as the origin facing direction
 */




class Solution {
public:
    
    // Simulation solution
    bool isRobotBounded(string instructions) {
        int DIRS[4][2] = { {0,1}, {1,0}, {0,-1}, {-1,0} };
        int dirIndex = 0;
        int currVector[] = { 0, 0 };
        
        // At most we'll repeat the instructions 4 times. No more.
        for (int i = 0; i < 4; ++i) {
            for (char c : instructions) {
                if (c == 'G') {
                    currVector[0] += DIRS[dirIndex][0];
                    currVector[1] += DIRS[dirIndex][1];
                }
                else if (c == 'L')
                    dirIndex = (dirIndex == 0) ? 3 : dirIndex - 1;
                else
                    dirIndex = (dirIndex + 1) % 4;
            }

            if (currVector[0] == 0 && currVector[1] == 0) return true;
        }
        return false;
    }





    // Single pass, logical solution
	bool isRobotBounded(string instructions) {

		int angle = 0;
		int dispX = 0;
		int dispY = 0;

		for (char c : instructions) {
			switch (c) {
			case 'L':
				angle -= 90;
				if (angle == -90) angle = 270;
				break;
			case 'R':
				angle += 90;
				if (angle == 360) angle = 0;
				break;
			case 'G':
				if (angle == 0) dispY++;
				else if (angle == 90) dispX++;
				else if (angle == 180) dispY--;
				else dispX--;
			}
		}

		return ((dispX == 0 && dispY == 0) || angle != 0);
	}
};