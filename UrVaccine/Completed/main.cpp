/* =======================================================
 /$$   /$$ /$$$$$$$  /$$    /$$  /$$$$$$   /$$$$$$   /$$$$$$  /$$$$$$ /$$   /$$ /$$$$$$$$
| $$  | $$| $$__  $$| $$   | $$ /$$__  $$ /$$__  $$ /$$__  $$|_  $$_/| $$$ | $$| $$_____/
| $$  | $$| $$  \ $$| $$   | $$| $$  \ $$| $$  \__/| $$  \__/  | $$  | $$$$| $$| $$
| $$  | $$| $$$$$$$/|  $$ / $$/| $$$$$$$$| $$      | $$        | $$  | $$ $$ $$| $$$$$
| $$  | $$| $$__  $$ \  $$ $$/ | $$__  $$| $$      | $$        | $$  | $$  $$$$| $$__/
| $$  | $$| $$  \ $$  \  $$$/  | $$  | $$| $$    $$| $$    $$  | $$  | $$\  $$$| $$
|  $$$$$$/| $$  | $$   \  $/   | $$  | $$|  $$$$$$/|  $$$$$$/ /$$$$$$| $$ \  $$| $$$$$$$$
 \______/ |__/  |__/    \_/    |__/  |__/ \______/  \______/ |______/|__/  \__/|________/


Name
Member 1 : Soh Jun Wei          (A20EC0151)
Member 2 : Ethan Leong Yi Tian  (A20EC0033)
Member 3 : Cheah Yau Khin       (A20EC0185)
Member 4 : Soh Zen Ren          (A20EC0152)

Lecturer: Dr. Bander Ali Saleh Al-rimy
Date submission: 26/6/2021

IMPORTANT:
To log in as Admin, use:
    IC: 123456789012
    Password: 3333
======================================================= */

#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
#include <stdlib.h>
#include <iomanip>
#include "./utilities.h"
#include "./project.h"
#include "./database.h"
using namespace std;
void UserMenu();
void displayMainMenu();
void CheckStatus();
void RegisterVaccine(User);
void UpdateStock();
void UpdateUser();
void UpdateInfo();
void AdminRegister(Admin);

//=========================================
//  USER OPERATIONS
//=========================================

//  Vaccine Registration: 
void RegisterVaccine(User p) {
    system("cls");
    system("color E");

    string name;
    cout << "Please enter your full name: ";
    getline(cin, name, '\n');
    cout << "Hello, Mr/Mrs " << name << endl;
    string IC;
    cout << "Please enter your identification card number (IC no.): ";
    getline(cin, IC, '\n');
    //IC verification
    while (!icverification(IC)) {
        cout << " Invalid ic  !! Please ensure that your ic is in digit only!" << endl;
        cout << "Input your ic: " << endl;
        cin >> IC;
    }
    // CHECK IC
    if (getUser(IC) == NULL) {
        int age;
        string district, state;

        cout << "Please enter you age: ";
        cin >> age;
        while (!check_age(age)) {
            cout << "Invalid age!" << endl;
            cout << "Please enter you age: ";
            cin >> age;
        }
        cin.ignore(1);

        cout << "Please enter your current living district: ";
        getline(cin, district, '\n');
        cout << "Please enter your current living state: " << endl;
        state = GetState();

        User p(name, age, IC);
        p.setLocation(district, state);
        system("cls");
        cout << "Please wait second for the registeration, do not close the window..." << endl << endl;
        Sleep(3000);
        system("cls");
        cout << "Congratulation, Mr/Mrs" << name << " you have successfully register the vaccination program!" << endl << endl;
        p.displayInfo();

        addUser(p);
        saveUsers();
        system("pause");
    }
    else {
        cout << "..........................." << endl;
        Sleep(1000);
        cout << "You are already registered the vaccination program !" << endl;
        system("pause");
    }
}
////  Check Vaccine Status: 
void CheckStatus() {
    string IC;
    cout << "Input your ic: " << endl;
    cin >> IC;
    //IC verification
    while (!icverification(IC)) {
        cout << " Invalid ic  !! Please ensure that your ic is in digit only!" << endl;
        cout << "Input your ic: " << endl;
        cin >> IC;
    }
    User* search = getUser(IC);
    system("cls");
    if (search == nullptr) {
        cout << "IC not found in database!" << endl;
        char choice;
        cout << "Would you like to register for vaccine ? Enter y for yes " << endl;
        cin >> choice;
        if (choice == 'y')
            cout << "Remember choose 1 at menu to register ^v^" << endl;
    }
    else
        search->displayInfo();
    system("pause");
}
//Update Info 
void UpdateInfo() {
    string IC;
    string state;
    string district;

    cout << "Enter User IC : ";
    cin >> IC;
    //Ic verification
    while (!icverification(IC)) {
        cout << " Invalid ic  !! Please ensure that your ic is in digit only!" << endl;
        cout << "Input your ic: " << endl;
        cin >> IC;
    }
    User* C_User = getUser(IC);
    system("cls");

    if (C_User == nullptr) {
        cout << "IC is not found !!" << endl;
        system("pause");
        return;
    }
    else {
        C_User = getUser(IC);
        C_User->displayInfo();
        cout << endl;
        cout << "Enter New State : "<<endl;
        state = GetState();
        cout << "Enter New District : ";
        getline(cin, district);//wow
        C_User->setLocation(state, district);
        saveUsers();

        cout << "Successfully changed state and district: " << state << ", " << district << endl;
        system("pause");
    }
}


