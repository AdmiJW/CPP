
#include <vector>
using namespace std;

//https://leetcode.com/problems/remove-duplicates-from-sorted-array-ii/

/*
 * 	This is an array, two pointer problem.
 *
 * 	We have to manipulate the array IN-PLACE, replacing each useless element with the next useful element that
 * 	follows it. How do we do that?
 *
 * 	Since the array is already sorted, that means all the same elements will be grouped in one single place. By
 * 	iterating, we can easily know how many occurrences of the same element is in the array.
 * 	Therefore, we can check once the counter variable had exceeded 2, the following same elements are considered
 * 	useless already.
 * 	Once the element we met is a new one (different from last element), reset the counter to 1.
 *
 * 	Now, once we noticed a useful element, how do we fill it into the previous empty spaces? (The space that
 * 	are occupied by useless elements)
 * 	Introduce two pointers method:
 * 		>	First pointer simply to iterate through the array
 * 		>	Second pointer will point to the available space to put in useful elements, or the 'tail' of
 * 			the result array so far.
 *
 * 	When we encountered a useful element, put the useful element into the space pointed by second pointer and
 *	increment the pointer.
 *	Conversely, if it is a useless element, simply proceed the fast pointer without moving the slow pointer,
 *	so that the slow pointer will still point to the tail of the result array, ready to be inserted.
 *
 *	Note that the first element in the array no matter what, must be included. This is a useful property
 *	such that we can just start checking from the second element, since each iteration we have to check if the
 *	element is same as previous element.
 */

class Solution {
public:

	//	Iterator approach
	int removeDuplicates(vector<int>& nums) {
		if (nums.begin() == nums.end()) return 0;

		const int len = nums.size();
		int counter = 1;
		int slowpt = 1;

		for (vector<int>::iterator it = nums.begin() + 1; it != nums.end(); ++it) {
			//	Validation. Check if previous element count
			if (*it == *(it - 1)) counter++;
			else counter = 1;

			//	Valid value. Replace slow pointer's value (which points
			//	to the available space to fill) with the fast pointer's value
			if (counter <= 2)
				nums[slowpt++] = *it;
		}
		return slowpt;
	}
};