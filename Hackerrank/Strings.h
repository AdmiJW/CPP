#pragma once

#include <iostream>
#include <string>

using namespace std;

/*
	scanf won't really work with strings, unless it is a char[] type.
	
	printf only takes in char pointer which points to the string's starting char. Therefore we have to use
	string.data() or string.c_str();
*/

void strings() {

	string a, b;
	cin >> a;
	cin >> b;
	string c = a + b;

	printf("%d %d\n", a.length(), b.size());

	printf("%s\n", c );
	
	char temp = a[0];
	a[0] = b[0];
	b[0] = temp;

	printf("%s %s", a.data(), b.c_str() );


}
