
#include <queue>
#include <vector>
#include <iostream>
using namespace std;

//https://leetcode.com/problems/the-skyline-problem/

/*
 * 	This is a Heap problem / Divide and Conquer / Segment Tree / Line Sweep problem
 *
 * 	We want to construct the skyline contour, which is just an array of points where the horizontal line occurs a change
 * 	in its y position, either up or down. Intuitively, it only occurs when:
 * 		>	We encounter a new building
 * 		>	We reached the end of a building
 *
 * 	Now, the buildings are already sorted by start value, so from left to right is guaranteed the encounter of buildings.
 *
 * 	Now let's think detail: When we encounter a building:
 * 		>	The building start value is further than current building's end value - Not yet reach
 * 				Please leave the current building first
 *
 * 		>	The building start value is inside the current building's end value - Reached
 *
 * 				- The new building is higher.
 * 					If the building is higher, no matter what we would experience a change in y value. However, let's see:
 * 					-	If the current building ends before the new building ends, then current building is useless already! DIscard
 * 					-	Otherwise the current building ends after new building ends. The current building maybe still used later.
 * 						Store somewhere
 *
 *				- The new building is lower
 *					If the building is lower, current building wins and no change in y occur. However, in some cases the new
 *					building may still be useful:
 *					-	If the current building ends before the new building ends, then the new building may still be used. Store
 *						somewhere
 *					-	Otherwise the current building ends after new building ends. The new building is useelss because its shorter
 *						and ends earlier. New Building is 'inside' current building. Discard
 *
 *
 *	We keep talking about storing the building somewhere for later use, especially when we reach endpoint of current building. How?
 *	Consider we reached the end of current building which is tallest. What we really want is the next second tallest building!
 *	A heap will do this very well, as heap can sort the buildings in descending height automatically.
 *
 *	Remember that a heap may have useless buildings. The ones which are shorter and ended earlier than current building. Discard them
 *	upon encounter.
 *
 *	Onto edge cases, when we encounter buildings which are equal in start and end point, but different in height values, we would
 *	only want to take the highest building only. Discard the rest.
 *
 *	-------------------------------------------------------
 *
 *	Heap allows for O(log N) insertion and heapify (When removed) operation. THerefore time complexity of this solution is
 *	O(N log N). Space is O(N). At worst case, all cities will be pushed into heap.
 *
 *	Note that a BST tree solution is also applicable (TreeMap/Set). However, BST takes O(log N) for all operations. Not much
 *	difference in big dataset
 */

class Solution {
public:
	vector<vector<int>> getSkyline(vector<vector<int>>& buildings) {
		vector<vector<int>> res;
		auto comparator = [](vector<int>* a, vector<int>* b) -> bool {
			return (*b)[2] - (*a)[2] > 0;
		};
		priority_queue<vector<int>*, vector<vector<int>*>, decltype(comparator)> heap(comparator);

		const int len = buildings.size();
		int idx = 0;
		vector<int>* curr = nullptr;

		while (idx < len) {
			//	Introduce a new element. Only add when current focus block is null, or the current block's end
			//	is greater than the next block's start.
			if (!curr || (*curr)[1] >= buildings[idx][0]) {
				vector<int>* toAdd = &buildings[idx++];

				//	If the next building has same start point, greater or equal end,
				//	and equal height or greater than current, then ignore this one
				if (idx < len && buildings[idx][0] == (*toAdd)[0] && buildings[idx][1] >= (*toAdd)[1] && buildings[idx][2] >= (*toAdd)[2])
					continue;

				//	Current is null. Just select next block as current and record because we just rise from ground
				if (!curr) {
					curr = toAdd;
					res.emplace_back(vector<int> {(*toAdd)[0], (*toAdd)[2]});
				}
				//	If the block to add is shorter in height
				else if ((*toAdd)[2] <= (*curr)[2]) {
					//	Only useful if it is longer end than current. Otherwise useless
					if ((*toAdd)[1] > (*curr)[1])
						heap.push(toAdd);
				}
				//	If the block to add is higher
				else {
					//	If it is less longer, Current block may still be used later. Push to heap while toAdd
					//	becomes the current
					if ((*toAdd)[1] < (*curr)[1])
						heap.push(curr);
					//	Regardless, we encountered a higher one. It must be used as current now.
					curr = toAdd;
					res.emplace_back(vector<int> {(*curr)[0], (*curr)[2]});
				}
			}
			//	Otherwise the next block is out of reach. Lets proceed with the block in range first
			else {
				//	Try to discard useless elements first - Less long than current AND less taller than current
				while (!heap.empty() && (*heap.top())[1] <= (*curr)[1] && (*curr)[2] >= (*heap.top())[2])
					heap.pop();

				//	No more available blocks. Return to ground 0
				if (heap.empty()) {
					res.emplace_back(vector<int> {(*curr)[1], 0});
					curr = nullptr;
				}
				else {
					auto next = heap.top();
					heap.pop();
					if ( (*curr)[2] != (*next)[2])
						res.emplace_back(vector<int> {(*curr)[1], (*next)[2]});
					curr = next;
				}
			}
		}

		while (curr != nullptr) {
			//	Try to discard useless elements first - Less long than current AND less taller than current
			while (!heap.empty() && (*heap.top())[1] <= (*curr)[1] && (*curr)[2] >= (*heap.top())[2])
				heap.pop();

			//	No more available blocks. Return to ground 0
			if (heap.empty()) {
				res.emplace_back(vector<int> {(*curr)[1], 0});
				curr = nullptr;
			}
			else {
				auto next = heap.top();
				heap.pop();
				if ((*curr)[2] != (*next)[2])
					res.emplace_back(vector<int> {(*curr)[1], (*next)[2]});
				curr = next;
			}
		}
		return res;
	}
};