#pragma once

#include <iostream>
#include <unordered_map>

struct Workshop {
	int start_time;
	int duration;
	int end_time;
};


struct Available_Workshops {
	int n;
	Workshop* workshop;	//Later, will point to the array of the Workshop
};


Available_Workshops* initialize(int start_time[], int duration[], int n) {
	Available_Workshops* obj = &Available_Workshops();
	obj->n = n;
	obj->workshop = new Workshop[n];	//Workshops will be created here

	for (int i = 0; i < n; i++) {
		Workshop& ws = obj->workshop[i];	//	Setting the workshop properties
		ws.start_time = start_time[i];
		ws.duration = duration[i];
		ws.end_time = start_time[i] + duration[i];
	}

	return obj;
}

int calculateMaxWorkshops(Available_Workshops* ptr) {
	int n = ptr->n;
	int max = 0;		// The maximum ending time
	std::unordered_map<int, Workshop*> endTimeMap;

	for (int i = 0; i < n; i++) {
		Workshop& ws = ptr->workshop[i];

		int endTime = ws.end_time;
		max = std::max(endTime, max);

		if (endTimeMap.count(endTime) && endTimeMap[endTime]->duration < ws.duration) {
			continue;
		}
		endTimeMap[endTime] = &ws;
	}

	//	Dynamic Programming
	int* dp = new int[max + 1];
	dp[0] = 0;

	for (int i = 1; i <= max; i++) {
		if (endTimeMap.count(i)) {
			Workshop& ws = *endTimeMap[i];
			dp[i] = std::max(dp[i - 1], 1 + dp[ws.start_time]);
		}
		else {
			dp[i] = dp[i - 1];
		}
	}

	return dp[max];

}

void printAvailable(Available_Workshops* pt) {
	int n = pt->n;

	for (int i = 0; i < n; i++) {
		Workshop& ws = pt->workshop[i];
		std::cout << ws.start_time << " " << ws.duration << " " << ws.end_time << std::endl;
	}
}

void tester() {
	int st[] = { 1, 3, 0, 5, 5, 8 };
	int dr[] = { 1,1,6,2,4,1 };

	Available_Workshops* aw = initialize(st, dr, 6);
	printAvailable(aw);
}

