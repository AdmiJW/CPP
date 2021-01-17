#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <Windows.h>
#include <iomanip>
#include <ctime>
#include "Utilities.h";


bool displayPayment(const std::vector<OrderItem>& orders);
void obtainCustomerInfo(std::string& telephone, std::string& address);
bool displayCreditCardPayment(std::string & telephone);
bool displayOnlineBankingPayment(std::string& telephone);
bool displayOTP(const std::string& telephone);
bool recordOrder(const std::vector<OrderItem>& orders, const std::string& telephone, const std::string& address);



bool displayPayment(const std::vector<OrderItem>& orders) {
	std::system("color E");

	std::string telephone;
	std::string address;
	obtainCustomerInfo(telephone, address);

	std::system("cls");
	PRINTLN("Your Delivery Information: ");
	PRINTLN("Telephone: " << telephone);
	PRINTLN("Address: " << address);
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

	if (choice == 1 && displayCreditCardPayment(telephone)) return recordOrder(orders, telephone, address);
	else if (choice == 2 && displayOnlineBankingPayment(telephone)) return recordOrder(orders, telephone, address);
	else if (choice == 3) return recordOrder(orders, telephone, address);
	else if (choice == 4) return false;
}


void obtainCustomerInfo(std::string& telephone, std::string& address) {
	std::system("cls");

	std::string input;

	PRINTLN("<<<<<<<<<<<<<<< CUSTOMER INFORMATION >>>>>>>>>>>>>>>>");
	BREAKLINE;

	PRINTLN("Enter your Telephone Number");
	PRINTLN("EG: 012-34567890: ");
	telephone = obtainUserInputWithRegex("[0-9]{2,4}-?[0-9]+", "");

	BREAKLINE;
	PRINTLN("Enter your Address");
	PRINTLN("EG: 1234, Jalan ABC 1, Taman DEF: ");
	std::getline(std::cin, address);
	address.append(", ");

	BREAKLINE;
	address += obtainUserInputWithRegex("[0-9]{5}", "Enter your Postcode: ");
}


bool displayCreditCardPayment(std::string& telephone) {
	std::system("cls");

	std::string input;

	PRINTLN("<<<<<<<<<<<<<<< CREDIT/DEBIT CARD PAYMENT >>>>>>>>>>>>>>>>");
	BREAKLINE;

	obtainUserInputWithRegex("[0-9]{16}", "Enter your Card Number Without Spaces: ");

	BREAKLINE;
	obtainUserInputWithRegex("([0-2][0-9]||3[0-1])/(0[1-9]||1[0-2])", "Enter your Card Expiry Date (DD/MM): ");

	BREAKLINE;
	obtainUserChoice(0, 999, "Enter your Card CVV: ");

	return displayOTP(telephone);
}




bool displayOnlineBankingPayment(std::string& telephone) {
	std::system("cls");

	std::string input;

	PRINTLN("<<<<<<<<<<<<<<< ONLINE BANKING PAYMENT >>>>>>>>>>>>>>>>");
	BREAKLINE;

	PRINTLN("Enter your Bank Account Number: ");
	std::getline(std::cin, input);

	BREAKLINE;
	PRINTLN("Enter your Bank Account Password: ");
	std::getline(std::cin, input);

	return displayOTP(telephone);
}



bool displayOTP(const std::string& telephone) {
	std::system("cls");

	PRINTLN("<<<<<<<<<<<<<<< One-Time Password (OTP) >>>>>>>>>>>>>>>>");
	BREAKLINE;

	PRINTLN("A One-time Password (OTP) has been sent to your mobile number " << telephone);
	BREAKLINE;
	obtainUserChoice(0, 999999, "Please Enter your 6-digit One-time Password(OTP): ");

	for (int i = 0; i < 8; ++i) {
		std::system("cls");
		PRINT("Processing request... Please do not refresh your browser");
		for (int j = 0; j < i; ++j) PRINT('.');
		Sleep(500);
	}

	return true;
}


bool recordOrder(const std::vector<OrderItem>& orders, const std::string& telephone, const std::string& address) {
	auto orderFile = getFileBuffer( ORDERS_CSV );
	auto timeNow = std::time(nullptr);
	tm timeStruct;
	localtime_s(&timeStruct, &timeNow);
	char timeStr[35] = {};
	strftime(timeStr, 35, "%T %a, %F", &timeStruct);

	for (auto order : orders)
		orderFile << "\n" << telephone << '|' << address << '|' << timeStr << '|'
		<< order.food.foodName << '|' << order.quantity << '|' << order.netPrice;

	orderFile.close();

	std::system("cls");
	PRINTLN("<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>");
	PRINTLN("PAYMENT SUCCESSFUL! YOUR FOOD WILL BE DELIVERED SOON!");
	PRINTLN("<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>");
	BREAKLINE;

	pressEnterToContinue("Press Enter to return to Main Menu...");
	return true;
}