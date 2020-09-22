#pragma once

#include <iostream>
#include <string>

using namespace std;

int sum_of_four(int a, int b, int c, int d) {
	return max(a, max(b, max(c, d) ) );
}

void functions() {
	int a, b, c, d;

	scanf("%d %d %d %d", &a, &b, &c, &d);

	int res = sum_of_four(a, b, c, d);

	printf("%d\n", res);

}
