#include <vector>
#include <algorithm>
#include <unordered_map>
using namespace std;

//https://leetcode.com/problems/find-original-array-from-doubled-array/
/*
 * 	This is primarily a sorting + hashmap problem.
 *
 * 	In an array that has elements e - The original element that isn't doubled, and 2e, how do we identify element e,
 * 	that isnt doubled?
 *
 * 	If we sort the array, we can easily obtain the smallest element in the array. If the array is valid, then the
 * 	smallest element couldn't possibly be 2e.
 *
 * 	Therefore we will just try to eliminate the smallest element whenever possible.
 */

class Solution {
public:

    vector<int> findOriginalArray(vector<int>& changed) {
		const int len = changed.size();
		if (len % 2 != 0) return {};

		// The array has to be sorted. Imagine case [12,6,3,24]. If we don't sort, we would've paired 12 with 6!
		sort( changed.begin(), changed.end() );

		vector<int> res(len / 2, 0);
		int i = 0;
		unordered_map<int, int> map;

		for (int n : changed) {
			if (n % 2 == 0 && map.count(n / 2) && map[n / 2] > 0) {
				res[i++] = n / 2;
				--map[n / 2];
			}
			else ++map[n];
		}

		if (i != len / 2) return {};
		return res;
    }

};