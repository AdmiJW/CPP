#include<iostream>
#include<string>
using namespace std;

class Car {
    string model;
    string manufacture;
public:
    Car() {};
    Car(string m, string mft);
    void displayCarInfo() {
        cout << "Car model is: " << model << endl << "Manufactured by: " << manufacture << endl << endl;
    }
    ~Car() {
        cout << "Car destroyed" << endl;
    }

};

Car::Car(string cm, string cmft) {
    model = cm;
    manufacture = cmft;
    cout << "Car is created" << endl;
}

class Person {
    long long int ID;
    string name;
    Car pCar;
public:
    Person(long long int i, string n, Car c) {
        ID = i;
        name = n;
        pCar = c;
        cout << "Person is created" << endl;
    }
    ~Person() {
        cout << "Person destroyed" << endl;
    }
    void displayPersonInfo() {
        cout << "Person ID is: " << ID << endl << "Name is: " << name << endl << "Car model is: ";
        pCar.displayCarInfo();
    }
};


int main() {
    Car first("Mustang", "Ford");
    Person person_one(210505051147, "ArigatoMeow", first);
    person_one.displayPersonInfo();
}