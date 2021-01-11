
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <fstream>
using namespace std;

int main() {
	ifstream in("input.txt");

	for (int i = 0; i < 10; ++i) {
		int s;		
		in >> s;		//	In never gets extracted. S keep the original value
		cout << s;
	}
}