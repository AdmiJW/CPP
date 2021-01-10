#include <vector>
using namespace std;

//https://leetcode.com/problems/create-sorted-array-through-instructions/
/*
 * 	I couldn't solve this problem. Well, at least I learned Fenwick Tree / Binary Indexed Tree
 *
 * 	The idea is, for every element I want to insert, I would need 2 informations:
 * 		The number of elements that are strictly smaller than current value.
 * 		The number of elements that are strictly greater than current value.
 *
 * 	The naive approach would be to have a frequency array, where value->frequency. However, for querying ranges
 * 	from 0 up to n, will take O(N) time. If implement the approach will be O(N^2) which results in Time Limit Exceeded.
 *
 * 	If we use Prefix sum array, querying is fast in O(1), but updating still is O(N)!
 *
 * 	So, There is Fenwick Tree which allows for updating in O(log N) as well as querying.
 * 	Every element before inserting, query for number of elements strictly less than current value (n-1), and number
 * 	of elements strictly greater than current value (Current index - get(n) ).
 *
 * 	Then, update the fenwick tree on the current value.
 */


class Solution {
public:

	int fenwickTree[100001] = {};

	int createSortedArray(vector<int>& instructions) {
		int diff = 0;
		for (int i = 0; i < instructions.size(); ++i) {
			int n = instructions[i];
			diff = (diff + min(get(n - 1), i - get(n))) % 1000000007;
			update(n);
		}
		return diff;
	}

private:
	int get(int pos) {
		int res = 0;
		while (pos > 0) {
			res += fenwickTree[pos];
			pos -= pos & -pos;
		}
		return res;
	}

	void update(int pos) {
		while (pos < 100001) {
			++fenwickTree[pos];
			pos += pos & -pos;
		}
	}
};