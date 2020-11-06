
#include <vector>
#include <cmath>
#define LONG long long int

/*
 * 	This is a binary search problem.
 *
 * 	First, notice that for a number, we have to obtain the sum of the division results, to the ceiling (Eg: 2.6 -> 3)
 * 	From this, we need to observe one thing:
 *
 * 		The lower the divisor, the higher the result will be, since more of the divisor may divide into a number
 * 		Eg: If divisor is 1, the result will always be the number itself
 * 		Conversely, the higher the divisor, the lower the result will be, since less divisor divide into a number.
 *
 * 	If we were to plot a graph of result against the divisor, the graph will basically look like a downhill slope. So
 * 	we basically have to find the smallest divisor which the sum is most closest, but less than or equal to the
 * 	threshold.
 *
 * 	Tackling this, we can use binary search, since for a given number, it either the sum is below or equal the threshold,
 * 	or not, and the divisor has a linear relationship with the sum.
 *
 * 	Define a range to binary search. Then, choose the middle value and run a linear division to check:
 * 		>	If the final sum is over threshold, the answer must be larger divisor. Make Left = mid + 1
 * 		>	Otherwise, the final sum is suitable. The answer can be this one, or optimally a lesser divisor. Make
 * 			Right = mid
 */

class Solution {
public:
    int smallestDivisor( std::vector<int>& nums, int threshold) {
        int left = 1, right = 1000000;
        while (left < right) {
            LONG res = 0;
            int mid = left + (right - left) / 2;

            for (int n : nums) {
                res += std::ceil(n * 1.0 / mid);
                if (res > threshold)
                    break;
            }

            if (res > threshold) {
                left = mid + 1;
            }
            else {
                right = mid;
            }
        }

        return left;
    }
};
