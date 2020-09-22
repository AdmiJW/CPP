#pragma once

#include <cmath>
#include <vector>
#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;


class Matrix {
public:
	vector< vector<int> > a;

	Matrix operator+(Matrix& matrix2) {
		int n = a.size();
		int m = a[0].size();
		Matrix newMatrix;
		newMatrix.a.reserve(n);
		
		for (int i = 0; i < n; i++) {
			vector<int> row;
			row.reserve(m);
			for (int j = 0; j < m; j++) {
				row.push_back(this->a[i][j] + matrix2.a[i][j]);
			}
			newMatrix.a.push_back(row);
		}
		return newMatrix;
	}
};



int main() {
	int cases, k;
	cin >> cases;

	for (k = 0; k < cases; k++) {
		Matrix x;
		Matrix y;
		Matrix result;
		int n, m, i, j;		// n is the row, m is the column, i is the row index, j is the column index;
		cin >> n >> m;

		//	Construction of first matrix
		for (i = 0; i < n; i++) {
			vector<int> vec;
			int input;
			for (j = 0; j < m; j++) {
				cin >> input;
				vec.push_back(input);
			}
			x.a.push_back(vec);
		}

		//	Construction of second matrix
		for (i = 0; i < n; i++) {
			vector<int> vec;
			int input;
			for (j = 0; j < m; j++) {
				cin >> input;
				vec.push_back(input);
			}
			y.a.push_back(vec);
		}

		result = x + y;

		for (i = 0; i < n; i++) {
			for (j = 0; j < m; j++) {
				cout << result.a[i][j] << " ";
			}
			cout << endl;
		}
		return 0;
	}
}