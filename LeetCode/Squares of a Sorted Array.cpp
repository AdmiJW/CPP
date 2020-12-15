
#include <vector>
using namespace std;

//https://leetcode.com/problems/squares-of-a-sorted-array/
/*
 * 	This is a Two pointers array problem. First attempted in Arrays section. Now revisited
 *
 * 	No matter if a number is negative or positive, when it is squared, it will become positive regardless
 * 	Therefore it is the MAGNITUDE of the number that is important
 *
 * 	Notice this sorted array:
 * 			-10, -5, 0, 3, 7
 *
 * 	The magnitude starts out large, then become smaller, then eventually after the negative part and arrived
 * 	positive part, it begins to become large again.
 *
 * 	Therefore a idea comes to mind. Use two pointer and compare each time: which one is more suited to fill into
 * 	the result array next. The suitable one will have its square inserted, and pointer moved.
 *
 * 	-------------------------------------------------------------------
 *
 * 	The INSIDE OUT approach utilizes linear scan (or better yet, binary search) to find out the first non negative
 * 	element's index. Then put the 2 pointer:
 * 		Positive pointer: the result of binary search - First non negative element
 * 		Negative pointer: the previous element of the first non negative element must be negative!
 *
 * 	Now, each time, compare. The one with smaller magnitude, will have the square inserted into res array. Do until
 * 	all elements is inserted
 *
 * 	--------------------------------------------------------------------
 *
 * 	Upon observation, the both ends of the array are actually large in magnitude. Therefore, we can also initialize
 * 	the two pointers to be point at the maximum magnitude first, and begin shrinking down to center.
 *
 * 	This means the result array has to be filled reversely. However this elimiates the need of linear scan or
 * 	binary search
 */

class Solution {
public:
	vector<int> sortedSquares(vector<int>& nums) {
		const int len = nums.size();
		int posPt = binarySearch(nums);
		int negPt = posPt - 1;

		vector<int> res;
		res.reserve(len);

		//	There is still comparison need to be done
		while (posPt < len && negPt >= 0) {
			//	Positive number pointer is larger
			if (nums[posPt] + nums[negPt] > 0) {
				res.push_back(nums[negPt] * nums[negPt]);
				--negPt;
			}
			else {
				res.push_back(nums[posPt] * nums[posPt]);
				++posPt;
			}
		}
		while (posPt < len)
			res.push_back(nums[posPt] * nums[posPt++]);
		while (negPt >= 0)
			res.push_back(nums[negPt] * nums[negPt--]);

		return res;
	}

	vector<int> sortedSquares2(vector<int>& nums) {
		const int len = nums.size();
		vector<int> res(len, 0);

		int idx = len;
		int left = 0, right = len - 1;
		while (left <= right) {
			if (abs(nums[left]) > abs(nums[right]))
				res[--idx] = (nums[left] * nums[left++]);
			else
				res[--idx] = (nums[right] * nums[right--]);
		}
		return res;
	}


	//	Returns the index of the first non-negative index O(log N) time, given that the array is sorted.
	int binarySearch(vector<int>& nums) {
		int left = 0;
		int right = nums.size();

		while (left < right) {
			int mid = left + (right - left) / 2;

			if (nums[mid] < 0)
				left = mid + 1;
			else
				right = mid;
		}
		return left;
	}
};