//=========================================
//  ADMIN OPERATIONS
//=========================================
void AdminRegister() {
    system("cls");
    system("color B");
    string name;
    cout << "Please enter your full name: ";
    getline(cin, name, '\n');
    cout << "Hello, Mr/Mrs " << name << endl;
    string IC;
    cout << "Please enter your identification card number (IC no.): ";
    getline(cin, IC, '\n');
   
    //IC verification
    while (!icverification(IC)) {
        cout << " Invalid ic  !! Please ensure that your ic is in digit only!" << endl;
        cout << "Input your ic: " << endl;
        cin >> IC; }

    // CHECK IC
    if (getAdmin(IC) == NULL) {
        int age;
        string center, pw;
        cout << "Please enter your age: ";
        cin >> age;
        while (!check_age(age)) {
            cout << "Invalid age!" << endl;
            cout << "Please enter your age: ";
            cin >> age;}
        cin.ignore(1);

        cout << "Please enter a password (pw no.): ";
        getline(cin, pw, '\n');

        cout << "Please select a vaccine center : " << endl;
        center = GetCenterName();

        Admin q(name, age, IC ,getVaccineCenter(center));
        q.setPassword(pw);
        system("cls");
        cout << "Please wait second for the registeration, do not close the window..." << endl <<endl;
        Sleep(3000);
        system("cls");
        cout << "Congratulation, Mr/Mrs" << name << " you have successfully become an admin !" << endl << endl;
        q.displayInfo();
        addAdmin(q);
        saveAdmins();
        system("pause");
    }
    else {
        cout << "..........................." << endl;
        Sleep(1000);
        cout << "You are already an admin !" << endl;
        system("pause");
    }
}


