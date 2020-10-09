#pragma once

#include <exception>
#include <iostream>
#include <string>
#include <sstream>



// When out of the what() scope, the C string will get destructed. Therefore we keep a String object in the class so that the
//	pointer don't go away
class BadLengthException : public std::exception {
public:
	std::string s;
	BadLengthException(int n) : std::exception(), s(std::to_string(n) ) {}

	
	virtual const char* what () const throw() {
		return s.c_str();
	}
};



bool checkUsername(std::string& name) {
	int len = name.length();

	if (len < 5) throw BadLengthException(len);

	for (int i = 0; i < len - 1; i++) {
		if (name[i] == 'w' && name[i + 1] == 'w') {
			return false;
		}
	}
	return true;
}



void inherited_code() {
	std::string name;
	int T;
	std::cin >> T;


	while (T-- > 0) {
		std::cin >> name;

		try {
			bool isValid = checkUsername(name);
			if (isValid) {
				std::cout << "Valid" << "\n";
			}
			else {
				std::cout << "Invalid" << "\n";
			}
		}
		catch (BadLengthException e) {
			std::cout << "Too short: " << e.what() << "\n";
		}
	}
}