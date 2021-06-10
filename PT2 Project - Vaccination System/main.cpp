#include <iostream>
#include <string>
#include "./utilities.h"
#include "./project.h"
#include "./database.h"


void UserMenu();
void displayMainMenu();
void CheckStatus() {}
void RegisterVaccine() {}
void UpdateStock() {}
void UpdateUser() {}
void UpdateInfo() {}


//  Vaccine Registration: //ETHAN LEONG YI THIAN3

//  Enter your name:[name]
//  Hello, [name]
//  input ic
//  ic verification 
//  check ic (loop)
//  1.if ic not inside text file(Database) then input age, city , state,then display: Successfully registered(Name,IC,age,city state input to txt file),press anything to continue
//      Enter Name,IC,State?
//  2.else if ic found inside text file ,
//      display Info:You alrdy registered,
//      Press anything to go back menu...  

//  Check Vaccine Status: //ZR 
//  Enter your IC:[IC]
//  check ic(loop text file)
//  external function{status}
//  1. if ic found in txt, display:[Name][IC][age][city][state][dose taken],press anything to continue
//  2. if not found in txt,display: would you like to register for the vaccine
//      2.1 go to main menu ( remind la if yes )

//  Update Info -CYK
//      Enter user IC: [IC],display {status}
//      setlocation : state: - , city: - ,display {status}

//  ADMIN-CYK
//  Update Stock-CYK
//      Enter brand: [brand]
//      ++stock if got order 
//      --stock when a user is vaccinated


// Update User  -CYK
// Enter patient ic 
// check ic(loop user text file)                                          
// if found ic                                                            
//      display{status}, user dose++, stock decreaseAmount       
// if not found ic, display: Patient doesnt exist,re-enter IC or exit admin menu

void UserMenu() {
    int choice;
    system("cls");
    system("color C");
    cout << "===============" << endl;
    cout << "  User Page" << endl;
    cout << "===============" << endl;
    cout << "Hello, what do you want to perform? " << endl;
    cout << "1. Vaccine Registeration" << endl;
    cout << "2. Check Your Vaccine status" << endl;
    cout << "3. Update Info " << endl;
    cout << "4. Back to Main Menu" << endl << endl;
    choice = getUserChoice(1, 4);
    switch (choice) {
    case(1):
        CheckStatus();
        break;
    case(2):
        RegisterVaccine();
        break;
    case(3):
        UpdateInfo();
        break;
    case(4):
        return;
    }
}
void AdminMenu() {
    int choice;
    system("cls");
    system("color A");
    cout << "===============" << endl;
    cout << "  Admin Page" << endl;
    cout << "===============" << endl;
    cout << "Hello, what do you want to perform? " << endl;
    cout << "1. Update Stock" << endl;
    cout << "2. Update User Vaccine Status" << endl;
    cout << "3. Back to Main Menu" << endl << endl;
    choice = getUserChoice(1, 3);
    switch (choice) {
    case(1):
        UpdateStock();
        break;
    case(2):
        UpdateUser();
        break;
    case(3):
        return;
    }
}

void displayMainMenu() {
    int choice;

    while (true) {
        system("cls");
        system("color F");
        cout << "WELCOME TO URVACCINE" << endl << endl;
        cout << "Select Options : 1. User " << endl;
        cout << "               : 2. Admin" << endl;
        cout << "               : 3. Exit" << endl;
        choice = getUserChoice(1, 3);
        switch (choice) {
        case(1):
            cout << endl;
            UserMenu();
            break;
        case (2):
            cout << endl;
            AdminMenu();
            break;
        case (3):
            goto outside;
        }
    }
outside:
    cout << endl << "Thank you for choosing us" << endl;
}


int main() {
    //VaccineBrand b1("AZ", 69);
    //b1.displayInfo();
    //b1.decreaseAmount(12);
    //b1.displayInfo();
    //b1.increaseAmount(123);
    //b1.displayInfo();
    //User per("SOH", 69, "69696966969");
    //per.setLocation("Johor", "Kulai");
    //per.displayInfo();

    cout << loadUsers() << endl;
    cout << user_size << endl;

    cout << userLists[0] << endl;

    return 0;
}