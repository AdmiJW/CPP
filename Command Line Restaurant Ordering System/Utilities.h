#pragma once

#include <vector>
#include <iostream>
#include <ctime>
#include <string>

#ifndef PRINT(X)
#define PRINT(X) std::cout << X
#endif

#ifndef PRINTLN(X)
#define PRINTLN(X) std::cout << X << std::endl
#endif

#ifndef BREAKLINE
#define BREAKLINE std::cout << '\n'
#endif


struct FoodItem {
	unsigned int id;
	std::string foodName;
	float price = 0;

	FoodItem() {
		PRINTLN("Created foodItem");
	}
};


struct OrderItem {
	FoodItem food;
	unsigned int quantity = 0;
	float netPrice = 0;

	OrderItem() {
		PRINTLN("Order Item Created");
	}
};


struct CustomerOrder {
	std::time_t orderTime;
	std::vector<OrderItem> orders;
	float totalPrice;
};


int obtainUserChoice(int lowerBound = 0, int upperBound = 1, const std::string& prompt = "Please enter your choice: ");
std::ifstream getReadFileBuffer(const std::string& filePath);
std::ofstream getWriteFileBuffer(const std::string& filePath);
std::fstream getFileBuffer(const std::string& filePath);
void pressEnterToContinue(const std::string& prompt = "Press Enter to continue... ");


//	Required to jump from one state to another
void displayMainMenu();
void displayCustomerMenu();
void displayManagerMenu();
bool displayPayment(const std::vector<OrderItem>&);