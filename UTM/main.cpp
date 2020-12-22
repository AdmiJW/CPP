
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

void foo(int* arr) {
	cout << arr;
}



int main() {

	int arr[2][10] = { {2,3} };
	for (auto a : arr) {
		for (int i = 0; i < 10; i++) {
			cout << a[i] << endl;
		}
	}
}

