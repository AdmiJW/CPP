#include <vector>
using namespace std;

// https://leetcode.com/problems/average-salary-excluding-the-minimum-and-maximum-salary/
/*
 * This is an array problem.
 * Simply iterate through the array, find the minimum and maximum salary, and also obtain the sum.
 *
 * At the end, subtract the sum by min and max, and divide by N-2
 */



class Solution {
public:
    double average(vector<int>& salary) {
        int min_v = INT32_MAX;
        int max_v = INT32_MIN;
        int sum = 0;

        for (int s: salary) {
            min_v = min(min_v, s);
            max_v = max(max_v, s);
            sum += s;
        }

        return (sum + 0.0 - min_v - max_v) / (salary.size() - 2);
    }
};