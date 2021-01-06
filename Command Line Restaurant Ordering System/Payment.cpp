#include <string>
#include <iostream>
#include <vector>
#include "Utilities.h";


bool displayPayment(const std::vector<OrderItem>& orders);
std::string obtainCustomerInfo();


bool displayPayment(const std::vector<OrderItem>& orders) {
	std::system("color E");

	std::string info = obtainCustomerInfo();

	std::system("cls");
	PRINTLN("Your Delivery Information: " << info);
	BREAKLINE;
	PRINTLN("<<<<<<<<<<<<<<<<<<<< Payment Gateway >>>>>>>>>>>>>>>>>>>> ");
	BREAKLINE;
	PRINTLN("1. Credit / Debit Card");
	PRINTLN("2. Online Banking");
	PRINTLN("3. Cash on Delivery");
	PRINTLN("4. Return to Ordering");
	BREAKLINE;
	PRINTLN("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>> ");

	int choice = obtainUserChoice(1, 4);


	if (choice == 4) return false;
}


std::string obtainCustomerInfo() {
	std::system("cls");

	std::string info = "";
	std::string input;

	PRINTLN("Enter your Telephone Number");
	PRINTLN("EG: 012-34567890: ");
	std::getline(std::cin, input);
	info += input + " | ";

	BREAKLINE;
	PRINTLN("Enter your Address");
	PRINTLN("EG: 1234, Jalan ABC 1, Taman DEF: ");
	std::getline(std::cin, input);
	info += input + ", ";

	BREAKLINE;
	PRINTLN("Enter your Postcode");
	PRINTLN("EG: 12345: ");
	std::getline(std::cin, input);
	info += input;

	return info;
}