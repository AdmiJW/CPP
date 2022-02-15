#include <vector>
using namespace std;


//https://leetcode.com/problems/single-number/
/*
 * 	The trivial implemententation would be to use a Set - Add the number to set whenever you encounter it first time,
 * 	and remove it when encountered second time.
 *
 * 	The element that remains would be the single number.
 *
 * 	---------------------------
 *
 * 	Best way is by using XOR property - XOR a number 2 times will have the effect of cancelling it:
 *
 * 	01011 XOR 10111 ----> 11100
 * 	11100 XOR 10111 ----> 01011   (You get back the original number!)
 *
 * 	The cool property of this bitwise XOR is, it doesn't matter how many numbers you XOR before, let's say you have
 * 	[1,2,3,1,2,3] and you XOR the number from left to right: You will still get back 0!
 *
 * 	Using this, if there is only ONE single element from the array, XORing will end up yielding that element directly!
 */


class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int res = 0;
        for (int i : nums) res ^= i;
        return res;
    }
};