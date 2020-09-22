#pragma once

#include <iostream>
#include <string>


class Person {
protected:
    std::string name;
    int age;
    int cur_id;
public:
    Person(int id) : cur_id(id) {}
    virtual void getdata() = 0;
    virtual void putdata() = 0;
    virtual ~Person() {}
};


class Student : public Person {
    int marks[6] = { 0 };

    static int next_id;
public:
    Student() : Person(next_id++) { }
    ~Student() {}
    void getdata() {
        std::cin >> this->name;
        std::cin >> this->age;
        for (int i = 0; i < 6; i++) {
            std::cin >> this->marks[i];
        }
    }
    void putdata() {
        std::cout << this->name << " ";
        std::cout << this->age << " ";
        int sum = 0;
        for (int i = 0; i < 6; i++) {
            sum += this->marks[i];
        }
        std::cout << sum << " ";
        std::cout << this->cur_id << '\n';
    }
};


class Professor : public Person {
    int publications;

    static int next_id;
public:
    Professor() : Person(next_id++) {}
    ~Professor() {}
    void getdata() {
        std::cin >> this->name;
        std::cin >> this->age;
        std::cin >> this->publications;
    }

    void putdata() {
        std::cout << this->name << " ";
        std::cout << this->age << " ";
        std::cout << this->publications << " ";
        std::cout << this->cur_id << "\n";
    }

};

int Student::next_id = 1;
int Professor::next_id = 1;