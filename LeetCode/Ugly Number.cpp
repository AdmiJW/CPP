
// https://leetcode.com/problems/ugly-number/description/
/*
 * A ugly number can only have prime factors of 2, 3, 5. If a number has prime factors of [] like 1, it is also ugly.
 * 
 * We can approach this recursively.
 *      > If n is divisible by 2 and (n/2) is ugly, then n is ugly
 *      > If n is divisible by 3 and (n/3) is ugly, then n is ugly
 *      > If n is divisible by 5 and (n/5) is ugly, then n is ugly
 * 
 * We can actually improve the performance by using Dynamic Programming to cache the results of the recursive calls.
 * 
 * Time complexity and space complexity is O(log n), N is keep divided by 2, 3, 5. 
 */


class Solution {
public:
    bool isUgly(int n) {
        if (n < 1) return false;
        if (n == 1) return true;

        if (n % 2 == 0 && isUgly(n / 2)) return true;
        if (n % 3 == 0 && isUgly(n / 3)) return true;
        return (n % 5 == 0 && isUgly(n / 5));        
    }
};