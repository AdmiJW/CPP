#include <string>
#include <sstream>
using namespace std;

//https://leetcode.com/problems/complex-number-multiplication/
/*
 *  No complex algorithms here. Simply parse the string, extract out the real and imiginary part,
 *  do the math and output properly
 *
 *  The regex is to determine the delimiter. Example in 1+-1i, we want to always treat the '+' and 'i' as delimiter.
 *  So what's left is 1 and -1
 */

class Solution {
public:
    string complexNumberMultiply(string num1, string num2) {
        int real1, real2, im1, im2;
        sscanf(num1.c_str(), "%d+%di", &real1, &im1);
        sscanf(num2.c_str(), "%d+%di", &real2, &im2);

        return to_string(real1 * real2 - im1 * im2) + "+" + to_string(real1 * im2 + real2 * im1) + "i";
    }


    // or using stringstream
    string complexNumberMultiply(string num1, string num2) {
        int real1, real2, im1, im2;
        char buff;
        stringstream n1(num1), n2(num2);
        stringstream res;

        n1 >> real1 >> buff >> im1;
        n2 >> real2 >> buff >> im2;

        res << (real1 * real2 - im1 * im2) << '+' << (real1 * im2 + real2 * im1) << 'i';
        return res.str();
    }
};