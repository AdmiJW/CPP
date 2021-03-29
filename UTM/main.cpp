#include <iostream>
using namespace std;


class Rectangle {
protected:
	int length;
	int width;
	int area;
public:
	int getWidth();
	int getLen();
	void setWidth(int);
	void setLen(int);
};

int Rectangle::getWidth() {
	return width;
}
int Rectangle::getLen() {
	return length;
}
void Rectangle::setWidth(int width) {
	this->width = width;
}
void Rectangle::setLen(int len) {
	length = len;
}


int main() {

	

}