#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector>

#include "Utilities.h";

#ifndef PRINT(X)
	#define PRINT(X) std::cout << X
#endif

#ifndef PRINTLN(X)
	#define PRINTLN(X) std::cout << X << std::endl
#endif

#ifndef BREAKLINE
	#define BREAKLINE std::cout << '\n'
#endif



int obtainUserChoice( int lowerBound, int upperBound, const std::string& prompt) {
	int choice;
	
	PRINT('\n' << prompt);
	std::cin >> choice;
	
	while (choice < lowerBound || choice > upperBound) {
		PRINTLN("Invalid Input. Valid input only ranges from " << lowerBound << " to " << upperBound);
		PRINT('\n' << prompt);

		std::cin.clear();					//	If invalid input, the cin fail() will set to true. Clear it to proceed
		std::cin.ignore(INT32_MAX, '\n');	//	Ignore all characters until newline character
		std::cin >> choice;
	}

	std::cin.ignore(INT32_MAX, '\n');	//Valid input but \n left in the input buffer.
	PRINT('\n');
	return choice;
}
float obtainUserChoice(float lowerBound, float upperBound, const std::string& prompt) {
	float choice;

	PRINT('\n' << prompt);
	std::cin >> choice;

	while (choice < lowerBound || choice > upperBound) {
		PRINTLN("Invalid Input. Valid input only ranges from " << lowerBound << " to " << upperBound);
		PRINT('\n' << prompt);

		std::cin.clear();					//	If invalid input, the cin fail() will set to true. Clear it to proceed
		std::cin.ignore(INT32_MAX, '\n');	//	Ignore all characters until newline character
		std::cin >> choice;
	}

	std::cin.ignore(INT32_MAX, '\n');	//Valid input but \n left in the input buffer.
	PRINT('\n');
	return choice;
}


std::ifstream getReadFileBuffer( const std::string& filePath ) {
	std::ifstream f;
	f.open(filePath);

	if (!f) {
		std::string err = "Unable to read file from location: ";
		err += filePath;
		err += "!\n";
		throw err;
	}
	return f;
}


std::ofstream getWriteFileBuffer(const std::string& filePath) {
	std::ofstream f;
	f.open(filePath);

	if (f.fail()) {
		std::string err = "Unable to open/create file from location: ";
		err += filePath;
		err += "!\n";
		throw err;
	}
	return f;
}


std::fstream getFileBuffer(const std::string& filePath) {
	std::fstream f;
	f.open(filePath, std::ios_base::app);

	if (f.fail()) {
		std::string err = "Unable to open/create file from location: ";
		err += filePath;
		err += "!\n";
		throw err;
	}
	return f;
}


std::vector<FoodItem> readFoodMenu(std::ifstream& foodMenu) {
	std::vector<FoodItem> foodItems;
	std::string line, token;
	std::istringstream lineStream;

	getline(foodMenu, line);	//Discard the first row, which is the ID, Name and Price

	int row = 0;
	while (!foodMenu.eof()) {
		foodItems.emplace_back(FoodItem());

		getline(foodMenu, line);
		lineStream.clear();
		lineStream.str(line);

		//	ID
		getline(lineStream, token, ',');
		foodItems.back().id = ++row;

		//	Food Name
		getline(lineStream, token, ',');
		foodItems.back().foodName = token;

		//	Price
		getline(lineStream, token, ',');
		foodItems.back().price = std::atof(token.c_str());
	}

	return foodItems;
}



std::vector<DetailedOrderItem> readOrderMenu(std::ifstream& orderMenu) {
	std::vector<DetailedOrderItem> orders;
	std::string line, token;
	std::istringstream lineStream;

	getline(orderMenu, line);	//Discard the first row, which is the ID, Name and Price

	while (!orderMenu.eof()) {
		orders.emplace_back(DetailedOrderItem());

		getline(orderMenu, line);
		lineStream.clear();
		lineStream.str(line);

		//	Telephone
		getline(lineStream, token, '|');
		orders.back().telephone = token;

		//	Address
		getline(lineStream, token, '|');
		orders.back().address = token;

		//	Time
		getline(lineStream, token, '|');
		orders.back().time = token;

		//	Food
		getline(lineStream, token, '|');
		orders.back().food = token;

		//	Quantity
		getline(lineStream, token, '|');
		orders.back().quantity = std::atoi(token.c_str());

		//	Net Price
		getline(lineStream, token, '|');
		orders.back().netPrice = std::atof(token.c_str());
	}

	return orders;
}



void printFoodMenu(std::vector<FoodItem>& foodMenu) {
	BREAKLINE;
	PRINTLN("<<<<<<<<<<<<<<<<<<<< FOOD MENU >>>>>>>>>>>>>>>>>>>");
	BREAKLINE;
	PRINT(std::setw(5) << std::left << "ID");
	PRINT(std::setw(25) << std::left << "Cusine");
	PRINT(std::setw(10) << std::left << "Price(RM)");
	BREAKLINE;

	for (int i = 1; i <= foodMenu.size(); ++i) {
		PRINT(std::setw(5) << std::left << (foodMenu[i-1].id = i) );
		PRINT(std::setw(25) << std::left << foodMenu[i-1].foodName);
		PRINT(std::setw(10) << std::left << foodMenu[i-1].price);

		BREAKLINE;
	}

	BREAKLINE;
	PRINTLN("<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>");
}



void printOrderMenu(const std::vector<DetailedOrderItem>& orders) {
	BREAKLINE;
	PRINTLN("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< ORDERS >>>>>>>>>>>>>>>>>>>>>>>>>>>>>");
	BREAKLINE;
	PRINT(std::setw(3) << std::left << "ID");
	PRINT(std::setw(15) << std::left << "Telephone");
	PRINT(std::setw(30) << std::left << "Time");
	PRINT(std::setw(25) << std::left << "Food");
	PRINT(std::setw(10) << std::left << "Quantity");
	PRINT(std::setw(10) << std::left << "Net Price(RM)");
	BREAKLINE;

	for (int i = 1; i <= orders.size(); ++i ) {
		PRINT(std::setw(3) << std::left << i);
		PRINT(std::setw(15) << std::left << orders[i-1].telephone);
		PRINT(std::setw(30) << std::left << orders[i - 1].time);
		PRINT(std::setw(25) << std::left << orders[i - 1].food);
		PRINT(std::setw(10) << std::left << orders[i - 1].quantity);
		PRINT(std::setw(10) << std::left << orders[i - 1].netPrice);

		BREAKLINE;
	}

	BREAKLINE;
	PRINTLN("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>");
}



void pressEnterToContinue( const std::string& prompt) {
	PRINT(prompt);
	std::cin.ignore(INT32_MAX, '\n');
	PRINTLN("");
}