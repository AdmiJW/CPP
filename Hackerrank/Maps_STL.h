#pragma once

#include <iostream>
#include <map>
#include <string>


void maps_STL() {

	int Q;
	std::cin >> Q;
	std::map <std::string, int> map;

	int t, mark;
	std::string name;
	std::pair< std::map<std::string, int>::iterator, bool > iter;

	while (Q-- > 0) {
		std::cin >> t >> name;

		switch (t) {
		case 1:
			std::cin >> mark;

			//	map[name] = mark;		//	Insertion using [] operator

			//	map.insert( std::pair<std::string, int>(name, mark) );		//	Insertion using insert() with a pair object passed in

			//	Insertion using insert() along with special function (std::make_pair) which doesn't require specifying the template
			//	type.
			//	Notice that insert() operation will return a pair object. the pair's first is the newly inserted element or the
			//	unmodified existing element, and the second is a boolean value indicating if the insertion of new element
			//	is successful. (If key already exist, insert() will be fail )
			iter = map.insert(std::make_pair(name, 0) );		//	If not exist, insert new element with value 0
			iter.first->second += mark;					//	Now only we add the mark into the value

			break;


		case 2:
			map.erase(name);			//	Delete elements by key
			break;


		case 3:
			std::map<std::string, int>::iterator it = map.find(name);

			//	If find fails, it will return map.end()
			if (it == map.end()) {
				std::cout << 0 << "\n";
			}
			std::cout << it->second << "\n";		//	Remember the returned value (pointed by pointer) is a pair object
													//	Access the key using pair.first and value using pair.second
			break;


			//	Access eleemnt using [] operator, or at() <- throws exception!

			//	int& i = map[name];		//	If it don't exist in map, it will insert with default value
			//	std::cout << i << "\n";
		}
	}


}