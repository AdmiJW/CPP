#pragma once

#include <iostream>
#include <string>

using namespace std;


class Triangle {
public:
	Triangle() {}
	void triangle() {
		cout << "I am a triangle\n";
	}
};

class Isosceles : public Triangle {
public:
	Isosceles() : Triangle() {}
	void isosceles() {
		cout << "I am an isosceles triangle\n";
	}
	void description() {
		cout << "In an isosceles triangle two sides are equal\n";
	}
};

void inheritance_Introduction() {
	Isosceles iso;
	iso.isosceles();
	iso.description();
	iso.triangle();
}