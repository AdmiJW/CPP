
#include <vector>
using namespace std;

//https://leetcode.com/problems/remove-duplicates-from-sorted-array-ii/
/*
 * 	This is an array, two pointer problem.
 *
 * 	We have to manipulate the array IN-PLACE, replacing each useless element (The third or more occurrance of a number)
 * 	with the next useful element that follows it. How do we do that?
 *
 * 	Since the array is already sorted, that means all the same elements will be grouped in one single place. By
 * 	iterating, we can easily know how many occurrences of the same element is in the array.
 * 	Therefore, we can check once the counter variable had exceeded 2, the following same elements are considered
 * 	useless already.
 * 	Once the element we met is a new one (different from last element), reset the counter to 1.
 *
 * 	Another method is to simply derive this logic:
 * 		- Since it requires 3rd occurrance or more to make an element as useless, the first 2 elements of the original
 * 		  array can't be useless
 *  	- For other elements, simply check back the previous 2 elements.
 *
 * 	Now, once we noticed a useful element, how do we fill it into the previous empty spaces? (The space that
 * 	are occupied by useless elements)
 * 	Introduce two pointers method:
 * 		>	First pointer simply to iterate through the array
 * 		>	Second pointer will point to the available space to put in useful elements, or the 'tail' of
 * 			the result array so far.
 *
 * 	When we encountered a useful element, put the useful element into the space pointed by second pointer and
 *	increment the tail pointer.
 *	Conversely, if it is a useless element, simply proceed the fast pointer without moving the slow pointer,
 *	so that the slow pointer will still point to the tail of the result array, ready to be inserted by another useful
 *	element.
 *
 *	At the end, the tail pointer is the length of the array with useless elements eliminated.
 *
 *	--------------------------------------------------------------
 *	Look at the case:
 *
 *	[1,1,1,2,2]
 *
 *	Surely, the 3rd (1) will be eliminated. When we arrive at the last (2), the array would look like:
 *
 *	[1,1,2,2,(2)]
 *	If we use the current pointer to check previous element, we would falsely think that the current (2) is already a
 *	useless element, due to previous 2 elements being  the same element.
 *
 *	Instead, the solution is to use toIns poointer to check the previous 2 elements!
 *
 */

class Solution {
public:

	//	Iterator approach
	int removeDuplicates(vector<int>& nums) {
        if (nums.size() <= 2) return nums.size();
        int toIns = 2;

        for (int i = 2; i < nums.size(); ++i) {
            // Check the previous 2 elements using the toIns pointer
            if (nums[i] == nums[toIns - 1] && nums[i] == nums[toIns - 2]) continue;
            // Otherwise, insert the useful element into the tail of array, and increment the pointer
            nums[toIns++] = nums[i];
        }

        return toIns;
	}
};