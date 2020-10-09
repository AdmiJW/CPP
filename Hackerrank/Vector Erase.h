#pragma once

#include <iostream>
#include <string>
#include <vector>

void vector_erase() {

	int E;
	std::cin >> E;
	std::vector<int> vect;
	vect.reserve(E);

	while (E-- > 0) {
		int i;
		std::cin >> i;
		vect.push_back(i);
	}


	int d;
	std::cin >> d;

	vect.erase( vect.begin() + d - 1 );

	
	int b, e;
	std::cin >> b >> e;

	vect.erase(vect.begin() + b - 1, vect.begin() + e - 1);



	std::cout << vect.size() << "\n";
	for (std::vector<int>::const_iterator it = vect.begin(); it != vect.end(); it++) {
		std::cout << *it << " ";
	}
}


