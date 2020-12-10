
#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <iomanip>
#include <cctype>
using namespace std;

/*
    INDIVIDUAL BATTLE
    SOH JUN WEI,    A20EC0151
*/

//  Problem 2

bool isSpecial(char c) {
    c = tolower(c);
    return c == 'l' || c == 'm' || c == 'n' || c == 'p';
}
string convert(string s) {
    return s.substr(1) + s[0] + (isSpecial(s[0]) ? "ais" : "ay");
}

int problem2() {
    string str[5] = { };

    for (int i = 0; i < 5; ++i) {
        cout << "Enter a string: : ";
        getline(cin, str[i]);
    }

    cout << "\n";
    cout << "----------------------------------------------------------------\n";
    cout << "\tPIG LATIN CONVERSION\t\t\n";
    cout << "----------------------------------------------------------------\n";
    cout << "Before Convertion\t\t\tAfter Conversation\n";
    cout << "----------------------------------------------------------------\n";
    for (int i = 0; i < 5; ++i) {
        cout << left << setw(30) << str[i] << setw(30) << convert(str[i]) << "\n";
    }

    cout << "----------------------------------------------------------------\n";

    return 0;
}