#include <iostream>
#include <string>
using namespace std;


string dayNames[] = { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };


//	Function declaration
double max(double n1, double n2);
void getHighestRainAndAverage(double rainAmounts[]);
void getFloods(double rainAmounts[]);
void getDroughts(double rainAmounts[]);


//	The main() function 
void assgm1() {

	double rainAmounts[7];

	for (int i = 0; i < 7; i++) {
		cout << "Enter the rain amount for " << dayNames[i] << ": ";
		cin >> rainAmounts[i];
	}

	cout << "\n";

	getHighestRainAndAverage(rainAmounts);
	cout << "\n";
	getFloods(rainAmounts);
	cout << "\n";
	getDroughts(rainAmounts);
}


//	Function just returns the maximum out of n1 and n2
double max(double n1, double n2) {
	if (n1 < n2) return n2;
	return n1;
}



//	Pass in the rain amount array, will find out the
//	Highest amount and print the days having highest
//	rain
void getHighestRainAndAverage(double rainAmounts[]) {
	double highest = 0;
	double sum = 0;
	for (int i = 0; i < 7; i++) {
		sum += rainAmounts[i];
		highest = max(highest, rainAmounts[i]);
	}

	cout << "Average week rain amount is: " << sum / 7.0 << "\n";

	cout << "Highest Amount of Rain is " << highest << "\n";

	for (int i = 0; i < 7; i++) {
		if (rainAmounts[i] == highest) {
			cout << "Highest Amount of Rain occurred at " << dayNames[i] << "\n";
		}

	}
}





//	Pass in the rain amount array, will find out the
//	Number of floods occurred
void getFloods(double rainAmounts[]) {
	double overflow = 0;
	int floodCount = 0;

	for (int i = 0; i < 7; i++) {
		if (rainAmounts[i] + overflow > 230) {
			floodCount++;
			overflow = rainAmounts[i] + overflow - 230;
		}
	}

	cout << "There is a total of " << floodCount << " floods this week" << "\n";
}





//	Pass in the rain amount array, will find out which day does the drought occurs
void getDroughts(double rainAmounts[]) {
	double waterLevels[7];
	double overflow = 0;
	for (int i = 0; i < 7; i++) {
		waterLevels[i] = overflow + rainAmounts[i];
		overflow = max(waterLevels[i] - 230, 0);
	}

	bool isDraught[7] = {};
	for (int i = 2; i < 7; i++) {
		if (waterLevels[i] + waterLevels[i - 1] + waterLevels[i - 2] == 0) {
			isDraught[i] = true;
			isDraught[i - 1] = true;
			isDraught[i - 2] = true;
		}
	}

	for (int i = 0; i < 7; i++) {
		if (isDraught[i])
			cout << "Drought occurred at " << dayNames[i] << "\n";
		else
			cout << "There is no drought on " << dayNames[i] << "\n";
	}

}