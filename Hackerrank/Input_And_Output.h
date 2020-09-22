#pragma once

#include <iostream>
#include <string>

using namespace std;


void inputAndOutput() {

	int nums[3];

	for (int i = 1; i <= 3; i++) {
		printf("Please enter your number #%d: ", i);
		cin >> nums[i - 1];
	}

	cout << "The sum of 3 numbers are: " << nums[0] + nums[1] + nums[2] << endl;

}