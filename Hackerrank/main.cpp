#include <iostream>
#include <string>

#include "Multi_Level_Inheritance.h"

using namespace std;

int main() {

	Triangle tri;
	tri.triangle();

	Isosceles iso;
	iso.triangle();
	iso.isosceles();

	Equilateral eq;
	eq.Triangle::triangle();
	eq.Isosceles::isosceles();
	eq.equilateral();
	
}