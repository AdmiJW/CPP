#include <vector>
using namespace std;

//https://leetcode.com/problems/beautiful-arrangement-ii/
/*
 * 	This is a Array question which challenges your problem solving ideas.
 *
 * 	You want to create an array with elements 1 to n, and having their differences to be having k different integers.
 * 	Intuitively, you want to complete the array as early as possible, like if you have k = 3, then you may
 * 	want to have an array such that
 * 			[1,2,4,7...]		<- See how I included 3 differences as early as possible?
 *
 * 	There are problems with above approach. Say if N=5, then above approach won't work anymore. The number easily go out
 * 	of bounds.
 * 	Therefore we have to utilize the absolute difference property. That is, -3 also counts as integer 3.
 * 	Then, when is the best time to decrement, and when is the best time for increment?
 * 		>	Turns out, it's best if we started with maximum difference, going way down to 1.
 * 		>	Also, we increment and decrement the difference alternatively.
 *
 * 	See:
 * 			n = 10, k = 6
 *
 * 		[1, 7, 2, 6, 3, 5, 4, ...]		<- See how differences alternate can prevent out of bounds, while still having k
 * 										   differences
 *
 * 	Diff: [6,-5,4,-3,2,-1, ...]
 *
 *
 * 	Then, what do we fill in afterwards after above approach? The space remaining we can just fill in the remaning number in
 * 	ascending order. Our array is split in 2 parts:
 *
 * 		[The part that makes up k differences | The remaining part ]
 *
 * 	The maximum element in first half is gonna be 1+k. Therefore, we could just start the remaining part with 2+k, and go
 * 	up accordingly. It will not create a new difference into the array.
 *
 */

class Solution {
public:
	vector<int> constructArray(int n, int k) {
		vector<int> res(n, 1);
		int remaining = k;

        //	First half: Alternating differences to create k diff
        for (int i = 1; remaining != 0; ++i) {
            res[i] = res[i - 1] + remaining;
            remaining = remaining < 0 ? -remaining - 1 : -(remaining - 1);	//	Decreases Magnitude by 1 everytime, depends on sign
        }

        //	Fill in remaining spaces via their index
        for (k = k + 1; k < n; ++k)
            res[k] = k + 1;

        return res;
	}
};