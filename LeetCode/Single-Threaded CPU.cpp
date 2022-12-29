#include <queue>
#include <vector>
using namespace std;


// https://leetcode.com/problems/single-threaded-cpu/
/*
 * This is a heap problem.
 *
 * Maintain two heaps, one sorted by start time, one sorted by duration. We will always pick the process with
 * shortest duration to execute. If there is no process in durationPQ, we need to wait until the next process
 * starts. If there are multiple processes with shortest duration, we will pick the one with smallest id.
 *
 * We will keep track of the time starting from t=1. Start by adding all processes into startPQ.
 * We will simulate the adding of processes by adding the processes from startPQ that start
 * before current time to durationPQ. Then just select one process that is the shortest time to execute at each
 * iteration.
 *
 * Time complexity: O(nlogn)
 * Space complexity: O(n)
 */


class Process {
public:
    long long int id;
    long long int startTime;
    long long int duration;

    Process(int id, int startTime, int duration) {
        this->id = id;
        this->startTime = startTime;
        this->duration = duration;
    }
};




class CompareStart {
public:
    bool operator() (Process& x, Process& y) {
        return x.startTime == y.startTime ? x.id > y.id : x.startTime > y.startTime;
    }
};

class CompareDuration {
public:
    bool operator() (Process& x, Process& y) {
        return x.duration == y.duration ? x.id > y.id : x.duration > y.duration;
    }
};



class Solution {
public:
    vector<int> getOrder(vector<vector<int>>& tasks) {
        const int n = tasks.size();

        // Sort by start time
        priority_queue<Process, vector<Process>, CompareStart> startPQ;
        // Sort by duration
        priority_queue<Process, vector<Process>, CompareDuration> durationPQ;

        // Add all processes to startPQ first
        for (int i = 0; i < n; i++)
            startPQ.push( Process(i, tasks[i][0], tasks[i][1]) );

        // Current time
        long long int time = 1;
        vector<int> res(n, 0);

        for (int i = 0; i < n; ) {
            // If there is no process in durationPQ, we need to wait until the next process starts
            if (durationPQ.empty()) {
                Process p = startPQ.top();
                startPQ.pop();
                time = max(time, p.startTime);
                durationPQ.push(p);
            }

            // Add all processes that start before current time to durationPQ
            while (!startPQ.empty() && startPQ.top().startTime <= time) {
                durationPQ.push(startPQ.top());
                startPQ.pop();
            }

            // Process the process with shortest duration
            Process p = durationPQ.top();
            durationPQ.pop();
            res[i++] = p.id;
            time += p.duration;
        }

        return res;
    }
};