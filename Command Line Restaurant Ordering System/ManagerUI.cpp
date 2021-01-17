#include <vector>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <unordered_map>
#include <unordered_set>
#include "Utilities.h";


void updateFoodMenu();
void acceptOrders();
void displayOrderHistory();
void displayHistorySummary();
void addFoodItem(std::vector<FoodItem>& foodItems);
void deleteFoodItem(std::vector<FoodItem>& foodItems);
void modifyFoodItem(std::vector<FoodItem>& foodItems);
void saveFoodMenuChanges(const std::vector<FoodItem>& foodItems);
void overWriteOrders(const std::vector<DetailedOrderItem>& orders);
void appendHistoryChanges(const std::vector<DetailedOrderItem>& accepted);



void displayManagerMenu() {

	while (1) {
		std::system("cls");
		std::system("color 6");

		BREAKLINE;
		PRINTLN("<<<<<<<<<<<<<<<<<<<< MANAGER MENU >>>>>>>>>>>>>>>>>>>> ");
		BREAKLINE;
		PRINTLN("1. Update Food Menu");
		PRINTLN("2. Accept Orders");
		PRINTLN("3. Order History");
		PRINTLN("4. View Summary");
		PRINTLN("5. Back to Main Menu");
		BREAKLINE;
		PRINTLN("<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>> ");

		int choice = obtainUserChoice(1, 5);

		//	TODO: Make choices
		if (choice == 1) updateFoodMenu();
		else if (choice == 2) acceptOrders();
		else if (choice == 3) displayOrderHistory();
		else if (choice == 4) displayHistorySummary();
		else if (choice == 5) return;
	}
}



void updateFoodMenu() {
	auto foodBuffer = getReadFileBuffer( FOODMENU_CSV );
	auto foodItems = readFoodMenu(foodBuffer);

	while (1) {
		std::system("cls");

		BREAKLINE;
		PRINTLN("<<<<<<<<<<<<<<<<<<<<<<<<< Update Food Menu >>>>>>>>>>>>>>>>>>>>>>>>>");
		BREAKLINE;
		PRINTLN("1. Add New Food Item");
		PRINTLN("2. Delete Food Item");
		PRINTLN("3. Modify Food Item");
		PRINTLN("4. Save Changes and Return to Manager Menu");
		PRINTLN("5. Discard Changes and Return to Manager Menu");
		BREAKLINE;
		PRINTLN("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>");

		int choice = obtainUserChoice(1, 5);

		if (choice == 1) addFoodItem(foodItems);
		else if (choice == 2) deleteFoodItem(foodItems);
		else if (choice == 3) modifyFoodItem(foodItems);
		else if (choice == 4) {
			saveFoodMenuChanges(foodItems);

			PRINTLN("Changes Successfully saved!");
			pressEnterToContinue();
			break;
		}
		if (choice == 5) break;
	}
}


void addFoodItem(std::vector<FoodItem>& foodItems) {
	std::string newFoodName;
	float newFoodPrice;

	BREAKLINE;
	newFoodName = obtainUserInputWithRegex("[a-zA-Z ]+", "Please Enter Food Name: ");
	BREAKLINE;
	newFoodPrice = obtainUserChoice(0.01F, 999.9F, "Please Enter Food Price: ");
	BREAKLINE;

	foodItems.emplace_back( FoodItem { UINT32_MAX, newFoodName, newFoodPrice } );

	PRINTLN("Successfully added new Food Item: " << newFoodName);
	pressEnterToContinue();
}


void deleteFoodItem(std::vector<FoodItem>& foodItems) {
	std::system("cls");

	if (!foodItems.size()) {
		PRINTLN("There is currently nothing in Food Menu! Please add some Food Items first!");
		pressEnterToContinue();
		return;
	}

	printFoodMenu(foodItems);

	BREAKLINE;
	int toDelete = obtainUserChoice(0, foodItems.size(), "Please enter the code of Food Item to remove (or 0 to cancel): ");

	if (!toDelete) return;
	
	foodItems.erase(foodItems.begin() + toDelete - 1);
	PRINTLN("Food Item ID " << toDelete << " successfully Erased!");
	pressEnterToContinue();
}


void modifyFoodItem(std::vector<FoodItem>& foodItems) {
	std::system("cls");

	if (!foodItems.size()) {
		PRINTLN("There is currently nothing in Food Menu! Please add some Food Items first!");
		pressEnterToContinue();
		return;
	}

	printFoodMenu(foodItems);

	BREAKLINE;
	int toDelete = obtainUserChoice(0, foodItems.size(), "Please enter the code of Food Item to modify (or 0 to cancel): ");

	if (!toDelete) return;

	std::string newFoodName;
	float newFoodPrice;
	BREAKLINE;
	newFoodName = obtainUserInputWithRegex("[a-zA-Z ]*", "Please Enter Food Name (or ENTER to remain same): ");
	BREAKLINE;
	newFoodPrice = obtainUserChoice(0.0F, 999.9F, "Please Enter Food Price (or 0 to remain same): ");
	BREAKLINE;

	if (!newFoodName.empty()) foodItems[toDelete - 1].foodName = newFoodName;
	if (newFoodPrice) foodItems[toDelete - 1].price = newFoodPrice;
	PRINTLN("Food Item ID " << toDelete << " Successfully Modified!");
	pressEnterToContinue();
}



