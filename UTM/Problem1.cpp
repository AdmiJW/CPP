
#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <iomanip>
using namespace std;

/*
    INDIVIDUAL BATTLE
    SOH JUN WEI,    A20EC0151
*/
//  PROBLEM 1

int problem1() {
    string statenames[6] = { "Johor", "Selangor", "Perak", "Kedah",
                            "Pahang", "Melaka" };
    int occurrences[6] = {};

    for (int i = 0; i < 6; ++i) {
        cout << "Please enter number of accidents for " << statenames[i] << " : ";
        cin >> occurrences[i];
        if (occurrences[i] < 0) {
            cout << "Negative value is not allowed!\n";
            --i;
        }
    }

    cout << "\n";
    cout << "--------------------------------------------------\n";
    cout << "\tAUTOMOBILE ACCIDENTS 2019\t\t\n";
    cout << "--------------------------------------------------\n";
    cout << "\tStates\t\tNo Of Accidents\t\t\n";

    for (int i = 0; i < 6; ++i)
        cout << "\t" << statenames[i] << "     \t\t" << occurrences[i] << "\n";
    cout << "--------------------------------------------------\n";

    cout << "\n";

    int maxidx = 0, minidx = 0;
    for (int i = 1; i < 6; ++i) {
        if (occurrences[i] > occurrences[maxidx])
            maxidx = i;
        if (occurrences[i] < occurrences[minidx])
            minidx = i;
    }

    cout << statenames[maxidx] << " had the highest accidents with " << occurrences[maxidx] << "\n";
    cout << statenames[minidx] << " had the lowest accidents with " << occurrences[minidx];

    return 0;
}