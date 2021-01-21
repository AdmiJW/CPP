#include <vector>
#include <queue>
using namespace std;



class Solution {
public:

	//	Brute force solution.
	//	Easily Time Limit Exceeded
	vector<int> mostCompetitive(vector<int>& nums, int k) {
		const int len = nums.size();
		vector<int> res(k, 0);
		int pt = 0; 
		int startingP = 0;

		for (int i = 0; i < k; ++i) {
			startingP = findMinInRange(nums, startingP, len - k + i);
			res[pt++] = nums[startingP];
			++startingP;
		}

		return res;
	}
	int findMinInRange(vector<int>& nums, int start, int end) {
		int minIdx = start;

		for (int i = start; i <= end; ++i)
			if (nums[i] < nums[minIdx]) minIdx = i;

		return minIdx;
	}



	//	Heap Solution - Keep a Heap of size K. At the end sort them by index and return
	class comparator1 {
	public:
		bool operator() (const pair<int, int>& l, const pair<int, int>& r) {
			return (l.first < r.first);
		}
	};
	vector<int> mostCompetitive(vector<int>& nums, int k) {
		const int len = nums.size();
		priority_queue< pair<int, int>, vector<pair<int, int>>, comparator1 > heap;

		for (int i = 0; i < len; ++i) {
			int n = nums[i];

			while (!heap.empty() && heap.top().first > n && k - heap.size() + 1 <= len - i)
				heap.pop();

			if (heap.size() < k) heap.emplace(make_pair<>(n, i));
		}

		vector< pair<int, int>> li(k);
		for (int i = 0; i < k; ++i) {
			li[i] = heap.top();
			heap.pop();
		}
		sort(li.begin(), li.end(), [](auto x, auto y)-> bool {
			return x.second < y.second;
			});
		vector<int> res(k);
		for (int i = 0; i < k; ++i) res[i] = li[i].first;

		return res;
	}


	//	Stack based solution - Implementation using array and pointer
	vector<int> mostCompetitive3(vector<int>& nums, int k) {
		const int len = nums.size();
		vector<int> res(k);
		int pt = 0;

		for (int i = 0; i < len; ++i) {
			int n = nums[i];

			//	While there still elements in Stack, the top element is greater, and
			//	The element required to fill res array after popping is less than or equal to elements
			//	left in array
			while (pt > 0 && res[pt - 1] > n && k - pt + 1 <= len - i)
				--pt;

			//	If after popping there is available space, push to Stack
			if (pt < k) res[pt++] = n;
		}

		return res;
	}
};