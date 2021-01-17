#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector>
#include <regex>

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



//	Prompts and obtains user input for integral values only
//
//	lowerBound - The lower bound (Inclusive) for user input
//	upperBound - The upper bound (Inclusive) for user input
//	prompt - The message shown to nofify user to enter input
//
//	returns - The user input
int obtainUserChoice( int lowerBound, int upperBound, const std::string& prompt) {
	int choice;
	
	if (prompt.size()) 
		PRINT('\n' << prompt);

	std::cin >> choice;
	
	while (choice < lowerBound || choice > upperBound) {
		PRINTLN("Invalid Input. Valid input only ranges from " << lowerBound << " to " << upperBound);
		
		if (prompt.size() ) 
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

	if (prompt.size() ) 
		PRINT('\n' << prompt);

	std::cin >> choice;

	while (choice < lowerBound || choice > upperBound) {
		PRINTLN("Invalid Input. Valid input only ranges from " << lowerBound << " to " << upperBound);
		
		if (prompt.size())
			PRINT('\n' << prompt);

		std::cin.clear();					//	If invalid input, the cin fail() will set to true. Clear it to proceed
		std::cin.ignore(INT32_MAX, '\n');	//	Ignore all characters until newline character
		std::cin >> choice;
	}

	std::cin.ignore(INT32_MAX, '\n');	//Valid input but \n left in the input buffer.
	PRINT('\n');
	return choice;
}


std::string obtainUserInputWithRegex(const std::string& pattern, const std::string& prompt) {
	std::string input;
	std::regex regex(pattern);

	if (prompt.size() ) 
		PRINT('\n' << prompt);

	std::getline(std::cin, input);

	while ( !std::regex_match(input, regex)) {
		PRINTLN("Invalid Input! Please retry!");
		PRINT('\n' << prompt);

		std::getline(std::cin, input);
	}

	PRINT('\n');
	return input;
}



//	Fetch a file from filePath and returns the ifstream buffer
//	
//	filePath - Path to the file to be opened
//
//	returns - ifstream of the file if successfully opened.
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


//	Fetch a file (or create a new one) from filePath and returns the ofstream buffer
//
//	filePath - Path to the file to be written.
//
//	returns - ofstream of the file if available
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



//	Fetch a file from filePath and returns the fstream buffer. The open mode is in append mode (ios::app)
//
//	filePath - Path to the file to be written.
//
//	returns - fstream of the file if successfully opened
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



//	Reads the food menu csv text file from ifstream, parse it and return the std::vector containing food items
//
//	foodMenu - ifstream instance of the food menu csv file
//
//	returns - vector containing food items
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




//	Reads the order menu csv text file from ifstream, parse it and return the std::vector containing order items
//
//	orderMenu - ifstream instance of the order menu csv file
//
//	returns - vector containing order items
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