#pragma once

#include <iostream>
#include <string>


enum class Fruit { apple, orange, pear };
enum class Color { red, green, orange };


template <typename T>
struct Traits;


template <>
struct Traits <Fruit> {
	static std::string valueNames[];
	static std::string name(int idx) {
		return (idx > 2 || idx < 0 ? "unknown" : valueNames[idx]);
	}
	
};




template <>
struct Traits <Color> {
	static std::string valueNames[];
	static std::string name(int idx) {
		return (idx > 2 || idx < 0 ? "unknown" : valueNames[idx]);
	}
};


std::string Traits<Fruit>::valueNames[3] = { "apple", "orange", "pear" };
std::string Traits<Color>::valueNames[3] = { "red", "green", "orange" };


int main() {

	int t;
	std::cin >> t;

	for (int i = 0; i < t; i++) {
		int idx1;
		std::cin >> idx1;
		int idx2;
		std::cin >> idx2;

		std::cout << Traits<Color>::name(idx1) << " ";
		std::cout << Traits<Fruit>::name(idx2) << std::endl;
	}

	return 0;
}