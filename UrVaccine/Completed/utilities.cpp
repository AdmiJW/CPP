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
bool icverification(string ic) {
	int month, day, state;
	if (ic.length() != 12)
		return false;
	for (int i = 0; i < 12; i++) {
		if (!isdigit(ic[i]))
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
string GetState() {
	string state;
	int x;
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

string GetBrand() {
	string brand;
	int x;
	cout << "1.Pfizer" << endl;
	cout << "2.AstraZeneca" << endl;
	cout << "3.CanSino" << endl;
	cout << "4.Sinovac" << endl;
	cout << "5.Covax" << endl;
	x = getUserChoice(1,5);
	if (x == 1) brand = "Pfizer";
	if (x == 2) brand = "AstraZeneca";
	if (x == 3) brand = "CanSino";
	if (x == 4) brand = "Sinovac";
	if (x == 5) brand = "Covax";
	return brand;
}

string GetCenterName() {
	string centername;
	int x;
	cout << "1.Johor - Hospital Kesihatan Bukit Indah" << endl;
	cout << "2.Kedah - Hospital Sultanah Bahiyah" << endl;
	cout << "3.Kelantan - Dewan Perpaduan Machang" << endl;
	cout << "4.Malacca - Hospital Besar Melaka" << endl;
	cout << "5.Negeri Sembilan - Klinik Kesihatan Senawang" << endl;
	cout << "6.Pahang - Hospital Tengku Ampuan Afzan" << endl;
	cout << "7.Penang - Hospital Bukit Mertajam" << endl;
	cout << "8.Perak - Dewan Serbaguna Seri Iskandar" << endl;
	cout << "9.Perlis - Hospital Tuanku Fauziah" << endl;
	cout << "10.Sabah - Hospital Queen Elizabeth" << endl;
	cout << "11.Sarawak - Stadium Perpaduan Kuching" << endl;
	cout << "12.Terengganu - Pusat Sains dan Kreativiti" << endl;
	cout << "13.Selangor - Dewan Sukan Pandamaran" << endl;
	x = getUserChoice(1,13);
	if (x == 1) centername =	"Hospital Kesihatan Bukit Indah";
	if (x == 2) centername =	"Hospital Sultanah Bahiyah";
	if (x == 3) centername =	"Dewan Perpaduan Machang";
	if (x == 4) centername =	"Hospital Besar Melaka";
	if (x == 5) centername =	"Klinik Kesihatan Senawang";
	if (x == 6) centername =	"Hospital Tengku Ampuan Afzan";
	if (x == 7) centername =	"Hospital Bukit Mertajam";
	if (x == 8) centername =	"Dewan Serbaguna Seri Iskandar";
	if (x == 9) centername =	"Hospital Tuanku Fauziah";
	if (x == 10) centername =	"Hospital Queen Elizabeth";
	if (x == 11) centername =	"Stadium Perpaduan Kuching";
	if (x == 12) centername =	"Pusat Sains dan Kreativiti";
	if (x == 13) centername =	"Dewan Sukan Pandamaran";
	return centername;
}