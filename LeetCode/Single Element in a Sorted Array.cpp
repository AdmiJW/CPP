#include <vector>
using namespace std;

//https://leetcode.com/explore/challenge/card/may-leetcoding-challenge/535/week-2-may-8th-may-14th/3327/
/*
 * 	This is a binary search problem.
 *
 * 	If the array is not sorted, we could do best in O(N) time using XOR technique. However, since it is sorted, we know
 * 	for certain all pairs occur adjacently. Therefore, we easily try to utilize binary search here. This does not have
 * 	anything to do with sorted, just that they are adjacently paired.
 *
 * 	- Firstly, the array must be odd lengthed. This is because of Length = 2(no of pairs) + 1 single element
 *
 *
 * 	My intuition comes from observing an array without the single element, let's see:
 * 	[1,1,2,2,3,3,4,4,5,5]
 * 	At any single index i, observe:
 * 		If i is odd, then arr[i] should equal to arr[i-1]
 * 		If i is even, then arr[i] should equal to arr[i+1]
 *
 * 	The binary search serves to narrow the search range by half, by eliminating the half part which the single element
 * 	could not possibly be at. How to know if a single element could not possibly be in a subarray? By checking if the
 * 	subarray satisfies the 2 condition above. That is, the subarray only consist of pairs, no single element.
 *
 *
 *
 * 	Then, we come up with an algorithm:
 *
 * 		If i is odd:
 * 			If arr[i-1] == arr[i] then single element must be to the right (Left side is all pairs)
 * 			Else single element must be to the left
 *		If i is even:
 *			If arr[i] == arr[i+1] then single element must be to the right (Left side is all pairs)
 *			Else single element must be to the left
 */

class Solution {
public:
    int singleNonDuplicate(vector<int>& nums) {
        const int len = nums.size();
        int l = 0, r = len - 1;

        while (l < r) {
            int mid = l + (r - l) / 2;

            // Odd index.
            // If previous element is same then single element > mid
            // otherwise single element <= mid
            if (mid % 2) {
                if (mid != 0 && nums[mid - 1] == nums[mid]) l = mid + 1;
                else r = mid;
            }
            // Even index.
            // If next element is same then single element is > mid
            // Otherwise the single element <= mid
            else {
                if (mid != len-1 && nums[mid + 1] == nums[mid]) l = mid + 1;
                else r = mid;
            }
        }

        return nums[l];
    }
};