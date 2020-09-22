#pragma once

#include <iostream>
#include <string>
#include <new>

using namespace std;

//http://www.cplusplus.com/doc/tutorial/dynamic/

/*
	In C++, memory allocation is done before the runtime of the program. Therefore especially for arrays,
	if we wait for the user input to determine the size of array, the program can't possibly know how much
	memory to allocate for the array!

	This is solved via dynamic memory allocation, which is done at runtime

	First we need to include the <new> header file
	
	Here we will have 2 keywords to use:
		>	new
		>	delete

	To allocate a new memory of single element, we will do like:
		
		int* myElem = new int;

	This will return the pointer to the element itself, which is stored in myElem pointer variable.
	Then we can access the variable now which is dynamically allocated during runtime

	As for arrays, similar syntax goes as follows:

		int* arr = new int[ sizeHere ];

	It will return the pointer to the first element of the array.
	Then we will be accessing the elements in usual way:

		cout << arr[1];		OR EVEN		cout << *(arr + 1);



	====================================================================================

	Memory allocation may be unsuccessful, especially when the memory is very limited. It will by default
	throw an exception if unsuccessful.
	However if we want it to not throw the exception and ruin the program, we can put a (nothrow) object
	from <new> header between the 'new' and your 'datatype'

		int* arr = new (nothrow) int[100];

	If allocation is unsuccessful, it will return a nullptr. Then, program continues as usual. We can
	detect the allocation status by checking if it is a null pointer or not

		if (arr == nullptr) { ...handle }

	======================================================================================

	Once the array or single element we allocated during runtime has done its purpose, we shall free its
	memory to prevent memory leak. This is done by 'delete' keyword

	To delete a dynamically allocated single element:
		delete elemPointer;

	To delete the dynamically allocated array:
		delete[] arrPointer;

*/


void arrayIntroduction() {

	int n;
	cin >> n;
	int* arr = new int[n];

	for (int i = 0; i < n; i++) {
		cin >> arr[i];
	}

	for (int i = n - 1; i >= 0; i--) {
		cout << arr[i];
	}
	delete[] arr;
}

