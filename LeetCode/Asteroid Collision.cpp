
#include <vector>
#include <cmath>

//https://leetcode.com/problems/asteroid-collision/

/*
    This is a stack problem.

    For every asteroid, we have to know if it will get destroyed or not, based on the direction of the asteroid

    This is achieved by iterating over the asteroids. For each asteroid, it can moving to the left or right. Initially,
    all the asteroids moving to the left will never collide.
    Now, if we have one asteroid moving to the left, we have to see if it will destroy the previous one or not. THis is done
    by checking stack top. If it does, then destroy the asteroid at stack top and continue to next checking of stack top.
*/

class Solution {
public:
    std::vector<int> asteroidCollision( std::vector<int>& asteroids) {
        std::vector<int> stack;

        for (int n : asteroids) {
            if (n > 0) {
                stack.push_back(n);
            }
            else {
                while (!stack.empty() && stack.back() > 0 && stack.back() < std::abs(n)) {
                    stack.pop_back();
                }

                if (stack.empty() || stack.back() < 0) {
                    stack.push_back(n);
                } else if (stack.back() * -1 == n) {
                    stack.pop_back();
                    continue;
                }
                
            }
        }

        return stack;
    }
};