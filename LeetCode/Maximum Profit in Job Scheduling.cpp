#include <map>
#include <vector>
#include <algorithm>
using namespace std;

//https://leetcode.com/problems/maximum-profit-in-job-scheduling/
/*
 * 	This is a mainly DP, (TreeSet - Binary Tree), Binary Search problem.
 *
 *	This is similar to classical 01 knapsack problem, where we can choose to either include or exclude
 *	some objects, and trying to reach optimum solution.
 *
 *	For each of the jobs, I have the choice of either taking it or not. If not taking it, the maximum
 *	profit remains as it is. However, if taking it, I would want to maximize the profit, such that,
 *	the formula involved is:
 *
 *		( Max profit before or at startTime + profit for taking this job )
 *
 *	The problem is how do we know the max profit before or at startTime?
 *
 *	This is solved if we:
 *		>	Process jobs according to their end time, ascendingly. This ensures we can retrieve the latest
 *			maximum profit in O(1) time.
 *		>	The maximum profit is stored sorted by their end time. This way we can always perform binary
 *			search on the floorEntry on startTime.
 */

class Solution {
public:
    int jobScheduling(vector<int>& startTime, vector<int>& endTime, vector<int>& profit) {
        const int len = startTime.size();
        vector<vector<int>> jobs;

        for (int i = 0; i < len; ++i)
            jobs.push_back({ startTime[i], endTime[i], profit[i] });

        //Sort in increasing ending time
        sort(jobs.begin(), jobs.end(), [](auto& l, auto& r)-> bool {
            return l[1] < r[1];
        });

        // Map of endTime -> max profit achieved
        map<int, int> map;
        map[0] = 0;

        // Consider taking each of the job.
        for (auto& job : jobs) {
            // If I take the job, profit is ( optProfit until startTime + profit )
            int optProfit = prev(map.upper_bound(job[0]))->second + job[2];
            // Or perhaps I do not take the job? Then it is closest optProfit <= endTime
            if (optProfit > map.rbegin()->second)
                map[job[1]] = optProfit;
        }

        return map.rbegin()->second;
    }
};