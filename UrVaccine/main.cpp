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
void AdminRegister() {}

//=========================================
//  USER OPERATIONS
//=========================================

//  Vaccine Registration: 
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
////  Enter your IC:[IC]
////  check ic(loop text file)
////  external function{status}
////  1. if ic found in txt, display:[Name][IC][age][city][state][dose taken],press anything to continue
////  2. if not found in txt,display: would you like to register for the vaccine
////      2.1 go to main menu ( remind la if yes )
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
//void UpdateInfo(){
////      Enter user IC: [IC],display {status}
////      setlocation : state: - , city: - ,display {status}
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

//  ADMIN
//  Update Stock-CYK
//      Enter brand: [brand]
//      ++stock if got order 
//      --stock when a user is vaccinated
//cout << "Enter Brand : ";
//cin >>
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
//Update User-SZR
//Enter patient ic 
//check ic(loop user text file)                                          
//if found ic                                                            
//     display{status}, user dose++, stock decreaseAmount       
//if not found ic, display: Patient doesnt exist,re-enter IC or exit admin menu
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
    //  TODO: Get VaccineCenter of Admin and decrement stock of that brand!
    VaccineCenter* vc = admin->getCenter();
    int amount = vc->checkVaccine(brand);
    cout<< "Vaccine left for brand " << brand <<" : "<< amount << endl;
    if(amount == 0){
        cout << "Inadequate stock. Please restock via update vaccine option first" << endl;
        system("pause");
        return;
    }
    vc->updateVaccine(brand,-1);

    //  TODO: Assign the firstCenter / secondCenter of User
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

    //  TODO: LOGIN ADMIN and PASSWORD
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