void UpdateStock(Admin* admin) {
    VaccineCenter* Center;
    string centername;
    string brand;
    int amount;

    Center = admin->getCenter();

    cout << "Select Vaccine Brand : "<<endl;
    brand = GetBrand();
    cout << "Enter Vaccine Amount : ";
    cin >> amount;
   
    Center->updateVaccine(brand, amount);
    cout << "\nSuccessfully Updated. Latest Info:\n";
    Center->displayInfo();

    saveVaccineCenter();

    system("pause");
}
//Update User
void UpdateUser(Admin* admin) {
    string IC, brand;
    cout << "Input patient ic: " << endl;
    getline(cin, IC, '\n');

    // Ic verification
    while (!icverification(IC)) {
        cout << " Invalid ic  !! Please ensure that your ic is in digit only!" << endl;
        cout << "Input your ic: " << endl;
        cin >> IC;
    }
    User* search = getUser(IC);
    while (search == nullptr) {
        int choice;
        cout << "IC is not found !!Press 1 for reenter and 2 for exit to main menu! " << endl;
        cin >> choice;
        choice = getUserChoice(1, 2);
        if (choice == 1) {
            cout << "Reenter ic: " << endl;
            cin >> IC;
            User* search = getUser(IC);
        }
        else if (choice == 2) {
            return;
        }
    }

    system("cls");
    search->displayInfo();

    if (search->getVaccineProfile().getDose() >= 2) {
        cout << "\nThe patient already had 2 doses!\n";
        system("pause");
        return;
    }

    brand=GetBrand();
    VaccineCenter* vc = admin->getCenter();
    int amount = vc->checkVaccine(brand);
    cout<< "Vaccine left for brand " << brand <<" : "<< amount << endl;
    if(amount == 0){
        cout << "Inadequate stock. Please restock via update vaccine option first" << endl;
        system("pause");
        return;
    }
    vc->updateVaccine(brand,-1);

    int dose = search->getVaccineProfile().getDose();
     cout<<"Registering dose " << (dose+1) << " for patient" << endl;
    if ( dose== 0 ) {
        search->getVaccineProfile().updateDose();
        search->getVaccineProfile().setFirstCenter(admin->getCenter(), brand);
    }else if(dose == 1){
        search->getVaccineProfile().updateDose();
        search->getVaccineProfile().setSecondCenter(admin->getCenter(), brand);
    }
    cout << "Vaccine has successfully registered !" << endl;

    saveUsers();
    saveVaccineCenter();

    system("pause");
}
//USER MENU 
void UserMenu() {
    int choice;
    User patient;

    system("cls");
    system("color C");
    cout << "===============" << endl;
    cout << "  User Page" << endl;
    cout << "===============" << endl;
    cout << "Hello, what do you want to perform? " << endl;
    cout << "1. Check Your Vaccine status" << endl;
    cout << "2. Vaccine Registeration" << endl;
    cout << "3. Update Info " << endl;
    cout << "4. Back to Main Menu" << endl << endl;
    choice = getUserChoice(1, 4);
    switch (choice) {
    case(1):
        CheckStatus();
        break;
    case(2):
        RegisterVaccine(patient);
        break;
    case(3):
        UpdateInfo();
        break;
    case(4):
        return;
    }
}


//ADMIN MENU 
void AdminMenu() {
    int choice;
    system("cls");
    system("color A");

    string ic;
    string pw;
    cout << "===============" << endl;
    cout << "  LOG IN Page" << endl;
    cout << "===============" << endl;
    cout << "Please enter your IC : ";
    getline(cin, ic, '\n');
    while(icverification(ic)==false){
        cout << "Please enter a valid IC : ";
        getline(cin, ic, '\n');
    }
    Admin* search = getAdmin(ic);
    if (search != nullptr) {
        cout << "Please enter your password : ";
        getline(cin, pw, '\n');
        if(search->verifyPassword(pw) == false){
            cout << "Incorrect password. Returning to main menu in 2 seconds" << endl;
            Sleep(2000);
            return;
        }
    }
    else{
        cout << "You are not an admin." << endl;
        cout << "Try:" << endl;
        cout << "   1. Register as an admin" << endl;
        cout << "   2. Enter a valid IC"<<endl<<endl;
        system("pause");
        return;
    }
    cout << "You are log in as :" << endl;
    search->displayInfo();
    cout << endl << "Loading.........." << endl;
    Sleep(3000);
    system("cls");
    system("color A");

    while (true) {
        cout << "===============" << endl;
        cout << "  Admin Page" << endl;
        cout << "===============" << endl;
        cout << "Hello, What Do You Want To Perform?" << endl;
        cout << "1. Register Admin" << endl;
        cout << "2. Update Stock" << endl;
        cout << "3. Update User Vaccine Status" << endl;
        cout << "4. Back to Main Menu" << endl << endl;
        choice = getUserChoice(1, 4);

        switch (choice) {
        case(1):
            AdminRegister();
            break;
        case(2):
            UpdateStock(search);
            break;
        case(3):
            UpdateUser(search);
            break;
        case(4):
            return;
        }
        system("cls");
    }
}
//MAIN MENU 
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
    cout << "\n" << "Thank you for choosing us" << endl;
}


// ./Debug/UrVaccine.exe
int main() {
    loadVaccineCenter();
    loadUsers();
    loadAdmins();
    displayMainMenu();

    return 0;
}