#include <iostream>
#include "Utilities.h";

void displayMainMenu();
void displayAbouts();
void displayExit();


void displayMainMenu() {
	std::system("cls");
	std::system("color A");

	BREAKLINE;
	PRINTLN("Restaurant Ordering System by SOH");
	BREAKLINE;
	PRINTLN("<<<<<<<<<<<<<<<<<<<< MENU >>>>>>>>>>>>>>>>>>>> ");
	PRINTLN("1. Customer Menu");
	PRINTLN("2. Adminstrator Menu");
	PRINTLN("3. About");
	PRINTLN("4. Exit");

	int choice = obtainUserChoice(1,4);

	if (choice == 1) displayCustomerMenu();
	else if (choice == 2) displayManagerMenu();
	else if (choice == 3) displayAbouts();
	else displayExit();
}


void displayAbouts() {
	std::system("cls");
	std::system("color C");

	PRINTLN("****************************** ABOUT ***********************************");
	BREAKLINE;
	PRINTLN("Restaurant Ordering System by SOH");
	PRINTLN("This is a Command Line Restaurant Ordering System Program written in C++");
	BREAKLINE;
	PRINTLN("************************************************************************");
	BREAKLINE;
	pressEnterToContinue("Press Enter to return to Main Menu... ");
	displayMainMenu();
}


void displayExit() {
	std::system("cls");
	std::system("color E");

	PRINTLN("****************************************");
	BREAKLINE;
	PRINTLN("Thank you for using this program!");
	PRINTLN("Hope to see you soon and have a good day");
	BREAKLINE;
	PRINTLN("****************************************");

	exit(1);
}


int main() {
	displayMainMenu();
}