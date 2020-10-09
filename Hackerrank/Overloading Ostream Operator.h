#pragma once


#include <iostream>
#include <string>


class Person {
private:
	std::string first_name_;
	std::string last_name_;
public:
	Person(const std::string& first_name, const std::string& last_name)
		: first_name_(first_name), last_name_(last_name) {}
	const std::string& get_first_name() const {
		return first_name_;
	}
	const std::string& get_last_name() const {
		return last_name_;
	}
};

//	Note that the function for operator << is not declared inside class. Therefore we cannot overload << operator outside of class definition
//	What we can do however is overload the GLOBAL << Operator! It will always apply to the correct function
std::ostream& operator<< (std::ostream& os, const Person& obj) {
	os << "first_name=" << obj.get_first_name() << ",last_name=" << obj.get_last_name();
	return os;
}