void acceptOrders() {
	auto orderBuffer = getReadFileBuffer(ORDERS_CSV);
	auto orderItems = readOrderMenu(orderBuffer);

	if (!orderItems.size()) {
		PRINTLN("There are currently no ongoing orders! :(");
		pressEnterToContinue();
		return;
	}

	std::vector<DetailedOrderItem> accepted;

	while (1) {
		std::system("cls");

		printOrderMenu(orderItems);

		BREAKLINE;
		PRINTLN("<<<<<<<<<<<<<<<<<<<<<<<<< Accept Orders >>>>>>>>>>>>>>>>>>>>>>>>>");
		BREAKLINE;
		PRINTLN("1. Accept Order");
		PRINTLN("2. Reject Order");
		PRINTLN("3. Save Changes and Return to Manager Menu");
		PRINTLN("4. Discard Changes and Return to Manager Menu");
		BREAKLINE;
		PRINTLN("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>");

		int choice = obtainUserChoice(1, 4);

		if (choice == 1) {
			int toAccept = obtainUserChoice(0, orderItems.size(), "Enter the ID of order to accept (or 0 to cancel): ");
			if (!toAccept) continue;
			
			accepted.emplace_back( orderItems[toAccept - 1] );
			orderItems.erase(orderItems.begin() + toAccept - 1);

			PRINTLN("Order ID " << toAccept << " Accepted Successfully!");
			pressEnterToContinue();
		}
		else if (choice == 2) {
			int toReject = obtainUserChoice(0, orderItems.size(), "Enter the ID of order to reject (or 0 to cancel): ");
			if (!toReject) continue;

			orderItems.erase(orderItems.begin() + toReject - 1);

			PRINTLN("Order ID " << toReject << " Deleted Successfully!");
			pressEnterToContinue();
		}
		else if (choice == 3) {
			appendHistoryChanges(accepted);
			overWriteOrders(orderItems);

			PRINTLN("Accepted Orders Successfully Saved!");
			pressEnterToContinue();
			return;
		}
		else if (choice == 4) break;
	}
}



void displayOrderHistory() {
	auto historyBuffer = getReadFileBuffer(HISTORY_CSV);
	auto historyItems = readOrderMenu(historyBuffer);
	printOrderMenu(historyItems);

	pressEnterToContinue();
}


void displayHistorySummary() {
	std::system("cls");

	auto historyBuffer = getReadFileBuffer(HISTORY_CSV);
	auto historyItems = readOrderMenu(historyBuffer);
	
	float sumEarnings = 0;
	int totalOrders = 0;
	int totalFoods = 0;
	std::unordered_map< std::string, unsigned int> foodCount;
	std::unordered_set<std::string> customerTel;

	for (const DetailedOrderItem& order : historyItems) {
		sumEarnings += order.netPrice;
		++totalOrders;
		totalFoods += order.quantity;

		auto foodItem = foodCount.find(order.food);
		if (foodItem == foodCount.end())
			foodCount[order.food] = order.quantity;
		else foodItem->second += order.quantity;

		customerTel.insert(order.address);
	}

	PRINTLN("<<<<<<<<<<<<<<<<<<<< SUMMARY >>>>>>>>>>>>>>>>>>>>");
	BREAKLINE;
	PRINTLN("Total Earnings So Far: RM" << sumEarnings);
	PRINTLN("Total Orders Accepted: " << totalOrders);
	PRINTLN("Total Foods Prepared: " << totalFoods);
	PRINTLN("Total Different Customers by Telephone: " << customerTel.size());
	BREAKLINE;
	PRINTLN("=============== Food Popularity Breakdown ===============");
	PRINTLN(std::setw(30) << std::left << "Food" << std::setw(30) << std::left << "Popularity");
	for (auto pairs : foodCount) {
		PRINT(std::setw(30) << std::left << pairs.first);
		PRINTLN(std::setw(30) << std::left << pairs.second << " (" << (pairs.second * 100.0 / totalFoods) << "%)");
	}
	BREAKLINE;
	PRINTLN("<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>");

	pressEnterToContinue();
}



void saveFoodMenuChanges(const std::vector<FoodItem>& foodItems) {
	auto outputFile = getWriteFileBuffer( FOODMENU_CSV );
	outputFile << "ID,Name,Price";

	for (int i = 1; i <= foodItems.size(); ++i )
		outputFile << "\n" << i << ',' << foodItems[i - 1].foodName << ',' << foodItems[i - 1].price;
}


void overWriteOrders(const std::vector<DetailedOrderItem>& orders) {
	auto writeFile = getWriteFileBuffer(ORDERS_CSV);

	writeFile << "Telephone|Address|Time|Food|Quantity|Net Price";

	for (const DetailedOrderItem& order : orders) {
		writeFile << "\n" << order.telephone << '|' << order.address << '|' << order.time << '|'
			<< order.food << '|' << order.quantity << '|' << order.netPrice;
	}
}


void appendHistoryChanges(const std::vector<DetailedOrderItem>& accepted) {
	auto appendFile = getFileBuffer(HISTORY_CSV);
	
	for (const DetailedOrderItem& order : accepted) {
		appendFile << "\n" << order.telephone << '|' << order.address << '|' << order.time << '|'
			<< order.food << '|' << order.quantity << '|' << order.netPrice;
	}
}