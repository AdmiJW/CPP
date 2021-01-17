#pragma once

#include <vector>
#include <iostream>
#include <ctime>
#include <string>

//==============================
//	FILE PATHS
//==============================
#define FOODMENU_CSV "./RestaurantDatabase/menu.csv"
#define ORDERS_CSV "./RestaurantDatabase/orders.csv"
#define HISTORY_CSV "./RestaurantDatabase/history.csv"


//==============================
//	OUTPUT FUCNTIONS MACRO
//==============================
#ifndef PRINT(X)
#define PRINT(X) std::cout << X
#endif

#ifndef PRINTLN(X)
#define PRINTLN(X) std::cout << X << std::endl
#endif

#ifndef BREAKLINE
#define BREAKLINE std::cout << '\n'
#endif



//==============================
//	STRUCTURED DATA
//==============================
struct FoodItem {
	unsigned int id;
	std::string foodName;
	float price = 0;
};
struct OrderItem {
	FoodItem food;
	unsigned int quantity = 0;
	float netPrice = 0;
};
struct DetailedOrderItem {
	std::string telephone;
	std::string address;
	std::string time;
	std::string food;
	unsigned int quantity;
	float netPrice;
};


//=======================
//	UTILITIES HEADER
//=======================
int obtainUserChoice(int lowerBound = 0, int upperBound = 1, const std::string& prompt = "Please enter your choice: ");
float obtainUserChoice(float lowerBound = 0, float upperBound = 1, const std::string& prompt = "Please enter your choice: ");
std::string obtainUserInputWithRegex(const std::string& pattern, const std::string& prompt = "Please enter information: ");
std::ifstream getReadFileBuffer(const std::string& filePath);
std::ofstream getWriteFileBuffer(const std::string& filePath);
std::fstream getFileBuffer(const std::string& filePath);
std::vector<FoodItem> readFoodMenu(std::ifstream& foodMenu);
std::vector<DetailedOrderItem> readOrderMenu(std::ifstream& orderMenu);
void printFoodMenu(std::vector<FoodItem>& foodMenu);
void printOrderMenu(const std::vector<DetailedOrderItem>& orders);
void pressEnterToContinue(const std::string& prompt = "Press Enter to continue... ");


//=========================================
//	Required to Switch Application States
//=========================================
void displayCustomerMenu();
void displayManagerMenu();
bool displayPayment(const std::vector<OrderItem>&);