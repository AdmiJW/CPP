#pragma once

#include <iostream>
#include <string>
#include <sstream>

using namespace std;


class Student {
private:
	int age;
	int standard;
	string first_name;
	string last_name;
public:
	int get_age() { return age; }
	string get_first_name() { return first_name; }
	string get_last_name() { return last_name; }
	int get_standard() { return standard; }

	void set_age(int age) {
		this->age = age;
	}
	void set_first_name(string firstName) {
		this->first_name = firstName;
	}
	void set_last_name(string lastName) {
		this->last_name = lastName;
	}
	void set_standard(int standard) {
		this->standard = standard;
	}

	string to_string() {
		stringstream ss;
		ss << age << ',' << first_name << ',' << last_name << ',' << standard;
		return ss.str();
	}
};

void _class() {
	int age, standard;
	string first_name, last_name;

	cin >> age >> first_name >> last_name >> standard;

	Student stud;
	stud.set_age(age);
	stud.set_first_name(first_name);
	stud.set_last_name(last_name);
	stud.set_standard(standard);

	printf("%d \n%s, %s \n%d \n\n%s",
		stud.get_age(), stud.get_last_name().c_str(), stud.get_first_name().data(),
		stud.get_standard(), stud.to_string().c_str());
}