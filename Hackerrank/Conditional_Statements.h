#pragma once

#include <iostream>
#include <string>

using namespace std;

/*
	Either use if else if else if statements, which is quite tedious
	Or use a function, along with a switch statement (Like below)
	Or even use an array to store the english words, since its index can be representing the numbers
*/
string getWord(int num) {
	switch (num) {
		case 1: return "one";
		case 2: return "two";
		case 3: return "three";
		case 4: return "four";
		case 5: return "five";
		case 6:	return "six";
		case 7: return "seven";
		case 8:	return "eight";
		case 9: return "nine";
		default: return "error";
	}
}


void conditionalStatements() {

	int n;

	if (n < 10)
		cout << getWord(n) << endl;
	else
		cout << "Greater than 9" << endl;
}