#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

typedef long long int LONG;

//https://leetcode.com/problems/maximum-performance-of-a-team/
/*
 * 	This is a hard greedy, sorting problem.
 * 	Of course, couldn't come up with the solution. I looked at it.
 *
 *
 * 	The brute force involves generating all possible team formations, which involves backtracking and recursion,
 * 	and takes exponential time, not efficient and not satisfy the time limit.
 *
 * 	=======================================================================================
 *
 * 	The performance points is calculated by SUM(speed) * MIN(efficiency) of the team. We can see, the bottleneck
 * 	is the MIN(efficiency) there.
 *
 * 	Observe this: in the optimal solution, surely there must be a minimum efficient engineer of the whole team.
 * 	Eg in the solution where efficiencies are given by [5,8,3,6], the engineer with efficiency 3 is the one.
 *
 * 	What if we attempt to fix every engineer to have the minimum efficiency in whole team, then:
 *
 * 		>	Other engineers in the team must have efficiency at least equal or higher than this fixed engineer
 *		>	With this, we know the MIN(efficiency) as the fixed engineer's efficiency value. How about SUM(speed)?
 *			Since it is summation, the more speed the better. Try to include as many engineers as possible, only
 *			if the efficiency is greater or equal to that of fixed engineer's
 *
 *	Therefore, if we sort the engineers in advance by efficiency in descending order, surely as we proceed iteration thru
 *	engineers,
 *		>	All engineers earlier are having efficiency value higher or equal to current fixed engineer's!
 *		>	The problem now is to choose the best previously seen engineers that give good SUMS.
 *
 *	To pick out the previously seen engineers with good SUMS, we would utilize heap (priority queue) for that.
 *	With a priority queue, we don't even have to iterate the previously seen engineers again for each fixed
 *	engineers, since we will always keep the best engineers of highest speed in the priority queue, popping
 *	out the lowest speed engineer as required.
 *
 *
 *	Time complexity is O(N (log N + log K))
 *		> N log N for sorting
 *		> N log K, for each engineer we fix as lowest efficiency engineer, we check if queue is size K, pop as necessary
 *
 *	Space is O(N + K). Since we construct the tuple array of size N here for sorting purposes.
 */

class Solution {
public:
	int maxPerformance(int n, vector<int>& speed, vector<int>& efficiency, int k) {
		int MOD = 1000000007;
		LONG res = 0;

		//	Tuple of efficiency, speed. Remember the performance is [ sum(speed) * min(efficiency) ]
		vector<pair<int, int>> pairs(n, pair<int, int>());
		for (int i = 0; i < n; ++i) {
			pairs[i].first = efficiency[i];
			pairs[i].second = speed[i];
		}

		//	Sort the efficiency decreasing order.
		sort(pairs.begin(), pairs.end(), [](auto& left, auto& right) -> bool {
			return left.first > right.first;
		});

		//	Priority queue to record all larger (or equal) efficiency workers. Sorted by speed, where smallest speed pop first
		//	In C++, priorityqueue is max heap. Thus we put negation to make it min heap
		priority_queue<int> pq;
		LONG pq_speed_sum = 0;

		for (auto& worker : pairs) {
			int currentEfficiency = worker.first;
			int currentSpeed = worker.second;

			//	Since we are going to add the current worker, we must ensure queue is only having K-1 elements
			if (pq.size() == k) {
				pq_speed_sum -= -pq.top();
				pq.pop();
			}

			//	Add current worker
			pq_speed_sum += currentSpeed;
			pq.push(-currentSpeed);

			//	Calculate the performance points with current worker included
			res = max(res, pq_speed_sum * currentEfficiency);
		}
		return (int)(res % MOD);
	}
};