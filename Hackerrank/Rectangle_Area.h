#pragma once


#include <iostream>
#include <string>

using namespace std;

class Rectangle {
protected:
	int width, height;
public:
	Rectangle() {}
	Rectangle(int width, int height) : width(width), height(height) {}
	void display() {
		printf("%d %d\n", this->width, this->height);
	}
};

class RectangleArea : public Rectangle {
public:
	RectangleArea() {}
	RectangleArea(int width, int height) : Rectangle(width, height) {}
	void read_input() {
		cin >> this->width >> this->height;
	}
	void display() {
		printf("%d\n", this->width * this->height);
	}
};





