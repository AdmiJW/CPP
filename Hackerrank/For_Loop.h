#pragma once

#include <iostream>
#include <string>

using namespace std;

//	Note: in printf with string (%s), it expects to accept a pointer to the first char of the string (char* ),
//		  not the entire string itself! 
//		  Therefore we shall pass in the string's first char pointer:
//				strToPassIn.c_str();
//				strToPassIn.data();

void forLoop() {

	int start, end;
	scanf("%d\n%d", &start, &end);

	string words[] = { "one", "two", "three", "four", "five", "six", "seven", "eight", "nine" };

	for (int i = start; i <= end; i++) {
		if (i < 10) {
			printf("%s\n", words[i-1].c_str() );
		}
		else if (i % 2 == 0)
			printf("even\n");
		else
			printf("odd\n");
	}

}