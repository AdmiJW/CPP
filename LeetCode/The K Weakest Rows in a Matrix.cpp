#include <vector>
#include <queue>
using namespace std;

//https://leetcode.com/problems/the-k-weakest-rows-in-a-matrix/
/*
 * Generally when we see the Kth smallest or Kth largest, it is a good idea to use Heap, since it allows us to
 * use only K spaces.
 *
 * Traverse through the matrices row by row. We can get the power of each row by following:
 * 	>	Naive counting - O(N) where N is number of elements in a row
 * 	>	Binary search - O(Log N) since every army is at front
 *
 * Then, store them as pair of index:value so that index can be compared in case power is same in the heap. The heap
 * will handle the sorting
 * Once heap size exceeded K, pop out the useless value, which is largest one. Therefore we'll use max heap for the job
 *
 * 	If use binary Search n heap, time will be O(M log N) where M is row, and N is col. If use linear scan, then it is
 * 	O(MN) instead.
 * 	Space is maintained in O(K)
 */

class TheComparator {
public:
	bool operator() (const pair<int, int>& l, const pair<int, int>& r) const {
		if (l.second == r.second) return r.second > l.second;
		return r.first > l.first;
	}
};


class Solution {
public:
	vector<int> kWeakestRows(vector<vector<int>>& mat, int k) {
		//	Stores Pair : <idx, val>
		priority_queue<pair<int, int>, std::vector<pair<int, int>>, TheComparator> heap;

		for (int i = 0; i < mat.size(); ++i) {
			heap.emplace(make_pair<>(i, linear(mat[i])));
			if (heap.size() > k) heap.pop();
		}

		vector<int> res(k);
		for (int i = k - 1; i >= 0; --i)
			res[i] = heap.top().first; heap.pop();

		return res;
	}



	int linear(vector<int>& arr) {
		int n = 0;
		for (int i : arr) {
			if (!i) break;
			++n;
		}
		return n;
	}


	int binarySearch(vector<int>& arr) {
		int l = 0, r = arr.size();
		while (l < r) {
			int mid = l + (r - l) / 2;
			if (arr[mid]) l = mid + 1;
			else r = mid;
		}
		return l;
	}
};