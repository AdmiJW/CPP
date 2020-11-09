#include <iostream>
#include <string>
using namespace std;





//	Function declaration
double* getRainAmounts();
void getHighestRain(double rainAmounts[], string dayNames[]);
void getAverageRain(double rainAmounts[]);
void getFloods(double rainAmounts[]);
void getDroughts(double rainAmounts[], string dayNames[] );


//	The main() function 
void assgm1() {
	string dayNames[] = { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };

	double* rainAmounts = getRainAmounts();

	getHighestRain(rainAmounts, dayNames);
	cout << "\n";
	getAverageRain(rainAmounts);
	cout << "\n";
	getFloods(rainAmounts);
	cout << "\n";
	getDroughts(rainAmounts, dayNames);

	delete[] rainAmounts;
}


//	Obtain the rain Amounts for 7 days from user input
double* getRainAmounts() {
	double* rainAmounts = new double[7];

	for (int i = 0; i < 7; i++) {
		cout << "Enter the rain amount for day " << (i + 1) << ": ";
		cin >> rainAmounts[i];
	}
	cout << "\n";

	return rainAmounts;
}

//	Pass in the rainAmounts array and the dayNames string array, will find the highest amount of rain, and
//	output which day had highest amount of rain
void getHighestRain(double rainAmounts[], string dayNames[]) {
	double highest = 0;
	for (int i = 0; i < 7; i++) {
		if (highest < rainAmounts[i])
			highest = rainAmounts[i];
	}

	cout << "The highest rain amount is " << highest << "\n";

	for (int i = 0; i < 7; i++) {
		if (rainAmounts[i] == highest)
			cout << "The highest amount of rain occurred at " << dayNames[i] << "\n";
	}
}

//	Pass in the rainAmounts array, will find the average of the rain amounts
void getAverageRain(double rainAmounts[]) {
	double sum = 0;
	for (int i = 0; i < 7; i++) {
		sum += rainAmounts[i];
	}
	double averageRain = sum / 7.0;
	
	cout << "Average amount is " << averageRain << '\n';
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
		else {
			overflow = 0;
		}
	}

	cout << "The total of flood in the week is " << floodCount << "\n";
}





//	Pass in the rain amount array, will find out which day does the drought occurs, accounting for water overflow
void getDroughts(double rainAmounts[], string dayNames[]) {
	double waterLevels[7];
	bool isDraught[7] = {};
	double overflow = 0;
	for (int i = 0; i < 7; i++) {
		waterLevels[i] = overflow + rainAmounts[i];
		if (waterLevels[i] - 230 <= 0) {
			overflow = 0;
		}
		else {
			overflow = waterLevels[i] - 230;
		}
	}

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
	}
}