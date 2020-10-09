#pragma once


#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

void vector_sort() {

	int T, E;
	std::cin >> T;
	std::vector<int> vector;

	while (T-- > 0) {
		std::cin >> E;
		vector.push_back(E);
	}


	//	Sort is consisted in the <algorithm> header file
	std::sort(vector.begin(), vector.end() );

	for (int i = 0; i < vector.size(); i++) {
		std::cout << vector.at(i) << " ";
	}
	
}