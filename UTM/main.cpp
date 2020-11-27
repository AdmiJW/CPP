
#include <iostream>
#include <string>

using namespace std;


int main() {
	int a = 4, b = 3, c = 5;

	int z = a + b * c-- % ++b;
	cout << z;
}