#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

#include "./project.h"
#include "./database.h"
using namespace std;

/*	TODO:
	>	Writing to files require access to each file members. Thus either
		set as friend function, or make getters
	>	In the implementation, I've made this function to be friend function
		of the classes in project.h
	>	Number of vaccine is too much (12). Reduce!
	>	Changed Person's full_name, age, IC variables to protected access
	>	User's getVaccineProfile is not implemented
	>	Pointers must be initialized to NULL! Especially in VaccineProfile firstCenter & secondCenter
*/

//	Global Arrays of Object - User, Admin, VaccineCenters
VaccineCenter vaccineCenterLists[13];
User userLists[MAX_USER_SIZE];
Admin adminLists[MAX_ADMIN_SIZE];
int user_size = 0;
int admin_size = 0;


//	Saves VaccineCenter Data.
//	Data saved:
//		Center name, Center state, and For each Vaccine Brands: ( Brand name, Brand Amount )
bool saveVaccineCenter() {
	ofstream saveFile(VACCINE_CENTER_FILELOC, ofstream::out);
	if (!saveFile.is_open()) return false;

	for (VaccineCenter& c : vaccineCenterLists) {
		saveFile << c.centerName << "," << c.centerState;
		
		for (VaccineBrand& v : c.brand) 
			saveFile << "," << v.brand << "," << v.amount;
		saveFile << "\n";
	}
	saveFile.close();
	return true;
}



//	Loads VaccineCenter Data
bool loadVaccineCenter() {
	ifstream saveFile(VACCINE_CENTER_FILELOC, ifstream::in);
	int counter = 0;
	if (!saveFile.is_open()) return false;

	for (int counter = 0; !saveFile.eof(); ++counter) {
		string line;
		getline(saveFile, line);
		if (!line.length()) break;
		stringstream ss(line);

		string centerName, centerState;
		getline(ss, centerName, ',');
		getline(ss, centerState, ',');
		
		vaccineCenterLists[counter] = VaccineCenter(centerName, centerState);
		for (int vaccineIndex = 0; ss; ++vaccineIndex) {
			string brandName;
			int amount;

			getline(ss, brandName, ',');
			ss >> amount;
			ss.get();			//	Consumes the comma if present

			vaccineCenterLists[counter].brand[vaccineIndex] = VaccineBrand(brandName, amount);
		}
	}
	saveFile.close();
	return true;
}


//	Performs search and returns the VaccineCenter with provided name
VaccineCenter* getVaccineCenter(string search) {
	if (!search.length()) return nullptr;

	for (VaccineCenter& v : vaccineCenterLists)
		if (v.getName() == search) return &v;
	return nullptr;
}



//	Saves Users Data
//	Data saved:
//		user's name, age, IC, district, state, numDose, brand, firstCenterName, secondCenterName
bool saveUsers() {
	ofstream saveFile(USER_FILELOC, ofstream::out);
	if (!saveFile.is_open()) return false;

	for (int i = 0; i < user_size; ++i) {
		User& u = userLists[i];
		VaccineProfile& vp = u.v;
		saveFile << u.full_name << ',' << u.age << ',' << u.ic << ',' << u.district << ','
			<< u.state << ',' << vp.numDose << ',' << vp.brand << ',';
		cout << vp.firstCenter;
		if (vp.firstCenter) saveFile << vp.firstCenter->getName();
		saveFile << ',';
		if (vp.secondCenter) saveFile << vp.secondCenter->getName();
		saveFile << '\n';
	}
	saveFile.close();
	return true;
}



//	Load Users Data
bool loadUsers() {
	ifstream saveFile(USER_FILELOC, ifstream::in);
	if (!saveFile.is_open()) return false;

	for (user_size = 0; !saveFile.eof(); ++user_size) {
		string line;
		getline(saveFile, line);
		if (!line.length()) break;
		stringstream ss(line);

		string full_name, ic, district, state, firstCenterName, secondCenterName, brand;
		int age, numDose;

		//	Extract informations
		getline(ss, full_name, ',');
		ss >> age;
		ss.get();
		getline(ss, ic, ',');
		getline(ss, district, ',');
		getline(ss, state, ',');
		ss >> numDose;
		ss.get();
		getline(ss, brand, ',');
		getline(ss, firstCenterName, ',');
		getline(ss, secondCenterName);
		
		userLists[user_size] = User(full_name, age, ic);
		userLists[user_size].setLocation(state, district);
		userLists[user_size].v = VaccineProfile(brand);
		VaccineProfile& vp = userLists[user_size].v;
		vp.numDose = numDose;
		vp.firstCenter = getVaccineCenter(firstCenterName);
		vp.secondCenter = getVaccineCenter(secondCenterName);
	}
	saveFile.close();
	return true;
}