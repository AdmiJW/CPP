#include <iostream>
#include <string>
#include <iomanip>
using namespace std;


int main() {

	string s = "So Hard!";

	cout << setw(20) << s << endl;

	cout << setfill('C') << s << endl;

}