#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include "Utilities.h"


void displayCustomerMenu();
void browseFoodMenu();
void orderFood();
std::vector<FoodItem> readFoodMenu(std::ifstream& foodMenu);
void printFoodMenu(const std::vector<FoodItem>& foodMenu);
void printOrders(const std::vector<OrderItem>& orders);



void displayCustomerMenu() {
	std::system("cls");
	std::system("color B");

	BREAKLINE;
	PRINTLN("<<<<<<<<<<<<<<<<<<<< CUSTOMER MENU >>>>>>>>>>>>>>>>>>>> ");
	BREAKLINE;
	PRINTLN("1. Browse Menu");
	PRINTLN("2. Order Food");
	PRINTLN("3. Back to Main Menu");
	BREAKLINE;
	PRINTLN("<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>> ");

	int choice = obtainUserChoice(1, 3);

	if (choice == 1) browseFoodMenu();
	else if (choice == 2) orderFood();
	else if (choice == 3) displayMainMenu();
}


void browseFoodMenu() {
	std::system("cls");

	auto menuBuffer = getReadFileBuffer("./RestaurantDatabase/menu.csv");
	auto foodItems = readFoodMenu(menuBuffer);
	printFoodMenu(foodItems);
	BREAKLINE;
	pressEnterToContinue();

	displayCustomerMenu();
}


void orderFood() {
	std::system("cls");

	auto menuBuffer = getReadFileBuffer("./RestaurantDatabase/menu.csv");
	auto foodItems = readFoodMenu(menuBuffer);

	if (foodItems.size() == 0) {
		PRINTLN("***************************************************");
		PRINTLN("Sorry, The restaurant is currently out of stock...");
		PRINTLN("***************************************************\n");
		pressEnterToContinue("Press Enter to go back to Main Menu...");
		displayMainMenu();
	}

	std::vector<OrderItem> orders;

	//	Loop for getting orders
	while (1) {
		std::system("cls");
		std::system("color B");

		PRINTLN("<<<<<<<<<<<<<<<<<<<< ORDER FOOD >>>>>>>>>>>>>>>>>>>>\n");
		PRINTLN("1. Add Order");
		PRINTLN("2. Remove Order");
		PRINTLN("3. Submit Order");
		PRINTLN("4. Discard Order and return to Customer Menu");
		PRINTLN("\n<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>");

		int choice = obtainUserChoice(1, 4);


		if (choice == 1) {
			std::system("cls");
			printFoodMenu(foodItems);
			BREAKLINE;
			
			int choice = obtainUserChoice(0, foodItems.size(), "Enter the Food ID (or 0 to cancel): ");
			if (!choice) continue;
			int quantity = obtainUserChoice(0, 100, "Enter the quantity: ");

			auto searchRes = std::find_if(orders.begin(), orders.end(), [&choice](const OrderItem& o) -> bool {
				return o.food.id == choice;
			});

			if (searchRes == orders.end()) {
				orders.emplace_back(OrderItem() );
				orders.back().food = foodItems[choice - 1];
				orders.back().quantity = quantity;
				orders.back().netPrice = foodItems[choice - 1].price * quantity;
			}
			else {
				searchRes->quantity += quantity;
				searchRes->netPrice = searchRes->food.price * searchRes->quantity;
			};

			PRINTLN("Order for " << quantity << " x " << foodItems[choice - 1].foodName << " successfully added...");
			pressEnterToContinue();
		}
		else if (choice == 2) {
			printOrders(orders);
			BREAKLINE;

			int toDelete = obtainUserChoice(0, foodItems.size(), "Enter the Food ID to be deleted (or 0 to cancel): ");
			if (!toDelete) continue;

			auto searchRes = std::find_if(orders.begin(), orders.end(), [&toDelete](const OrderItem& o) -> bool {
				return o.food.id == toDelete;
				});

			if (searchRes == orders.end()) {
				PRINTLN("The Food ID entered " << toDelete << " is not found...");
				pressEnterToContinue();
			}
			else {
				PRINTLN("Food Order " << searchRes->food.foodName << " successfully deleted...");
				orders.erase(searchRes);
				pressEnterToContinue();
			}
		}
		else if (choice == 3) {
			if (!orders.size()) {
				PRINTLN("You have nothing ordered!");
				pressEnterToContinue();
			}
			else if (displayPayment(orders) ) displayMainMenu();		//	Payment Successful.
		}
		else if (choice == 4) displayCustomerMenu();
	}
	
}


std::vector<FoodItem> readFoodMenu(std::ifstream& foodMenu) {
	std::vector<FoodItem> foodItems;
	std::string line, token;
	std::istringstream lineStream;

	getline(foodMenu, line);	//Discard the first row, which is the ID, Name and Price

	while (!foodMenu.eof() ) {
		foodItems.emplace_back( FoodItem() );
	
		getline(foodMenu, line);
		lineStream.clear();
		lineStream.str(line);

		//	ID
		getline(lineStream, token, ',');
		foodItems.back().id = std::atoi(token.c_str());

		//	Food Name
		getline(lineStream, token, ',');
		foodItems.back().foodName = token;

		//	Price
		getline(lineStream, token, ',');
		foodItems.back().price = std::atof(token.c_str());
	}

	return foodItems;
}


void printFoodMenu(const std::vector<FoodItem>& foodMenu) {
	BREAKLINE;
	PRINTLN("<<<<<<<<<<<<<<<<<<<< FOOD MENU >>>>>>>>>>>>>>>>>>>");
	BREAKLINE;
	PRINT(std::setw(5) << std::left << "ID");
	PRINT(std::setw(25) << std::left << "Cusine");
	PRINT(std::setw(10) << std::left << "Price(RM)");
	BREAKLINE;

	for (const auto& foodItem: foodMenu) {
		PRINT(std::setw(5) << std::left << foodItem.id);
		PRINT(std::setw(25) << std::left << foodItem.foodName);
		PRINT(std::setw(10) << std::left << foodItem.price);

		BREAKLINE;
	}

	BREAKLINE;
	PRINTLN("<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>");
}


void printOrders(const std::vector<OrderItem>& orders) {
	BREAKLINE;
	PRINTLN("<<<<<<<<<<<<<<<<<<<<<<<<<< YOUR ORDERS >>>>>>>>>>>>>>>>>>>>>>>>>");
	BREAKLINE;
	PRINT(std::setw(5) << std::left << "ID");
	PRINT(std::setw(25) << std::left << "Food");
	PRINT(std::setw(10) << std::left << "Price(RM)");
	PRINT(std::setw(10) << std::left << "Quantity");
	PRINT(std::setw(15) << std::left << "Net Price(RM)");
	BREAKLINE;

	for (const auto& order : orders) {
		PRINT(std::setw(5) << std::left << order.food.id);
		PRINT(std::setw(25) << std::left << order.food.foodName);
		PRINT(std::setw(10) << std::left << order.food.price);
		PRINT(std::setw(10) << std::left << order.quantity);
		PRINT(std::setw(15) << std::left << order.netPrice);

		BREAKLINE;
	}

	BREAKLINE;
	PRINTLN("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>");
}