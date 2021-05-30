#include <vector>
using namespace std;

//https://leetcode.com/problems/maximum-gap/
/*
 * 	This is a sorting problem.
 *
 * 	You are required to find out sorted array properties in linear time. Well, there are surely
 * 	some linear time sorting algorithms, but with some constraints.
 *
 * 	In this case, one particular sorting algorithm that can be fitted is radix sort, which we sort
 * 	by each places, from smallest to largest. The maximum iterations needed are dependent on number
 * 	of digits on largest magnitude number, which is 10 in this case. Within each iteration we linear
 * 	scan 2 times through the array. Estimated time complexity is approximately O( 10(2N) + N )
 *
 * 	----------------------------------------------------------------------
 *
 * 	There is another ingenious idea (from LC solution), which is bucket sort based.
 *
 * 	First, once we know about the maximum and minimum elements in the array, is there a way that we
 * 	can split them into buckets, such that
 * 		>	THE MAXIMUM DIFFERENCE BETWEEN ELEMENTS WITHIN BUCKET, WILL NEVER BE LARGER THAN THE MAXIMUM
 * 			DIFFERENCE BETWEEN BUCKETS?
 *
 * 		> 	Say we have N elements. Minimum case where maximum difference between two elements, is when
 * 			the elements are spaced very, very evenly.
 * 			Thus: ( (max - min) / N-1 )
 *
 * 		> 	Therefore, we could create the buckets each with that possible size. Each bucket is responsible
 * 			for that certain range of numbers, and only records the maximum and minimum number of that size.
 *
 * 		>	At the end, we only need to iterate through the buckets, matching current bucket's max with next
 * 			bucket's min, to find out the maximum difference.
 */

class Solution {
public:

	//	Radix sort solution
	int maximumGap(vector<int>& nums) {
		if (nums.size() < 2) return 0;
		int res = 0;

		//	Perform radix sort
		for (int i = 1; i <= 10; ++i)
			nums = radixSort(nums, i);

		//	Find consecutive difference.
		for (int i = 1; i < nums.size(); ++i)
			res = max(nums[i] - nums[i - 1], res);
		return res;
	}


	vector<int> radixSort(vector<int>& nums, int places) {
		vector<int> res(nums.size(), 0);
		int table[11] = {};

		int divisor = (int)(pow(10, places - 1));

		for (int n : nums)
			++table[(n / divisor) % 10 + 1];

		for (int i = 1; i < 11; ++i)
			table[i] += table[i - 1];
		for (int i = 1; i < 11; ++i)
			--table[i];

		for (int i = nums.size() - 1; i >= 0; --i) {
			int d = (nums[i] / divisor) % 10;
			int idx = table[d + 1];

			res[idx] = nums[i];
			--table[d + 1];
		}
		return res;
	}
};