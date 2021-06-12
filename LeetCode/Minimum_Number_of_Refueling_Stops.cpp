#include <vector>
#include <queue>
using namespace std;

//https://leetcode.com/problems/minimum-number-of-refueling-stops/
/*
 * 	This is a DP problem / Heap problem. Hard in coming up in the idea, but easier to implement.
 * 	I overcomplicated and fail to come up with a solution. It is a suprise that the solution can be done in O(N^2) or O(N log N)
 *
 * 	Instead of thinking about minimum refuel stops to reach the target like I do which failed,
 * 	think: What is the maximum distance that I could reach?
 * 	We'll have a DP array where DP[i] shows given i stops, what is the maximum distance I could
 * 	travel?
 * 	To do this, we'll consider each station one by one. For each station, I will try out all possible
 * 	number of stops, but we will stop at the currently considered station (if it is reachable, of course, by checking dp[i-1]).
 *
 * 	Since the DP updating is based on previous DP results (DP[i-1]), we should iterate the number of stops from back to front,
 * 	so that we'll not mistakenly took the updated value (with current station included) instead not the past value.
 *
 * 	======================================================================
 *
 * 	For Heap solution, we try to be greedy. We'll not refuel at any stations we pass by, but to record their presence.
 * 	When we really ran out of fuel before reaching a station, we'll try to compensate by refuelling at past stations.
 * 	Of course, we'll pick the largest amount of refuel as there is no consequence of choosing the largest amount of fuel.
 *
 * 	Check whether by greedily refuelling, is able to bring us to destination or not.
 */

class Solution {
public:
	int minRefuelStops(int target, int startFuel, vector<vector<int>>& stations) {
		const int len = stations.size();

        //	DP array at i stores the maximum distance to reach for i stops
        //	Base case is at dp[0], maximum distance to reach is startFuel
        vector<long long int> dp(len+1, 0);
        dp[0] = startFuel;

        //	For each new stations added, try out all possible stops
        for (int stationIdx = 0; stationIdx < len; ++stationIdx) {
            for (int stops = stationIdx + 1; stops > 0; --stops) {
                //	To even consider this station, I must be able to reach this station first!
                if (stations[stationIdx][0] <= dp[stops - 1])
                    dp[stops] = max(dp[stops], dp[stops - 1] + (long)stations[stationIdx][1]);
            }
        }

        for (int i = 0; i < len + 1; ++i)
            if (dp[i] >= target) return i;
        return -1;
	}


    int minRefuelStops2(int target, int startFuel, vector<vector<int>>& stations) {
        const int len = stations.size();

        priority_queue<int> pq;
        int tank = startFuel;
        int laststop = 0;
        int stops = 0;

		for (auto& s : stations) {
			tank -= s[0] - laststop;
			laststop = s[0];

			//	Ran out of fuel. Should've refuel at past stations
			while (!pq.empty() && tank < 0) {
				++stops;
				tank += pq.top(); pq.pop();
			}
			//	Even if I refuelled at all station, cannot reach current station too.
			if (tank < 0) return -1;

			//	Add to possible refuel stations selected
			pq.push(s[1]);
		}

		//	Can I reach destination from the available fuel?
		while (!pq.empty() && tank < target - laststop) {
			++stops;
			tank += pq.top(); pq.pop();
		}
		return (tank < target - laststop) ? -1 : stops;
    }
};