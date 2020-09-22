#pragma once

#include <iostream>
#include <string>

using namespace std;

/*
	An 2D array is basically an array of pointers, each pointer points to another array by itself

	Therefore we will create the array of pointers as so:

		int** myArray = new int*[n];

	Each 'row' can be of different length arrays. Therefore we do as such:

		for (int i = 0; i < n; i ++ ) {
			myArray[i] = new int[k];

			//	Then the normal loop here to fill your arrays
		}

	An easier way to do such would be using <vector> header.

	To cleanup (Deallocate memory), we need to clean each individual array in the outer array, then the outer
	array itself

		for (int i = 0; i < n; i++ ) {
			delete[] myArray[i];
		}
		delete[] myArray;

*/


void variableSizedArrays() {
	int n, q;			//	n is the number of arrays, and q is number of queries
	scanf("%d %d", &n, &q);

	int** arrays = new int*[n];

	for (int i = 0; i < n; i++) {
		int k;		//	k is the number of elements in this particular array
		scanf("%d", &k);
		arrays[i] = new int[k];

		for (int j = 0; j < k; j++) {
			int element;
			scanf("%d", &element);
			arrays[i][j] = element;
		}
	}

	for (int i = 0; i < q; i++) {
		int a, b;
		scanf("%d %d", &a, &b);
		printf("%d", arrays[a][b]);
	}



	//	Removing array; Cleanup
	for (int i = 0; i < n; i++) {
		delete[] arrays[i];
	}
	delete[] arrays;
	
}
