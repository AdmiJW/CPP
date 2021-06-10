#include <map>
using namespace std;

//https://leetcode.com/problems/my-calendar-i/
/*
 * 	This can be thought of as a Binary Search Tree problem?
 *
 *	A task can only be inserted if it is not overlapping with any other tasks. We have to think of
 *	a data structure that let us perform checking for overlapping, and insertion in fast time.
 *
 *	For brute force, we only keep a list of tasks. Everytime we have to insert a task, iterate through
 *	each previously inserted task and see if they overlap or not.
 *	If none of the tasks overlap, we are safe to say that the task is not overlapping and append to the list.
 *	This apporach however takes O(N^2) time.
 *
 *	A Binary Search Tree with balanced feature, like Java's TreeMap (Red black tree) is good for this.
 *	It is able to let us search for floorkey and ceilingkey time as well as insertion in
 *	O(log N) time. Check if both floorkey and ceilingkey task is overlapping or not. If not, it is safe
 *	to say the task can be safely inserted.
 */

class MyCalendar {
public:
    map<int, int> schedules;

    MyCalendar() {}

    //  C++ does not support looking for floor values.
    //  lower_bound looks for >=, while upper_bound looks for >
    bool book(int start, int end) {
        auto next = schedules.lower_bound(start);
        if (next != schedules.end() && next->first < end) return false;

        //  Check for previous task if exists
        if (next != schedules.begin()) {
            --next;
            if (next->second > start) return false;
        }
        schedules[start] = end;
        return true;
    }
};