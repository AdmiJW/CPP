#pragma once

#include <iostream>
#include <string>
#include <deque>

//https://www.hackerrank.com/challenges/deque-stl/problem

/*
*	A problem which asks to generate all possible subarrays of given length k, and find maximum element in it.
* 
*	A good solution is by using Deque, which solves it in O(N) time complexity
* 
*	The deque will be storing index. Index of elements which are useful:
*		>	Within range of the window
*		>	The head of the deque is always the index to the maximum element
* 
*	Therefore we will create a deque, and initialize the sliding window first. 
* 
*	We basically do the following steps:
*		While the deque is not empty, and the value at the back of the deque is smaller (or equal) to the currently introduced
*		value, keep popping those elements out. They are proved useless
*		Out of the loop, we push the current index into the back of the deque.
*	This way, we always eliminate the elements that are smaller in the window range, and ensuring the maximum element is always
*	at the head of the deque.
* 
*	>	WHY we MUST push the newly introduced value? This is because when we sliding the window, the maximum value may go out
*		of range. This way the next element in the deque after front element is popped, shall be the second maximum value which
*		is valid in the range. Essentially it is like storing a backup value
* 
*	Now, we will begin to slide the window. Everytime we slide the window, we have to do extra 2 steps:
*		>	Print out the value at head of deque. That is the maximum of the previous sliding window!
*		>	Check to see if the head of the deque is out of the window range. If it is, pop it out
*		Then we repeat the above steps of pushing the new introduced value into the back of deque.
* 
*	Essentially at the end of loop, we need to print one last time the head value of the deque. This is the maximum element
*	at the last, rightmost sliding window
*		
*/



//	This function is called when we are about to push a new index into the deque.	
void update(std::deque<int>& useful, int* arr, int idx) {

	int value = arr[idx];

	//	While the first element of the deque is less than the current value, pop it out
	while (!useful.empty() && arr[ useful.back() ] <= value) {
		useful.pop_back();
	}

	//	Now either the deque is empty, or the element before it is actually greater than current value. Push the index
	useful.push_back(idx);
}

void printKMax(int arr[], int n, int k) {
	std::deque<int> useful;

	//Initialize the deque
	for (int i = 0; i < k; i++) {
		update(useful, arr, i);
	}


	//Then we begin sliding the window in each step.
	for (int i = k; i < n; i++) {
		//	Print out the maximum element of the subarray prior to this sliding action
		std::cout << arr[ useful.front() ] << " ";

		/*
		* Eliminate the out of range index in the deque.
		* Since every time a new value is encountered, it is always pushed at the back, so it's impossible for a index in deque
		* at front to be larger than the element at back
		* Also, the sliding window slides only 1 step each iteration. Therefore, we only have to check the head of the deque
		* since it's impossible for second element to out of range proven
		*/
		if (!useful.empty() && useful.front() <= i - k) {
			useful.pop_front();
		}

		update(useful, arr, i);
	}

	std::cout << arr[ useful.front() ] << std::endl;

}