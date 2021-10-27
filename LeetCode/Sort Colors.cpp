#include <vector>
#include <algorithm>
using namespace std;

//https://leetcode.com/problems/sort-colors/
/*
 * 	This question can be done easily with a two-pass algorithm, the first pass counts the number of 0's (Red) and 1's (White), then the second
 * 	pass will replace the existing array with 0's and 1's, and the rest with 2's. Resulting in approximately O(2n) time and O(1) space
 *
 * 	To achieve a single pass algorithm, we have to use two pointers method. The left pointer points at the location where the next Red (0) should
 *  be placed, and the right pointer points at the location where the next Blue (2) should be placed, initialized at the index 0 and length(nums) -1
 *  respectively.
 *  With a reading pointer, it will run a linear scan through the array, starting from start of array, and follows the following algorithm:
 *  	1. If the color is Red(0): it will swap with the leftmost pointer elements, and move both the reader pointer and left pointer + 1
 *  	2. If the color is Blue(2): it will swap with the rightmost pointer elements, and move the right pointer - 1, the reader pointer is
 *  		not moved (To further verify the swapped elements)
 *  	3. If the color is White(1): no action will be done, and the reader pointer moves + 1
 *
 * 	The reading pointer will iterate until it is greater than the right pointer.
 *
 * 	Notice why in case 1, we can move the reader pointer forward without checking the swapped elements? This is because of the fact that
 * 	the reader pointer will always be equal or greater than left pointer. Any of the Blues(2) will have been handled by reader pointer beforehand,
 * 	resulting in only White(1) or Red(1) to handle.
 */


class Solution {
public:
    void sortColors(vector<int>& nums) {
        int l = 0, r = nums.size() - 1;

        for (int i = 0; i < r; ) {
            if (nums[i] == 0) {
                swap(nums, i, l++);
                if (i == l) ++i;
            }
            else if (nums[i] == 2)
                swap(nums, i, r--);
            else ++i;
        }
    }


    void swap(vector<int>& nums, int i, int j) {
        int temp = nums[i];
        nums[i] = nums[j];
        nums[j] = temp;
    }
};