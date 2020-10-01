#pragma once


#include <iostream>
#include <set>
#include <string>


void Sets_STL() {

	std::set<int> myset;

	int Q;
	std::cin >> Q;

	while (Q-- > 0) {
		int t, x;
		std::cin >> t >> x;

		if (t == 1) {
			myset.insert(x);
		}
		else if (t == 2) {
			myset.erase(x);
		}
		else {
			std::set<int>::iterator it = myset.find(x);
			std::cout << (it == myset.end() ? "No" : "Yes") << "\n";
		}
	}

}