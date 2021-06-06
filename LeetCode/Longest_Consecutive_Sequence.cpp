#include <unordered_set>
#include <unordered_map>
#include <vector>
using namespace std;

//https://leetcode.com/problems/longest-consecutive-sequence/
/*
 * 	This is a Array / Hashset problem.
 *
 * 	My initial solution is to construct intervals from the numbers given. Every element can be in either of cases:
 *
 * 	>	Standalone element. No element i-1 and i+1 encountered so far.
 * 	>	Middle element. i-1 and i+1 is encountered already. Merge the intervals
 * 	>	Tail element. i-1 is encountered before, but not i+1.
 * 	>	Head element. i+1 is encountered before, but not i-1
 *
 * 	First, duplicate elements should never be considered for this algorithm to work.
 * 	Have 2 hashmap, toFrom and fromTo.
 * 	>	toFrom maps from end of interval to start of interval. Eg: 5->1 means there is a interval 1 to 5
 * 	>	fromTo maps from start of interval to end of interval. Eg: 1->5 means there is a interval 1 to 5
 *
 * 	In each of the four cases above, perform the appropriate operations to construct / merge intervals in both Hashmap.
 * 	Also, check to see if the interval size is so far largest.
 *
 * 	===============================================================
 *
 * 	The official solution was to first obtain the ability to query presence of each number in array in O(1) time.
 * 	Then, iterate each element.
 *
 * 	If element was potentially the head of a sequence, checked by see if i-1 is present in the array or not,
 * 	then we will determine the length of the sequence.
 *
 * 	This is O(N) time algorithm and O(N) space.
 */

class Solution {
public:

	int longestConsecutive(vector<int>& nums) {
		if (nums.size() == 0) return 0;

		unordered_set<int> set;
		unordered_map<int, int> fromTo;
		unordered_map<int, int> toFrom;
		int res = 1;

		for (int i : nums) {
			//	Do not consider duplicate elements
			if (!set.insert(i).second) continue;

			// Case 1: ... e ...
			if (toFrom.count(i - 1) && fromTo.count(i + 1)) {
				int leftmost = toFrom[i - 1];
				int rightmost = fromTo[i + 1];

				fromTo[leftmost] = rightmost;
				toFrom[rightmost] = leftmost;

				toFrom.erase(i - 1);
				fromTo.erase(i + 1);

				res = max(rightmost - leftmost + 1, res);
			}
			//	Case 2: ... e X
			else if (toFrom.count(i - 1)) {
				int leftmost = toFrom[i - 1];
				fromTo[leftmost] = i;

				toFrom.erase(i - 1);
				toFrom[i] = leftmost;

				res = max(res, i - leftmost + 1);
			}
			//	Case 3: X e ...
			else if (fromTo.count(i + 1)) {
				int rightmost = fromTo[i + 1];
				toFrom[rightmost] = i;

				fromTo.erase(i + 1);
				fromTo[i] = rightmost;

				res = max(res, rightmost - i + 1);
			}
			//	Case 4: X e X - Individual element
			else {
				fromTo[i] = i;
				toFrom[i] = i;
			}
		}
		return res;
	}


	//	Best optimized solution - Single HashSet
	int longestConsecutive2(vector<int>& nums) {
		unordered_set<int> setOfNums(nums.begin(), nums.end());
		int res = 0;

		for (int i : setOfNums) {
			//	If the number is potentially the HEAD of a sequence (No prev elem)
			if (!setOfNums.count(i - 1)) {
				int streak = 0;
				for (int curr = i; setOfNums.count(curr); ++curr)
					++streak;
				res = max(streak, res);
			}
		}
		return res;
	}
};