#include <iostream>
#include <string>
#include <cstring>
using namespace std;


int main() {
    string name("mtu students");
    string word1 = "Comp";
    string word2 = "Sci";
    string word3 = "Welcome, ";
    
    cout << *(word1.assign(name.substr(0, 3))).begin() << endl;
}