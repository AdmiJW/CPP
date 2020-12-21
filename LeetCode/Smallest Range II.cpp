#include <vector>
#include <algorithm>
using namespace std;

//https://leetcode.com/problems/smallest-range-ii/

/*
 * 	This is a greedy, sort problem which can be hard to realize the idea
 *
 * 	The idea is to first sort the array. Now the maximum and minimum are at both ends of the array
 *
 * 	Then, since every element in the sorted array have to be either added K or minus K. Intuitively, the less elements
 * 	should be added K, and the greater elements should be minus K, so that we can achieve a kind of 'balance' to minimize
 * 	the extreme differences.
 *
 * 	The problem is, where? This is where we can try to iterate through the array to set each boundaries. At the boundaries,
 * 	all the elements at the left will be added K, and the elements at the right will be minus K.
 *
 * 	Does this mean O(N^2)? Actually, we don't have to check all elements as it is sorted. Ask yourself,
 *
 * 	At a boundary set and all elements applied +K or -K, which element can be the largest?
 * 		>	It can be the end of array (Max element in array) minus K, meaning that although maximum element minus K, it
 * 			remains to be largest, OR
 * 		>	It can be the last element at left boundary (The largest element to get added K) added K. Being the largest
 * 			element in left boundary, after added K can overtake the largest element minus K!
 *
 * 	Similarly, we can see which elements is smallest:
 * 		>	It can be the start of array (min element in array) plus K, meaning that although minimum element plus K, it
 * 			remains as the smallest element, OR
 * 		>	It can be the first element at right side of boundary (The first element to get minus K) minus K. Being the
 * 			smallest element in right side of boundary, after minus K, became the smallest element of array
 *
 * 	Iterate through, and update global minimum each time.
 */


class Solution {
public:
	int smallestRangeII(vector<int> A, int K) {
		const int len = A.size();
		sort(A.begin(), A.end());

		int minimumDiff = A[len - 1] - A[0];	//Initialize: All elements are added K, so actually no difference like this

		//	i = 0 means boundary is at right of first element. Try all boundaries until last element's left side
		for (int i = 0; i < len - 1; ++i) {
			int maxV = max(A[len - 1] - K, A[i] + K);
			int minV = min(A[0] + K, A[i + 1] - K);

			minimumDiff = min(minimumDiff, maxV - minV);
		}
		return minimumDiff;
	}
};