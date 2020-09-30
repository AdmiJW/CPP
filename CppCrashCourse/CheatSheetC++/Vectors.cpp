#include <iostream>
#include <string>
#include <vector>

using namespace std;


/*
*	STL is Standard Template Library, which are a library filled with 'containers', which is often used in data structures.
*	Those classes are templated, meaning we are the one to decide what datatype will go into those containers
* 
*	The best representative of STL is the 'vector' class, which is in the std namespace
*			std::vector
*	which is just a set, that don't enforce dupplicates, and ordering is important. (ArrayList equivalent)
* 
*	To use vector, include its header file <vector>
* 
*	Let's see how to use a vector:
*/


/*
*	CONSTRUCTORS
* 
*	>	empty (Default constructor)
*	>	fill  ( n, val)							- Initialize the vector with n elements, each with element value of val
*	>	range ( iteratorFrom, iteratorTo )		- Constructor will iterate through the iterator until the iteratorTo, which is
*												  exclusive. Then fills the vector with copies of the elements in the iterator's
*												  range
*	>	copy ( vector& )					    - Simply takes in another vector and copy all contents
*	>	move
*	>	initializer_list
*/

void printArr( vector<int>& arr) {
	for (vector<int>::iterator it = arr.begin(); it != arr.end(); it++) {
		cout << " " << *it;
	}
}



void V_constructor() {

	vector<int> arr1;		//	Default constructor. Now vector has nothing inside

	vector<int> arr2(5, 69);	//	Fill constructor. Now vector has 5 elements valued 69 inside

	cout << "Arr2: ";
	printArr(arr2);
	cout << endl;

	vector<int> arr3(arr2.begin(), arr2.end());	//	Range constructor. Iterates through the iterator until end is met, copying
												//	elements from it and fill it in

	cout << "Arr3: ";
	printArr(arr3);
	cout << endl;

	int copy[] = { 2,4,6,8,10 };
	vector<int> arr4(copy, copy + sizeof(copy) / sizeof(int) );	//	Range constructor, but work on static arrays instead

	cout << "Arr4: ";
	printArr(arr4);
	cout << endl;

}


















/*
*	ITERATORS
* 
*	Iterator is a type defined inside the vector itself. Like 
		std::vector<int>::iterator
		std::vector<int>::reverse_iterator
		std::vector<int>::const_iterator
		std::vector<int>::const_reverse_iterator
* 
*	>	begin()				-Iterator pointed to first element
*	>	end()				-Iterator pointed to last element + 1
*	>	rbegin()			-Iterator pointed to last element. Incrementing will make it go backwards
*	>	rend()				-Iterator pointed to first element - 1
* 
*	>	cbegin()			-Same as begin(), but cannot use this iterator to modify the value
*	>	cend()				-Same as end(), but cannot use this iterator to modify the value
*	>	crbegin()			-Same as rbegin(), but cannot use this iterator to modify the value
*	>	crend()				-Same as rend(), but cannot use this iterator to modify the value
* 
*/

void V_iterators() {

	int arr[] = { 2,4,6,8,10 };
	vector<int> vect(arr, arr + 5);	//	Range constructor

	cout << "Iterating using iterator: ";
	for (vector<int>::iterator it = vect.begin(); it != vect.end(); it++) {
		cout << " " << *it;
	}
	cout << endl;

	cout << "Iterating in reverse using reverse_iterator: ";
	for (vector<int>::reverse_iterator it = vect.rbegin(); it != vect.rend(); it++) {
		cout << " " << *it;
	}
	cout << endl;
}














/*
*	CAPACITY
* 
*	>	size()								- Number of elements in the vector
*	>	max_size()							- How many elements theoretically can this vector store
*	>	resize(n)							- Resizes the vector (not capacity!). If n is smaller, will delete until front n
*		resize(n, val)						  elements. If larger, will append with default values (Unless optional argument
*											  val is given, then it pads with the val)
*	
*	>	capacity()							- Current capacity of the vector
*	>	empty()								- Equivalent to isEmpty() in Java. Returns boolean value
*	>	reserve(n)							- Reserves the vector's capacity to be able to fit n elements
*	>	shrink_to_fit()						- Shrinks the capacity of vector to fit the size (current number of elements)
*/


