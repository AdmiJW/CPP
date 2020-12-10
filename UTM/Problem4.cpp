
#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <iomanip>
#include <cctype>
using namespace std;

#define LONG long long int

/*
    INDIVIDUAL BATTLE
    SOH JUN WEI,    A20EC0151
*/

//  Take in character, return respective value (Eg: B => 11, C => 12)
int getVal(char c) {
    if (isdigit(c)) return c - '0';
    else return (c - 'A') + 10; //  A should map to 10, and so on.
}

//  Take in string and a base, convert to the respective decimal value
LONG convertBase(string s, int base) {
    const int len = s.size();
    LONG val = 0;

    for (int i = 0; i < len; i++) {
        val += getVal(s[i]) * pow(base, len - i - 1);
    }

    return val;
}

//  Finds the minimum base. For example, "12B",
//  Due to presence of B, base must at least 12.
int minimumBase(string s) {
    int max = 0;
    for (char c : s) {
        int val = getVal(c);
        max = fmax(max, val + 1);
    }
    return max;
}


void findPairs(string i, string j) {
    //  Brute force all base from minimum possible base to 36 for first integer
    for (int baseA = minimumBase(i); baseA <= 36; ++baseA) {
        LONG valA = convertBase(i, baseA);

        //  Brute force all base from minimum possible base to 36 for second integer
        for (int baseB = minimumBase(j); baseB <= 36; ++baseB) {
            LONG valB = convertBase(j, baseB);

            if (valA == valB) {
                cout << i << " (base " << baseA << ") = " <<
                    j << " (base " << baseB << ")\n";
                return;
            }

        }
    }
    cout << i << " is not equal to " << j << " in any base 2...36\n";
}



int problem4() {
    for (int N = 0; N < 5; ++N) {
        string i, j;
        cin >> i >> j;

        findPairs(i, j);
    }

    return 0;
}