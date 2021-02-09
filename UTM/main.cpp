/*==================================
//	NAME: SOH JUN WEI
//	MATRIC: A20EC0151
//	SECTION: 08
//	LECT: DR.ADILA FIRDAUS BINTI ARBAIN
===================================*/


#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <stdlib.h>
#define SIZE 50
using namespace std;


//	TASK 1
struct Item {
	string code;
	string name;
	float cost;
	float salePrice;
	unsigned int noSales;
	float profit;
};


//	Task 7
int readInput(Item[]);
void calculateSalePrice(Item[], int);
void displayOutput(Item[], int);
void displayAnalysis(Item[], int);



//	TASK 6
int main() {
	Item items[SIZE];
	int itemAmt;

	itemAmt = readInput(items);
	calculateSalePrice(items, itemAmt);
	displayOutput(items, itemAmt);
	displayAnalysis(items, itemAmt);

	return 0;
}




//	Task 2
int readInput( Item items[] ) {
	int itemAmt = 0;
	ifstream inputFile;
	inputFile.open("./input.txt");

	if (!inputFile.is_open()) {
		cout << "Unable to open input.txt!";
		exit(0);
	}

	while (!inputFile.eof()) {
		Item& item = items[itemAmt];
		inputFile >> item.code;
		if (!item.code.length()) break;		//	Empty line. Break the loop
		inputFile >> item.noSales;

		++itemAmt;
	}

	inputFile.close();
	return itemAmt;
}



// Task 3
void calculateSalePrice(Item items[], int itemAmt) {
	for (int i = 0; i < itemAmt; ++i) {
		Item& item = items[i];
	
		//	Determine name and cost
		if (!item.code.compare("M101")) {
			item.name = "Double Mushroom";
			item.cost = 11.5;
		}
		else if (!item.code.compare("B202")) {
			item.name = "Double BBQ Beef";
			item.cost = 10.2;
		}
		else if (!item.code.compare("C303")) {
			item.name = "Grilled Chicken";
			item.cost = 7;
		}
		else {
			item.name = "Fish'n Crisp";
			item.cost = 6.25;
		}

		// Calculate sale price by add 30%
		item.salePrice = item.cost * 1.3;
	}
}



//	Task 4
void displayOutput(Item items[], int itemAmt) {
	cout << right << fixed << setprecision(2) <<  "----------------------------------------------------------------------" << endl;
	cout << setw(5) << "CODE" << setw(20) << "ITEM NAME" << setw(10)
		<< "COST(RM)" << setw(10) << "SALE(RM)" << setw(10)
		<< "QUANTITY" << setw(15) << "PROFIT(RM)" << endl;
	cout << "----------------------------------------------------------------------" << endl;

	for (int i = 0; i < itemAmt; ++i) {
		Item& item = items[i];

		//	Calculate profit
		item.profit = item.noSales * (item.salePrice - item.cost);

		cout << setw(5) << item.code;
		cout << setw(20) << item.name;
		cout << setw(10) << item.cost;
		cout << setw(10) << item.salePrice;
		cout << setw(10) << item.noSales;
		cout << setw(10) << item.profit << endl;
	}
}



//	Task 5
void displayAnalysis(Item items[], int itemAmt) {

	string itemNames[4] = { "Double Mushroom", "Double BBQ Beef",
		"Grilled Chicken", "Fish'n Crisp" };
	float itemProfits[4] = {};
	float highestProfit = 0, totalProfit = 0;

	//	Aggregate profits
	for (int i = 0; i < itemAmt; ++i) {
		Item& item = items[i];

		for (int j = 0; j < 4; ++j) {
			if (!itemNames[j].compare(item.name))
				itemProfits[j] += item.profit;
		}
	}
	
	//	Find Highest and total
	for (float& profit : itemProfits) {
		totalProfit += profit;
		if (profit > highestProfit)
			highestProfit = profit;
	}


	//	Display results;
	cout << "----------------------------------------------------------------------" << endl;
	cout << setw(10) << "" << setw(15) << "ITEM NAME"
		<< setw(10) << "" << setw(15) << "TOTAL PROFIT(RM)" << endl;
	cout << "----------------------------------------------------------------------" << endl;

	for (int i = 0; i < 4; ++i) {
		cout << setw(5) << "" << setw(20) << itemNames[i] << setw(5)
			<< "" << setw(20) << itemProfits[i] << endl;
	}

	cout << "----------------------------------------------------------------------" << endl;
	cout << setw(10) << "" << "The total amount of profit = RM "
		<< totalProfit << endl;
	cout << setw(10) << "" << setw(20) << "Highest profit = RM "
		<< highestProfit << endl;
	cout << "----------------------------------------------------------------------" << endl;
}



