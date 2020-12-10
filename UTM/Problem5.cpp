
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

bool exceedTwentyOne(vector<char>& arr) {
    int sum = 0;
    for (char c : arr) {
        if (c == 'J' || c == 'Q' || c == 'K') sum += 10;
        else if (c == 'A') sum += 1;
        else sum += c - '0';    //  Use ASCII code to convert value
    }
    return sum > 21;
}

int problem5() {
    int N;
    cout << "How many cards do you have? ";
    cin >> N;

    vector<char> arr;

    cout << "\n";

    for (int i = 0; i < N; ++i) {
        cout << "Enter the your #" << i + 1 << " card value: ";
        string s;
        cin >> s;

        if (!s.compare("10")) arr.push_back('J');   //Change 10 to J easier
        else arr.push_back(s[0]);
    }

    cout << "\n" << (exceedTwentyOne(arr) ? "True" : "False");

    return 0;
}