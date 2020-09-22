#pragma once

#include <iostream>
#include <string>
#include <ostream>

using namespace std;

/*
	SOME NOTES ON THIS QUESTION:

	>	For constructor, we can use the COnstructor Initializer List syntax, which initializes the member variables
		with ease
	>	Note the copy Constructor, which takes in another instance of the same Class to initialize this object.
		Here in the parameter where the instance shall be passed in, we shall declare it as
			const class_name& identifier
		1.	We will be getting it in form of reference
		2.	The const keyword must be used there
	>	For the volume calculation, We shall cast one of the values beforehand to a wider type so it doesn't overflow 
		before we cast it during returning phase
	>	Note the overriding of operators. In C++ we can override functions and operators
		To override operators, we first declare the return type, then the name 'operator' followed by the operator sign
		Eg:		Box operator+ (const Box& anotherBox)

		Here the operator when used, will return a modified Box object or new Box object (depend on how the implementation)
		The + operator is overridden, and the parameter takes in a second Box object's reference
		(Note: If the overridding function is not declared as member function, we need to take in a second reference to
		 another Box object!)

	>	The overridding of stream buffer operators is more complicated
		
*/

class Box {
private:
	int l, b, h;

public:
	Box() : l(0), b(0), h(0) { }
	Box(int l, int b, int h) : l(l), b(b), h(h) { }
	Box(const Box& anotherBox) {
		l = anotherBox.l;
		b = anotherBox.b;
		h = anotherBox.h;
	}
	int getLength() {
		return l;
	}
	int getBreadth() {
		return b;
	}
	int getHeight() {
		return h;
	}
	long long CalculateVolume() {
		return (long long)l * b * h;
	}

	bool operator< (const Box& anotherBox) {
		bool isLLarger = this->l > anotherBox.l;
		bool isLEqual = this->l == anotherBox.l;
		bool isBLarger = this->b > anotherBox.b;
		bool isBEqual = this->b == anotherBox.b;
		bool isHLarger = this->h > anotherBox.h;

		return !(isLLarger || (isLEqual && isBLarger) ||
			(isLEqual && isBEqual && isHLarger));
	}

	friend ostream& operator<< (ostream& output, const Box& anotherBox) {
		output << anotherBox.l << " " << anotherBox.b << " " << anotherBox.h;
		return output;
	}
};