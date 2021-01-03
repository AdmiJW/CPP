#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

//https://leetcode.com/problems/check-array-formation-through-concatenation/
/*
 * 	This is an array problem, can be solved using Hashmap and Sorting
 *
 * 	-------------------------------------
 *
 * 	Since the input size is small, the problem can be solved using brute force, in O(N^2) time
 * 	We'll keep a pointer pointing to the element we're looking for in the arr.
 *
 * 	We have to iterate through the pieces array to find the subpiece which starts with the element we're looking for.
 * 	If not found, we can immediately return false already. Otherwise, initiate another loop which loops through the
 *	subarray while comparing and incrementing the arr pointer. If not match, return false.
 *
 *	Once the arr pointer reaches the end of array, it means all elements are successfully matched, therefore return true
 *
 *	-------------------------------------
 *
 *	Instead of iterating the pieces array over and over again, we can retrieve it in O(1) time if using HashMap. Store
 *	the subpieces in HashMap using their first element as key.
 *
 *	This way when we iterate the arr array, we can perform lookup in just O(1) time.
 *
 *	-----------------------------------
 *
 *	If we want O(1) space solution, sorting is best bet. Sorting opens up the opportunity to search for subpieces by
 *	binary search. Therefore resulting in O(N log N) time complexity
 */

class Solution {
public:
	bool canFormArray(vector<int>& arr, vector<vector<int>>& pieces) {
		const int len = arr.size();

		int arrPt = 0;

		while (arrPt < len) {
			int prior = arrPt;

			for (auto& piece : pieces) {
				//	Found the subpiece starting with the element in arr
				if (piece[0] == arr[arrPt]) {
					//	Iterate through the elements in subpiece, checking if it matches the order in arr
					for (int i : piece) if (i != arr[arrPt++]) return false;
					//	All elements in subpiece matches. Break out of the loop
					break;
				}
			}
			//	If the pointer doesn't move after searching for subarray,
			//	it means subarray not found. Return false.
			if (prior == arrPt) return false;
		}
		return true;
	}


	//	Map solution. Map from arr[0] -> arr
	bool canFormArray2(vector<int>& arr, vector<vector<int>>& pieces) {
		const int len = arr.size();

		unordered_map<int, vector<int>*> map;
		for (auto& piece : pieces)
			map[piece[0]] = &piece;

		int arrPt = 0;

		while (arrPt < len) {
			auto found = map.find(arr[arrPt]);
			if (found == map.end()) return false;

			for (int i : *(found->second)) {
				if (arr[arrPt++] != i) return false;
			}
		}

		return true;
	}


	//	Sorting of pieces and binary search solution.
	bool canFormArray3(vector<int>& arr, vector<vector<int>>& pieces) {
		sort(pieces.begin(), pieces.end(), [](auto& x, auto& y)->bool {
			return x[0] - y[0] < 0;
		});

		const int len = arr.size();
		int arrPt = 0;

		while (arrPt < len) {
			auto res = binarySearch(pieces, arr[arrPt]);
			if (!res) return false;

			for (int i : *res ) {
				if (i != arr[arrPt++]) return false;
			}
		}
		return true;
	}
	vector<int>* binarySearch(vector<vector<int>>& pieces, int val) {
		int left = 0;
		int right = pieces.size() - 1;

		while (left < right) {
			int mid = left + (right - left) / 2;

			if (pieces[mid][0] < val)
				left = mid + 1;
			else right = mid;
		}

		return pieces[left][0] == val ? &pieces[left] : nullptr ;
	}
};