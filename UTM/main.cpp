
#include <iostream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;


int main() {
    int x = 5, y = 4, a = 18;
    float z = 3.5f;
    cout << x << " " << a << " " << y << " " << z << " \n";
    x *= x + z;
    cout << x << " " << a << " " << y << " " << z << " \n";
    y = z-- * y;
    cout << x << " " << a << " " << y << " " << z << " \n";
    z = ++y % (int)z;
    cout << x << " " << a << " " << y << " " << z << " \n";
    a += x / 4;
    cout << x << " " << a << " " << y << " " << z << " \n";
}