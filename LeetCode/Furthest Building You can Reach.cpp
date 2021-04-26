#include <queue>
#include <vector>
using namespace std;

//https://leetcode.com/problems/furthest-building-you-can-reach/
/*
 *	This is a heap problem.
 *
 * 	Say we have to climb up a series of heights. How do we know when to use ladders, and when to stack up
 * 	bricks?
 *
 *	Borrowing some idea from Dynamic Programming, we start from bottom up approach. Aka, we start by answering
 *	the smaller subproblems, which is whether can I climb up until nth building first where n starts from 1, 2...
 *
 *	From buildings 0 to buildings i, I have a series of heights to climb. Therefore, turns out:
 *	>	Using ladders on the maximum heights, maximizes the chance of ability to use bricks to climb
 *	>	If I have 3 heights to climb, and 3 ladders, of course we are going to use all ladders, without having to consider
 *
 *	So, how do we able to know the first L maximum heights in a given range of buildings? Turns out Heap was the perfect
 *	choice for this case.
 *	The priority queue is maintained at size equal to number of ladders available. The priority queue is going to be min
 *	heap, so if were to insert a greater height, we can simply pop out the smallest height to use bricks.
 *
 *	For every new building introduced, we check if we now have to climb the height greater than the smallest height in priority
 *	queue.
 *		>	If heightToClimb > heap.peek(), pop out the heap's minimum height and use bricks on it. Push heightToClimb into
 *			heap
 *		>	If heightToClimb <= heap.peek(), then current height was to be climbed using bricks
 *		>	If size of heap is smaller than ladders available, use ladder when we can. So push to heap current height
 *
 *	If suddenly the number of bricks left go negative, that means we are unable to climb the current building. Return index - 1
 */

struct compare {
public:
	bool operator()(int& a, int& b) // overloading both operators 
	{
		return a > b;
	}
};


class Solution {
public:
	int furthestBuilding(vector<int>& heights, int bricks, int ladders) {
		priority_queue<int, vector<int>, compare> pq;

		for (int i = 1; i < heights.size(); ++i) {
			int diff = heights[i] - heights[i - 1];
			if (diff <= 0) continue;

			if (pq.size() < ladders) pq.push(diff);
			else if (!pq.empty() && pq.top() < diff) {
				bricks -= pq.top(); pq.pop();
				pq.push(diff);
			}
			else
				bricks -= diff;

			if (bricks < 0) return i - 1;
		}
		return heights.size() - 1;
	}
};