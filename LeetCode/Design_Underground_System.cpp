#include <string>
#include <unordered_map>
using namespace std;

//https://leetcode.com/problems/design-underground-system/
/*
 * 	This is simply a Design problem.
 *
 * 	When you check in, you get the customer's ID, board station and the time. You don't know about when the customer
 * 	will check out the train. So you have to store them first!
 *
 * 	The key is obviously the customer's ID. However we have to store the boarding station and time. Since they are different
 * 	datatypes, we either use Pair<> object, or create our own class for that.
 *
 * 	When board off, look up the boarding info from the above Hashmap. Then, we can immediately store the information about
 * 	the times.
 * 	For some efficiency, store the boarding-checkout station names into single string. Another HashMap will be storing the
 * 	"boarding-checkout" string as key, and it points an integer array of size 2 (again, you can use Pair).
 * 	The integer array is [ total time, no of customers ]
 *
 */

class UndergroundSystem {
public:

	UndergroundSystem() {}

	void checkIn(int id, string stationName, int t) {
		onBoard[id] = { t, stationName };
	}

	void checkOut(int id, string stationName, int t) {
		BoardingDetail& d = onBoard[id];
		string encoded = d.station + "-" + stationName;

		if (!times.count(encoded))
			times[encoded] = make_pair<>(0, 0);

		++times[encoded].second;
		times[encoded].first += (t - d.time);

		onBoard.erase(id);
	}


	double getAverageTime(string startStation, string endStation) {
		string encoded = startStation + "-" + endStation;
		auto& time = times[encoded];
		return (double)time.first / time.second;
	}

private:
	struct BoardingDetail {
		int time;
		string station;
	};

	unordered_map<int, BoardingDetail> onBoard;		//	Maps ID to their boarding station detail
	unordered_map<string, pair<int, int>> times;	//	Maps String "<boardingStation-arrivalStation>" to their total time spent and counts
};