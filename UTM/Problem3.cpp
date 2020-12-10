
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


int problem3() {
    int N;
    cout << "Please input a row number: ";
    cin >> N;

    vector< vector<int> > grid(N, vector<int>(N, 0));

    //  Row loop
    for (int i = 0; i < N; ++i) {
        grid[i][0] = 1;
        grid[i][i] = 1;
        //  Column Loop, don't do the first and last element
        //  The element is sum of last row's 2 element
        for (int j = 1; j < i; ++j) {
            grid[i][j] = grid[i - 1][j] + grid[i - 1][j - 1];
        }
    }

    //  Printing
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j <= i; ++j) {
            cout << left << setw(6) << grid[i][j];
        }
        cout << "\n\n";
    }

    //  Query
    cout << "Please input a row and a position along the row: ";
    int R, C;
    cin >> R >> C;

    //  Invalid if row is over possible row numbers, or column is larger or equal to row
    if (R > N || C > R)
        cout << "invalid row and column position!" << "\n";
    else
        cout << "Value at row " << R << " and position " << C << " is " << grid[R - 1][C - 1];

    return 0;
}