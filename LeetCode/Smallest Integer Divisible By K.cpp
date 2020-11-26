

#include <unordered_set>
//https://leetcode.com/problems/smallest-integer-divisible-by-k/

/*
 * 	This is a math problem, with possibly Floyd's Hare and Tortoise Algorithm and Pigeonhole principle
 *
 * 	Each time, we increase the previous term of 1 so that 1 -> 11 -> 111 -> 1111...
 * 	However, the problem is that eventually it will definitely overflow. What should we do?
 *
 * 	Notice we only need the modulus of it. If it is divisible by K, then modulus will be 0, and we can immediately
 * 	return. How can we utilize this property?
 *
 * 	Remember the Remainder Theorem:
 * 			1 = aK + R				Where a is result of division of 1 by K, and R is the remainder
 * 	Also,
 * 			11 = 1 * 10 + 1
 *
 * 	We have 2 equations here. Try substitute:
 *
 * 			11 = (aK + R) * 10 + 1
 *
 * 	Then we need to obtain the modulus of it again. Notice when we perform modulo of K, the term aK will certain
 * 	result in remainder of 0. Therefore, we actually don't need that aK part! Just the previous term's modulo
 * 	is fine!
 *
 * 			Modulo of n term = ( Modulo of n-1 term * 10 + 1) % K
 *
 * 	==-----------------------------------------------------------------------------------
 *
 * 	Now we can detect when number is divisible by K. What if it cannot divide? It will result in inifinite loop.
 * 	How can we exit the loop when we sense it is not divisible?
 *
 * 	First naive method is to record the remainders encountered. When we returned to the remainder again, we know
 * 	it is going to loop forever, thus exit the loop
 *
 * 	Time is always O(K), but space is also O(K). Can we do O(1) space?
 *
 * 	---------------------------------------------------------------------------------------
 *
 * 	When sensing a loop, Floyd's Tortoise and Hare algorithm is able to detect it well. Keeping a fast pointer
 * 	which moves 2 step and a slow pointer who moves 1 step, if there is a loop, certainly the two pointers will
 * 	meet at some point.
 *
 * 	Maybe you ask when the two pointers have the same remainder value but not necessary they are in same position?
 * 	No because when the remainder values are same, they ARE already in a loop.
 *
 * 	This solution uses O(2K) space and O(1) space.
 *
 * 	------------------------------------------------------------------------------------------
 *
 * 	The optimized solution involves observation of Pigeonhole Principle.
 *
 * 	For divisor K, the remainders that we can get is {0,1,2... K-1}
 * 	Thus, when the loop had iterated until K times, we immediately know there is at least a element repeating
 * 	already. Return -1 at that point.
 */
class Solution {
public:

    int smallestRepunitDivByK(int K) {
        std::unordered_set<int> set;
        set.insert(1);
        int len = 1;
        int i = 1 % K;

        while (i != 0) {
            len++;

            i = i * 10 + 1;
            i %= K;

            auto ret = set.insert(i);
            if (!ret.second) return -1;
        }
        return len;
    }




    int smallestRepunitDivByK2(int K) {
        int pt1 = 1 % K;
        int pt2 = 1 % K;
        int len = 1;

        if (pt1 == 0) return len;

        while (pt1 != 0) {
            len++;

            pt1 = (pt1 * 10 + 1) % K;
            pt2 = (pt2 * 10 + 1) % K;

            if (!pt1) return len;

            len++;

            pt1 = (pt1 * 10 + 1) % K;
            if (pt1 == pt2) return -1;
        }
        return len;
    }



    int smallestRepunitDivByK3(int K) {
        int i = 1 % K;
        int len = 1;

        while (i != 0) {
            if (++len > K)
                return -1;

            i = (i * 10 + 1) % K;
        }
        return len;
    }
};