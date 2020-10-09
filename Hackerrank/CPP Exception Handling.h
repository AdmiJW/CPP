#pragma once

#include <iostream>
#include <string>


int largest_proper_divisor(int& n) {
	if (n == 0) {
		throw std::invalid_argument("largest proper divisor is not defined for n=0");
	} 
	if (n == 1) {
		throw std::invalid_argument("largest proper divisor is not defined for n=1");
	}
	for (int i = n / 2; i >= 1; i--) {
		if (n % i == 0)
			return i;
	}
	return -1;
}

void process_input(int& n) {
	int d;
	try {
		d = largest_proper_divisor(n);
		std::cout << "result=" << d << "\n";
	}
	// REMEMBER WHEN CATCHING EXCEPTIONS, USE THE REFERENCE, NOT COPY CONSTRUCTOR SO VIRTUAL FUNCTION what() WORK!
	catch ( std::exception& e ) {
		std::cout << e.what() << "\n";
	}
	std::cout << "Returning control flow to caller" << "\n";
}


void cpp_exception_handling() {
	int n;
	std::cin >> n;
	process_input(n);
}