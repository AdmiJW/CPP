#pragma once

#include <iostream>
#include <sstream>
#include <vector>
#include <string>


std::vector<int> parseInts(std::string str) {
	std::stringstream ss(str);
	std::vector<int> res;

	char c;
	int n;
	while (ss >> n) {
		res.push_back(n);

		if (!(ss >> c) ) {
			break;
		}
	}
	return res;
}