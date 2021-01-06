#include <vector>
using namespace std;

//https://leetcode.com/problems/kth-missing-positive-number/
/*
 * 	This is a array linear scan / binary search problem.
 *
 * 	For linear scan solution, we keep a variable that stores the supposed next number that we should encounter.
 * 	Initially, the number that we should encounter is 1.
 *
 * 	For each element we encounter, we can calculate how many numbers it had missed, by checking
 * 			arr[i] - supposed
 *	Eg: if first element we encounter is 5. Then we missed 5 - 1 = 4 elements (1,2,3,4)
 *
 *	Check if the number we are finding is within the missed numbers, by checking if k <= diff.
 *	If it is within the missed numbers, since we know the missed numbers are all in increasing sequence,
 *	we take the supposed number plus the k (The kth missing number we are finding), but minus 1 since the supposed
 *	number also counts as 1.
 *
 *	Otherwise, minus k from the missing number already occurred. Then continue.
 *
 *	If until the end we haven't reach the missing number, it is simply the last element's value + kth missing number
 *	ahead.
 *
 *	------------------------------------------------------------
 *
 *	At any index i, the number that shall be inside it shall be i+1. If it is greater, we can know how many missing numbers
 *	had passed by taking
 *			arr[i] - i - 1;
 *
 *	This leads to binary search solution. Find the leftmost position which the element had missed the number we are finding.
 *
 *	Since we are at index i that are supposed to have value i+k, but yet we missed m values there, it means
 *	the value we are finding shall be
 *
 *			i + k
 *
 *	Since between arr[i] and arr[i+1], the missing numbers are in sequence.
 */

class Solution {
public:
	int findKthPositive(vector<int>& arr, int k) {
		int supposed = 1;

		for (int i : arr) {
			int diff = i - supposed;

			if (k <= diff) return supposed + k - 1;

			k -= diff;
			supposed = i + 1;
		}
		return arr[arr.size() - 1] + k;
	}


	int findKthPositive2(vector<int>& arr, int k) {
		const int len = arr.size();
		int left = 0, right = len;

		while (left < right) {
			int mid = left + (right - left) / 2;
			int diff = arr[mid] - mid - 1;

			if (k > diff) left = mid + 1;
			else right = mid;
		}
		return left + k;
	}
};