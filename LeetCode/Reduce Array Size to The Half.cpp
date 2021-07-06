#include <vector>
#include <queue>
#include <unordered_map>
using namespace std;

//https://leetcode.com/problems/reduce-array-size-to-the-half/
/*
 * This is a Hash Table (HashMap), PriorityQueue / Sorting problem which revolves around idea of Greedy Algorithm
 *
 * 	If I want to remove an integer, of course I want to remove the one with largest frequency first. This is greedy
 * 	To achieve this, I must obtain the frequencies of all elements in the array beforehand.
 * 	Then, from the frequencies, sort them in decreasing order, then always remove the largest element first. That's it
 * 
 *	Overall time complexity is O(N log N)
 */

class Solution {
public:
	int minSetSize(vector<int>& arr) {
		int len = arr.size();
		const int target = len / 2;
		int res = 0;

		// Frequency table in O(N)
		unordered_map<int, int> freq;
		for (int i : arr)
			++freq[i];

		// Sort the frequencies, we can use Heap in this, giving us maximum element at first
		priority_queue<int> heap;
		for (auto& i : freq)
			heap.push(i.second);

		while (len > target) {
			len -= heap.top(); heap.pop();
			++res;
		}
		return res;
	}
};