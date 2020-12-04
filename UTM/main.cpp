
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>

using namespace std;

void show(int = 100);

int main() {
    show();
}

void show(int n = 100) {
    cout << n;
}