#include <vector>
#include <cmath>
using namespace std;

//https://leetcode.com/problems/range-sum-query-mutable/
/*
 * 	By doing this problem, I learned Sqrt Decomposition
 *
 * 	This is a Segment tree / Square Root Decomposition problem, which are advanced data structures.
 * 	Both of them are recorded in Data Structures directory. Visit for more info.
 *
 * 	Ideally in an interview, it should be solved using Sqrt Decomposition due to time constraints.
 * 	Otherwise, Segment tree would be better due to the time complexity of log2N is faster than sqrt(N)
 *
 */

class NumArray {
	int blockSize;
	vector<int> arr;
	vector<int> sums;
public:
	NumArray(vector<int>& arr) {
		blockSize = ceil(sqrt(arr.size()));
		sums = vector<int>(blockSize, 0);
		this->arr = arr;

		for (int i = 0; i < arr.size(); ++i)
			sums[i / blockSize] += arr[i];
	}

	void update(int index, int value) {
		int diff = value - arr[index];
		arr[index] = value;

		sums[index / blockSize] += diff;
	}

	int sumRange(int from, int to) {
		int leftBlock = from / blockSize;
		int rightBlock = to / blockSize;
		int sum = 0;

		//	If they are from within same block, simply sum
		if (leftBlock == rightBlock) {
			while (from <= to) sum += arr[from++];
			return sum;
		}

		//	Otherwise it involves 2 or more blocks.
		for (int i = from; i <= (leftBlock + 1) * blockSize - 1; ++i)
			sum += arr[i];
		for (int i = leftBlock + 1; i <= rightBlock - 1; ++i)
			sum += sums[i];
		for (int i = rightBlock * blockSize; i <= to; ++i)
			sum += arr[i];
		return sum;
	}
};