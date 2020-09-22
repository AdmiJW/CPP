#pragma once

#include <iostream>
#include <string>

using namespace std;

//	Note: in printf with string (%s), it expects to accept a pointer to the first char of the string (char* ),
//		  not the entire string itself! 
//		  Therefore we shall pass in the string's first char pointer:
//				strToPassIn.c_str();
//				strToPassIn.data();


void basicDataTypes() {

	//	Int (%d), Long (%ld), Char (%c), Float (%f), Double (%lf)

	int myint;
	long mylong;
	char mychar;
	float myfloat;
	double mydouble;
	

	//	Using cin and cout ==============================================
	//	To set precision, first use cout.precision() and then include 'fixed' first before outputting value

	cin >> myint >> mylong >> mychar >> myfloat >> mydouble;

	cout << myint << "\n" << mylong << "\n" << mychar << "\n";
	cout.precision(3);
	cout << fixed << myfloat << endl;
	cout.precision(9);
	cout << fixed << mydouble << endl;

	/*
	*	Alternatively, i can use setprecision() as so:
	* 
	*	cout << fixed << setprecision(3) << myfloat << endl;
	* 
	*	then I won't need to use precision()
	*	All of those are in std namespace
	*/



	//	Using scanf and printf ===============================================
	//	Note the precision! %.3f, and %.9lf

	scanf("%d %ld %c %f %lf", &myint, &mylong, &mychar, &myfloat, &mydouble);

	printf("%d\n%ld\n%c\n%.3f\n%.9lf", myint, mylong, mychar, myfloat, mydouble);



}