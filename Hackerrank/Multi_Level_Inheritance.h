#pragma once

#include <iostream>
#include <string>

using namespace std;


class Triangle {
public:
	Triangle() {}
	void triangle() {
		printf("I am an triangle\n");
	}
};

class Isosceles : public Triangle {
public:
	Isosceles() : Triangle() {}
	void isosceles() {
		cout << "I am an isosceles triangle\n";
	}
};

class Equilateral : public Isosceles {
public:
	Equilateral() : Isosceles() {}
	void equilateral() {
		cout << "I am an equilateral triangle\n";
	}
};

