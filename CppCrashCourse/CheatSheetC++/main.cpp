//Porgram 3.13
#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    cout << "\n\t   Multiplication Tables";
    cout << "\n..........................................\n\n";

    //  Pirnt multiplication table for 1 to 12
    for (int n = 1; n <= 2; n++) {
        for (int j = 1; j <= 10; j++) {
            cout << setw(4) << j * 1;
        }
        cout << endl;
    }
    cout << "\nEnd of Program";
    return 0;
}