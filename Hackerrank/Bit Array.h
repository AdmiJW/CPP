#pragma once

#include <iostream>
#include <unordered_set>
#include <cmath>

typedef unsigned long long int ULONG;

int main() {
	
	ULONG modulo = static_cast<ULONG>( pow(2, 31) );

	ULONG N, S, P, Q;
	std::cin >> N >> S >> P >> Q;

	ULONG slow = S % modulo;
	ULONG fast = slow;
	int slowdist = 0;

	//	Why slowdist starts at 0? Actually slowdist shall not start with 0. However, when the slow and fast collides,
	//	The slowdist is incremented, then only the conditional check is performed once more. Therefore starting at 0
	//	fits just right
	do {
		slow = (slow * P + Q) % modulo;

		fast = ( (fast * P + Q) % modulo * 1l * P + Q) % modulo;

		slowdist++;
		
		if (slowdist >= N) {
			std::cout << slowdist << std::endl;
			return 0;
		}
	} while ( slow != fast );

	int straightdist = 0;
	slow = S % modulo;

	while (slow != fast) {
		straightdist++;
		slow = (slow * P + Q) % modulo;
		fast = (fast * P + Q) % modulo;
	}

	//	Now both slow and fast are at beginning of cycle. Set the fast pt t be one ahead of the beginning of cycle, and make it
	//	iterate one full cycle to determine the length of the cycle
	fast = (slow * P + Q) % modulo;
	
	int l = 0;

	while (slow != fast) {
		fast = (slow * P + Q) % modulo;
		l++;
	}

	std::cout << l + straightdist << std::endl;
	return 0;
}