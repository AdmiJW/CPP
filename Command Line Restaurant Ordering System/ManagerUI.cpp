
#include "Utilities.h";

void displayManagerMenu() {
	std::system("cls");
	std::system("color 3");

	BREAKLINE;
	PRINTLN("<<<<<<<<<<<<<<<<<<<< MANAGER MENU >>>>>>>>>>>>>>>>>>>> ");
	PRINTLN("1. Update Food Menu");
	PRINTLN("2. Accept Orders");
	PRINTLN("3. View Accepted Orders");
	PRINTLN("4. View Pending Orders");
	PRINTLN("5. View Summary");
	PRINTLN("6. Back to Main Menu");

	int choice = obtainUserChoice(1, 6);

	//	TODO: Make choices
	if (choice == 6) displayMainMenu();
}