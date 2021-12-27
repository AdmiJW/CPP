

//https://leetcode.com/problems/number-complement/
/*
 * This is a bitwise manipulation problem.
 *
 * Given a number n, we only have to flip the bits up to the Most Significant Bit.
 * Eg: n = 5, then we only have to flip 3 bits, since 5 == (101). The other 0 bits are ignored.
 *
 * Recall the property of XOR: any bit XOR with 1 will be flipped:
 * 		0 XOR 1 = 1
 * 		1 XOR 1 = 0
 * Therefore we can use this to achieve complement. We just need a mask of all 1's until the MSB of the num.
 *
 *
 * Here's a tip: 0 is basically all 0's. If you want all 1's, simply complement it ---> ~0.
 */


class Solution {
public:

    int findComplement(int num) {
        int mask = 0;

        for (int n = num; n != 0; n >>= 1)
            mask = (mask << 1) + 1;


        return mask ^ num;
    }

};