#include <vector>
using namespace std;

// https://leetcode.com/problems/sign-of-the-product-of-an-array
/*
 * This is an array math problem.
 *
 * The purpose of the function is to simply return the sign of the
 * product of all element in the array. Therefore, the rules are:
 *
 * - If there is a 0 in the array, the product will be 0. Return 0
 * - Otherwise, keep a sign variable. If the element is positive, sign *= 1. Otherwise, sign *= -1
 */



class Sign_of_the_Product_of_an_Array {
public:
    int arraySign(vector<int>& nums) {
        int sign = 1;

        for (int i: nums) {
            if (i == 0) return 0;
            sign *= i > 0 ? 1 : -1;
        }

        return sign;
    }

}
