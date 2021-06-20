#ifndef PROJECT_H
#define PROJECT_H

#include <iostream>
#include <string>
using namespace std;

//=========================
//  VaccineBrand class
//=========================
class VaccineBrand {
private:
    string brand;
    int amount;
public:
    VaccineBrand();
    VaccineBrand(string, int);
    void displayInfo();
    string getBrand();
    void decreaseAmount(int);
    void increaseAmount(int);

    friend bool saveVaccineCenter();
    friend bool loadVaccineCenter();
};


//=========================
//  VaccineCentre class
//=========================
class VaccineCenter {
private:
    string centerName;
    string centerState;
    VaccineBrand brand[5];
public:
    VaccineCenter();
    VaccineCenter(string, string);
    string getName();
    string getState();
    void displayInfo();
    void updateVaccine(string, int);

    friend bool saveVaccineCenter();
    friend bool loadVaccineCenter();
};

//=========================
//  VaccineProfile class
//=========================
class VaccineProfile {
private:
    int numDose;
    VaccineCenter* firstCenter;
    VaccineCenter* secondCenter;
    string brand1, brand2;
public:
    VaccineProfile();
    void  setFirstCenter(VaccineCenter*, string);
    void  setSecondCenter(VaccineCenter*, string);
    void updateDose();
    int getDose();

    friend bool saveUsers();
    friend bool loadUsers();
    friend ostream& operator<<(ostream&, VaccineProfile&);
};

//=========================
//  Person class
//=========================
class Person {
protected:
    string full_name;
    int age;
    string ic;
public:
    Person();
    Person(string, int, string);
    virtual void displayInfo();
    friend ostream& operator<<(ostream&, Person&);
};


//=========================
//  User class
//=========================
class User :public Person {
    string district;
    string state;
    VaccineProfile v;
public:
    User();
    User(string, int, string);
    void displayInfo();
    void setLocation(string, string);
    VaccineProfile& getVaccineProfile();
    friend ostream& operator<<(ostream&, User&);
    friend bool saveUsers();
    friend bool loadUsers();
    friend User* getUser(string ic);
};

//=========================
//  Admin class
//=========================
class Admin :public Person {
    VaccineCenter* center;
    string password;
public:
    Admin();
    Admin(string, int, string, VaccineCenter*);
    void displayInfo();
    VaccineCenter* getCenter();
    friend ostream& operator<<(ostream&, Admin&);

    friend bool saveAdmins();
    friend bool loadAdmins();
    friend Admin* getAdmin(string);
    bool verifyPassword(string);
};
#endif
