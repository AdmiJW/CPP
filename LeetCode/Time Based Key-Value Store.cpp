#include <unordered_map>
#include <vector>
#include <string>
using namespace std;

//https://leetcode.com/problems/time-based-key-value-store/
/*
 * 	This is a Map + binary search problem.
 *
 *
 * 	Saving the values into a hash map isn't a problem. However, each key in the hashmap has different values
 * 	at different times. Therefore we need a way to save the different versions of the values at different timestamp.
 *
 * 	We will have a HashMap that maps key to a collection of values. The collection stores the timestamp and value
 * 	encapsulated together, and must be designed such that we can easily get the correct value based on correct timestamp given.
 *
 * 	The problem constraint states that the set() function is always called in increasing timestamp. Therefore, we have no need
 * 	to sort the collection of values every time we add a new value - It is sorted naturally if we insert in natural order.
 * 	And since it is sorted, we can easily apply binary search to reduce the time complexity of a search from O(V) to O(log V)
 * 	(V being size of collection of values of a key)
 */



class TimeMap {
public:

    class TimeValue {
    public:
        int timestamp;
        string value;

        TimeValue(string value, int timestamp) {
            this->timestamp = timestamp;
            this->value = value;
        }
    };

    unordered_map<string, vector<TimeValue>> map;


    void set(string key, string value, int timestamp) {
        if (!map.count(key)) {
            map[key] = vector<TimeValue>();
            map[key].emplace_back(TimeValue("", -1) );
        }
        map[key].emplace_back( TimeValue(value, timestamp));
    }

    string get(string key, int timestamp) {
        if (!map.count(key)) return "";
        return search(map[key], timestamp);
    }


    string search(vector<TimeValue>& values, int timestamp) {
        int l = 0, r = values.size() - 1;

        while (l < r) {
            int m = l + (r - l) / 2;
            int t = values[m].timestamp;

            if (t < timestamp) l = m + 1;
            else r = m;
        }

        if (values[l].timestamp <= timestamp) return values[l].value;
        return values[l - 1].value;
    }
};