#include <iostream>
#include <string>
#include <iomanip>

#include "./project.h"
#include "./database.h"
using namespace std;


//=========================
//  VaccineBrand class
//=========================
VaccineBrand::VaccineBrand() {}
VaccineBrand::VaccineBrand(string brand, int amount) {
    this->brand = brand;
    this->amount = amount;
}

void VaccineBrand::displayInfo() {
    cout << "Vaccine Brand : " << brand << endl;
    cout << "Vaccine Amount : " << amount << endl << endl;
}

string VaccineBrand::getBrand() {
    return brand;
}

void VaccineBrand::decreaseAmount(int x) {
    amount = amount - x;
}

void VaccineBrand::increaseAmount(int x) {
    amount = amount + x;
}

//=========================
//  VaccineCentre class
//=========================
VaccineCenter::VaccineCenter() {}
VaccineCenter::VaccineCenter(string centerName, string centerState) :
    centerName(centerName), centerState(centerState) {}
void VaccineCenter::displayInfo() {
    cout << "===========================================\n"
        << " Vaccine Center: " << centerName << "\n"
        << " of " << centerState << "\n"
        << "===========================================\n"
        << "\nAvailable Stocks:\n\n";
    for (VaccineBrand& b : brand)
        b.displayInfo();
}
string VaccineCenter::getName() {
    return centerName;
}
string VaccineCenter::getState() {
    return centerState;
}


void VaccineCenter::updateVaccine(string vaccineBrand, int delta) {
    for (VaccineBrand& b : brand) {
        if (b.getBrand() == vaccineBrand) {
            if (delta < 0) b.decreaseAmount(-delta);
            else b.increaseAmount(delta);
            break;
        }
    }
}

//=========================
//  VaccineProfile class
//=========================
VaccineProfile::VaccineProfile(): firstCenter(0), secondCenter(0) {}
VaccineProfile::VaccineProfile(string brand): VaccineProfile()
{
    this->brand = brand;
}
void VaccineProfile::setFirstCenter(VaccineCenter* firstC) { firstCenter = firstC; }
void VaccineProfile::setSecondCenter(VaccineCenter* secondC) { secondCenter = secondC; }
void VaccineProfile::updateDose(int num) {
    ++numDose;
}

//=========================
//  Person class
//=========================
Person::Person() {};
Person::Person(string full_name, int age, string ic) {
    this->full_name = full_name;
    this->age = age;
    this->ic = ic;
};
void Person::displayInfo() {
    cout << *this;
}
ostream& operator<<(ostream& out, Person& p) {
    out << left << setw(10) << "Name" << ":" << p.full_name << endl
        << setw(10) << "Age" << ":" << p.age << endl
        << setw(10) << "IC" << ":" << p.ic << endl;
    return out;
}

//=========================
// User class
//=========================
User::User() {}
User::User(string name, int age, string ic) :Person(name, age, ic) {}

void User::displayInfo() {
    cout << *this;
}
void User::setLocation(string st, string dt) {
    state = st;
    district = dt;
}
VaccineProfile& getVaccineProfile();
ostream& operator<<(ostream& out, User& user) {
    out << static_cast<Person&>(user);
    out << left << setw(10) << "District" << ":" << user.district << endl << setw(10) << "State" << ":" << user.state << endl;
    return out;
}
//=========================
//  Admin class
//=========================
Admin::Admin() {}
Admin::Admin(string full_name, int age, string ic, VaccineCenter* vc) :
    center(vc), Person(full_name, age, ic) {}

void Admin::displayInfo() {
    cout << *this;
}

VaccineCenter* Admin::getCenter() {
    return center;
}
ostream& operator<<(ostream& out, Admin& a) {
    out << static_cast<Person&>(a);
    out << left << setw(10) << "Center" << ":" << a.center->getName() << endl;
    out << left << setw(10) << "State" << ":" << a.center->getState() << endl;
    return out;
}