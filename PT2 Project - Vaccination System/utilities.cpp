#include <iostream>
#include "./utilities.h"
using namespace std;


int getUserChoice(int rangeFrom, int rangeTo) {
	int choice;
	cout << "Enter your choice: ";
	cin >> choice;

	while (choice < rangeFrom || choice > rangeTo) {
		cout << "Invalid choice! Your choice must range from " << rangeFrom << " to " << rangeTo << endl;
		cout << "Enter your choice again: ";
		cin >> choice;
	}
	return choice;
}