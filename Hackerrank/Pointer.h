#pragma once

#include <iostream>
#include <string>

using namespace std;


void update(int* a, int* b) {
	int temp = *a;
	(*a) = *a + *b;
	(*b) = temp - *b;
	(*b) = (*b) < 0 ? -*b : *b;

	//	Alternatively, use abs(temp - *b)
}


void pointer() {
	int a, b;

	scanf("%d\n%d", &a, &b);

	update(&a, &b);

	printf("%d\n%d", a, b);
}