void V_capacity() {

	int arr[] = { 2,4,6,8,10 };
	vector<int> vec;

	cout << "Is Empty: " << vec.empty() << endl;
	cout << "Capacity: " << vec.capacity() << endl;
	cout << "Max Size: " << vec.max_size() << endl;

	vec.reserve(10);		//	Will set the capacity to 10

	vec.assign(arr, arr + 5);
	
	cout << "Size: " << vec.size() << endl;
	cout << "Capacity: " << vec.capacity() << endl;

	vec.shrink_to_fit();

	cout << "Capacity: " << vec.capacity() << endl;
}

















/*
*	ACCESS
*
*	>	[n]					- Returns reference to the n'th element
*	>	at(n)				- Returns reference to the n'th element, but will check for out of bound error
*	>	front()				- Returns the first element. It returns the REFERENCE, unlike begin() which returns iterator
*	>	back()				- Returns the last element. It returns the REFERENCE, unlike end() which returns iterator
*	>	data()				- Returns the pointer to the first element of the ACTUAL ARRAY used by vector to store data
*							  We can use it like normal array pointer
*/

void V_access() {

	int arr[] = { 2,4,6,8,10 };

	vector<int> vec(arr, arr + 5);

	cout << vec[2] << endl;			// 6

	cout << vec.at(3) << endl;		 //	8
	
	try {
		cout << vec.at(5) << endl;		// Out of bounds exception
	}
	catch (...) {
		cout << "You tried to access out of bound element" << endl;
	}

	// Since it is the reference that gets returned, don't need to dereference it
	cout << "First element: " << vec.front() << endl;
	cout << "Last element: " << vec.back() << endl;

	//	Gets the pointer to the first element of the actual array
	int* pt = vec.data();
	while ( *pt != '\0') {
		cout << *(pt++) << endl;
	}

}






















/*
*	MODIFIERS
* 
*	To manipulate elements in the vector, do it through the pointer (iterator), by using at() or [] notation
*	
* 
*	>	assign												- Destroys all previous elements, fill it with this assign() new							
*															- elements. Kind of like constructor
*		-	range --> assign(iteratorFrom, iteratorTo)			
*		-	fill  --> assign(n, val)
*		-	initializer_list
* 
*	>	push_back(val)										- Adds a new element at the tail of the vector
*	>	pop_back()											- Removes the element at the tail of vector. WILL NOT RETURN
*															  ANYTHING
*	>	insert												- Inserts an element or a range of elements BEFORE the specified
*															  position (Using iterator)
*		-	single --> insert(position, val)
*		-	fill   --> insert(position, n, val)	
*		-	range  --> insert(position, iteratorFrom, iteratorTo)
* 
*	>	erase												- Removes an element, especially from middle of vector
*		
*		-	single --> erase(position)
*		-	range  --> erase(iteratorFrom, iteratorTo)
* 
*	>	swap( vector& )										- Swap contents with another vector
* 
*	>	clear()												- Delete all elements, essentially setting size to 0
*	>	emplace(pos, args)									- Creates the object element in place, using the arguments passed in as
*															  constructor argument of the object
*	>	emplace_back( args )								- Creates the object element in place at the tail of vector, using the
*															  arguments passed in as constructor argument of the object
*		
*		
*/


void V_modifiers() {

	vector<int> vec;

	int arr[] = { 2,4,6 };
	vec.assign(arr, arr + 3);
	printArr(vec);
	cout << endl;

	//	Append a value 8 to tail of vector
	vec.push_back(8);
	printArr(vec);
	cout << endl;

	//	Remove the value 8 from tail of vector
	vec.pop_back();
	printArr(vec);
	cout << endl;

	//	Insert three '5' before the 3th element (6)
	vec.insert( vec.begin() + 2, 3, 5);
	printArr(vec);
	cout << endl;

	//	Erase the 5th element, which shall be 5
	vec.erase(vec.begin() + 4);
	printArr(vec);
	cout << endl;

	vec.clear();
	printArr(vec);
	cout << endl;


}