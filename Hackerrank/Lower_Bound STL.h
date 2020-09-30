#pragma once


#include <algorithm>
#include <vector>
#include <iostream>
#include <string>

/*
*	lower_bound is a convenient <algorithm> function
*	it takes in a begin() iterator (Iterator at head of a vector or data structures),
*		a end() iterator (Iterator at tail of a vector or data structures),
*		and the value to search for.
* 
*	The data structure must be sorted beforehand. Consider using std::sort or just use normal sorted set
* 
*	It will return a index which points to the LEAST ELEMENT GREATER THAN VAL.
* 
*		1,2,3,4,5. If we find 4, it will point to element 4. 
* 
*	We can use pointer arithmetic to find out index of the iterator returned:  it - begin()
*/


void lowerBoundSTL() {

	int N;
	std::cin >> N;

	std::vector<int> vec;
	vec.reserve(N);

	while (N-- > 0) {
		int n;
		std::cin >> n;
		vec.push_back(n);
	}

	std::cin >> N;

	while (N-- > 0) {
		int q;
		std::cin >> q;

		std::vector<int>::iterator it;
		it = std::lower_bound(vec.begin(), vec.end(), q);

		std::cout <<
			( (*it == q) ? "Yes " : "No " ) <<
			it - vec.begin() + 1 <<
			"\n";
	}

}