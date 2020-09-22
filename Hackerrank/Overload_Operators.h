#pragma once

#include <iostream>
#include <string>

using namespace std;


class Complex {
public:
	int a, b;

	void input(string);
};

void Complex::input(string str) {
	int i = 0;

	//	Sample str: "512+i1023"

	//	While it is still digits
	while (str[i] != '+') {
		this->a = this->a * 10 + str[i] - '0';
	}
	//	While it is + or i
	while (str[i] == '+' || str[i] == 'i')
		i++;
	//	All the last digits go into b
	while (i < str.length()) {
		this->b = this->b * 10 + str[i] - '0';
	}

}


//	The operator is not overloaded in the class itself. Here we are overloading the global operator function
//	Remember how overloading works? If the arguments match the datatype specified in the parameter list, it will use the
//	overloaded operator function instead of the usual, non overloaded function
Complex operator+ (const Complex& complex, const Complex& complex2) {
	Complex newComplx;
	newComplx.a = complex.a + complex2.a;
	newComplx.b = complex.b + complex2.b;
	return newComplx;
}

//	Insertion operator takes in the ostream object reference, and also the reference to object to insert (In this case the Complex)
//	object. Here we will just do it like usual, but at last step the ostream must be returneds
ostream& operator<< (ostream& os, const Complex& complex) {
	os << complex.a << "+i" << complex.b << endl;
	return os;
}