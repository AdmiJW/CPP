
#include <iostream>
#include <string>

using namespace std;


string dayNames[] = { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };

double max(double n1, double n2);
void getHighestRain( double rainAmounts[] );
void getFloods( double rainAmounts[] );
void getDroughts(double rainAmounts[] );



void assgm1() {

	double rainAmounts[7];

	for (int i = 0; i < 7; i++) {
		cout << "Enter the rain amount for " << dayNames[i] << ": ";
		cin >> rainAmounts[i];
	}

	getHighestRain(rainAmounts);

	getDroughts(rainAmounts);


}

double max(double n1, double n2) {
	if (n1 < n2) return n2;
	return n1;
}

void getHighAmtRain( double rainAmounts[] ) {
	double highest = 0;
	for (int i = 0; i < 7; i++) {
		highest = max(highest, rainAmounts[i]);
	}

	cout << "Highest Amount of Rain is " << highest << "\n";

	for (int i = 0; i < 7; i++) {
		if (rainAmounts[i] == highest)
			cout << "Highest Amount of Rain occurred at " << dayNames[i] << "\n";
	}
}

void getFloods( double rainAmounts[] ) {
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

void getDroughts(double rainAmounts[]) {
	for (int i = 2; i < 7; i++) {
		if (rainAmounts[i] + rainAmounts[i - 1] + rainAmounts[i - 2] == 0)
			cout << "There is a Drought occurring at " << dayNames[i] << "\n";
	}
}