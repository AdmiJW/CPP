//Porgram 3.13
#include <iostream>
#include <iomanip>
using namespace std;

int* mkint();

int main() {
    
    cout << mkint() << endl;

    return 0;
}

int* mkint() {
    return new int;
}