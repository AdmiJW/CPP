#include <iostream>
#include <cstdlib>
#include <cstring>
#include "./utilities.h"

using namespace std;
//Return Choice 
int getUserChoice(int rangeFrom, int rangeTo) {
	int choice;
	cout << "Enter your choice: ";
	cin >> choice;
	
	while (choice < rangeFrom || choice > rangeTo) {
		cout << "Invalid Input. Valid input only ranges from " << rangeFrom << " to " << rangeTo << endl;
		cout << "Enter your choice again: ";

		cin.clear();					//	If invalid input, the cin fail() will set to true. Clear it to proceed
		cin.ignore(INT32_MAX, '\n');	//	Ignore all characters until newline character
		cin >> choice;
	}

	cin.ignore(INT32_MAX, '\n');	//Valid input but \n left in the input buffer.
	cout << "\n";
	return choice;
}
//IC verification
bool icverification(string ic){
	int month, day, state;
	if(ic.length() != 12)
		return false;
	for(int i=0;i<12;i++){
		if(!isdigit(ic[i]))
			return false; 
	}
	month = stoi(ic.substr(2, 4));
	day = stoi(ic.substr(4, 6));
	state = stoi(ic.substr(6, 8));
	if ((month < 0 && month>12) && (day < 0 && day>31) && (state < 0 && state>13)) {
		return false;
	}
	return true;
}
//return state 
string GetState(){
	string state;
	int x=0;
	cout << "1.Johor" << endl;
	cout << "2.Kedah" << endl;
	cout << "3.Kelantan" << endl;
	cout << "4.Malacca" << endl;
	cout << "5.Negeri Sembilan" << endl;
	cout << "6.Pahang" << endl;
	cout << "7.Penang" << endl;
	cout << "8.Perak" << endl;
	cout << "9.Perlis" << endl;
	cout << "10.Sabah" << endl;
	cout << "11.Sarawak" << endl;
	cout << "12.Terengganu" << endl;
	cout << "13.Selangor" << endl;
	x = getUserChoice(1, 13);
	if (x == 1) state = "Johor"; 
	if (x == 2) state = "Kedah"; 
	if (x == 3) state = "Kelantan";
	if (x == 4) state = "Malacca";
	if (x == 5) state = "Negeri Sembilan";
	if (x == 6) state = "Pahang";
	if (x == 7) state = "Penang";
	if (x == 8) state = "Perak";
	if (x == 9) state = "Perlis";
	if (x == 10)state = "Sabah";
	if (x == 11)state = "Sarawak";
	if (x == 12)state = "Terengganu";
	if (x == 13)state = "Selangor";
	return state;
}
// Age verification
bool check_age(int a) {
	if (a >= 0 && a < 120)
		return true;
	return false;
}