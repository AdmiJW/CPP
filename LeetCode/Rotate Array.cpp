#include <vector>
using namespace std;

//https://leetcode.com/problems/rotate-array/
/*
 * 	This is a Array question.
 *
 * 	To shift a array by k places, first we have to know that the way to reduce the processing is to make k MODULO the
 * 	length of the array, this is because we never need to shift the elements by more than or equal to the length times.
 * 	If K is greater than the length of the array, shifting it that much will eventually rotate back to a cycle, which
 * 	is the initial state. Therefore,
 * 		k = k % len
 * 	where if k now ends up 0, that means we no need to shift it and just return as it is
 *
 * 	-----------------------------------------------------------------------------------------------------------
 *
 * 	The first solution is to use extra O(N) space. For every element, we know where the element will be after shifted,
 * 	by calculating ( index + shift ) % len.
 * 	Save the result in extra array, then copy it back after complete.
 *
 * 	-------------------------------------------------------------------------------------------------------------
 *
 * 	The second solution intuition is, Since we know that where every element will end up, we can put that element in the
 * 	respective place already,
 *
 * 	Problem is, where shall the original element in that place go? Will it be destroyed forever?
 *
 * 	We could use a variable to store the element before its place get replaced. Now, since the variable contains that
 * 	replaced element, we shall proceed to place that replace element to its correct place. We can store the index in
 * 	another variable, and we can keep calculating the next index to be replaced based on that.
 *
 * 	If we keep doing the above step, eventually we would end up shifting all the elements into the correct place, when
 * 	we have finally gone a full loop and returned to the initial index... Right?
 *
 * 	See the example [1,2,3,4,5,6] and k = 2. Say we started index 0, the loop goes like this:
 * 		0 -> 2 -> 4 -> 0
 * 	Observe that we only moved the elements at index 0,2,4 to its correct place. Index 1,3,5 are ignored!
 * 	This is due to another loop in the array, which is
 * 		1 -> 3 -> 5 -> 1
 * 	Notice if there is a loop similar to this, it will always start at the previous initial index's next index.
 * 	Initial index 0 -> Next loop in index 1. (There will never be a case where a loop ends up one next to other,
 * 	except k = 1)
 *
 * 	To solve this problem, We have to deal with all cycles. Keep a counter to keep track of elements solved. When the
 * 	number of element dealt is still less than the actual amount of elements, continue next iteration with the initial
 * 	index set to one higher than previous one.
 *
 * 	----------------------------------------------------------------------------------------------------------
 *
 * 	Notice the pattern to all solutions:
 * 	1 - 2 - 3 - 4 - 5 - 6 - 7
 *
 * 	Say if k = 3,
 *
 * 	( 5 - 6 - 7 ) - ( 1 - 2 - 3 - 4 )
 *
 * 	It is like as if one subarray is swapped with another subarray. If that is it, how can we swap the places of those
 * 	2 subarrays?
 * 	When we reverse the array, the backmost element will go to the front, while the frontmost element will go to back.
 * 	Now, if we were to apply the reverse again, it will go back to normal order. If we apply it to certain range,
 * 	then it will be as if the subarray are moved to the certain part of the array!
 *
 * 	Reversed:
 * 	7 - 6 - 5 - 4 - 3 - 2 - 1
 *
 * 	Reverse Front 3:
 * 	5 - 6 - 7 - 4 - 3 - 2 - 1
 *
 * 	Reverse Back 4:
 * 	5 - 6 - 7 - 1 - 2 - 3 - 4
 *
 */


class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        // Cap rotation to be below nums.size()
        k %= nums.size();
        if (k == 0) return;

        int rotations = 0;
    
        for (int i = 0; rotations < nums.size(); ++i)
            rotations += rotate(nums, k, i);
    }


    // Simply begin the DFS approach to rotate the array given a start position. Stops when it
    // loops back to the beginning position
    int rotate(vector<int>& nums, int k, int p) {
        int rotated = 0;
        int curr = p;
        int hold = nums[curr];


        do {
            ++rotated;
            int nextpos = (curr + k) % nums.size();
            int temp = nums[curr];

            nums[curr] = hold;
            hold = temp;
            curr = nextpos;
        } while (curr != p);

        nums[p] = hold;
        return rotated;
    }

};