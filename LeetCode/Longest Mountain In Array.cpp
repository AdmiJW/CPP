
#include <vector>
#include <cmath>

//https://leetcode.com/problems/longest-mountain-in-array/solution/

class Solution {
public:

	//	Not an optimized solution. Does not use two pointers, but keep boolean state
	int longestMountain(std::vector<int>& A) {
		const int size = A.size();

		//	Size is 2 or below. Impossible
		if (size <= 2) return 0;

		int idx = 1;
		bool isFalling = true;		//	Indicates the state we are in. Initially we assume we just falled
		int len = 0;				//	Local state of length of mountain
		int res = 0;				//	Result. The maximum mountain length recorded

		//	While the starting mountain is falling, skip them.
		//	We will start at the mountain bottom
		while (idx < size && A[idx] <= A[idx - 1]) idx++;

		while (idx < size) {

			//	If the element is equal to previous element, first record the mountain length [1,2,3,2,2,2]
			//	and reset the mountain length to 0, set is Falling to true so next mountain shall be start of mountain
			//	bottom, like the above initialization loop does
			if (A[idx] == A[idx - 1]) {
				res = len > res ? len : res;
				len = 0;
				isFalling = true;
				while (idx < size && A[idx] <= A[idx - 1]) idx++;
				continue;
			}
			//	If we are in downward slope
			else if (isFalling) {
				//	Previous element is greater. Keep falling
				if (A[idx] < A[idx - 1]) len++;
				//	Otherwise encountered a upward slope. THis is a base of another mountain.
				else {
					isFalling = false;
					res = len > res ? len : res;
					len = 2;
				}
			}
			//	If we are in upward slope
			else {
				//	Previous element is greater. Previous element is the peak
				if (A[idx] < A[idx - 1]) {
					isFalling = true;
					len++;
				}
				//	Otherwise keep climbing
				else len++;
			}

			idx++;
		}

		//	If we are falling at the end of array, this is also an unrecorded mountain
		if ( A[size - 1] < A[size - 2]) {
			res = len > res ? len : res;
		}

		//	Ensure result returned is valid
		return res >= 3 ? res : 0;
	}


	//	An attempt Two Pointer Solution
	int longestMountain2(std::vector<int>& A) {
		const int size = A.size();

		//	Size is 2 or below. Impossible
		if (size <= 2) return 0;
		
		//	Base indicates the base of mountain. Initially start at 0
		int res = 0, base = 0;
		
		//	While we havent explored the entire array...
		while (base < size) {
			int peak;			//	THe peak of mountain
			int climber = base;	//	Our simulated climber

			//	While next element is greater, climb
			while (climber + 1 < size && A[climber + 1] > A[climber])
				climber++;

			//	If didn't climb, means invalid mountain. Proceed to next element
			if (climber == base) {
				base++;
				continue;
			}

			//	Now set the peak to be current position
			peak = climber;
			
			//	While next element is smaller, go downhill
			while (climber + 1 < size && A[climber + 1] < A[climber])
				climber++;

			//	If didn't move, invalid mountain. (Next element should be same as current)
			if (climber == peak) {
				base = peak + 1;
				continue;
			}

			//	Valid mountain. Record length. And since next element greater, set current position to be base
			res = std::fmax(climber - base + 1, res);
			base = climber ;
		}
		return res;
	}
};

