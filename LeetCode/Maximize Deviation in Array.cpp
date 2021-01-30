#include <queue>
#include <vector>
using namespace std;

//https://leetcode.com/problems/minimize-deviation-in-array/
/*
 * 	YES, this is a HARD Heap/ TreeSet problem.
 *
 * 	PS: Although I misread the question and thought that the differences must calculated in adjacent elements,
 * 	which makes a hard question even harder and can't figure it out
 *
 * 	--------------------------------------------------------------
 *
 * 	Obviously, the maximum difference is always the MAX and MIN element in the array at a particular time. Also,
 * 	we can perform:
 *
 * 		>	Odd numbers can x2.
 * 			Note that after x2, it becomes EVEN. So this operation can only be done once. Realizing this is the HARD part
 * 		>	Even numbers can /2.
 *
 * 	What if we can reduce the problem to be simpler? If we multiply all odd numbers by 2, the problem will essentialy
 * 	be reduced to find maximum diff in array of EVEN numbers only!
 *
 * 	The idea is as follows: We will have a Heap-like data structure which allows us to retrieve max and min element
 * 	very fast. Pop the maximum element out. Calculate the difference with min element. Now, if it is even, we can reduce
 * 	it further by /2, and returning it to array. Keep doing it until you encounter that max element is odd number.
 * 	This is because we cannot further reduce odd number down by /2! It's against the rules.
 */


class Solution {
public:

	int minimumDeviation(vector<int> nums) {
		int min = INT32_MAX;
		int res = INT32_MAX;
		priority_queue<int> heap;

		for (int i : nums) {
			heap.push(i % 2 ? i* 2 : i);
			min = fmin(i % 2 ? i * 2 : i, min);
		}

		while (1) {
			int max = heap.top(); heap.pop();

			res = fmin(res, max - min);

			if (max % 2) break;	//	Maximum is odd. We cannot reduce further by dividing 2

			heap.push(max / 2);
			min = fmin(max / 2, min);
		}
		return res;
	}

};