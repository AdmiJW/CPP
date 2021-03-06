#include <iostream> 
#include <string>
#include <cstdlib>
#include <time.h>
using namespace std;

//=====================================================================
//	Function declarations and its definitions ==========================
//=======================================================================
void greetings();


void greetings() {
	cout << "HELOWOLRD" << endl;
}


//	Takes in an int pointer type parameter
void incrementNum(int* numToMutate);

void incrementNum(int* numToMutate) {
	cout << "Mutated from " << numToMutate << " to " << (*numToMutate)++ << endl;
	//	Here we will dereference the pointer, and increment to it (mutate)
}




/* =======================
*		FUNCTIONS
* =======================
*
*	We've already seen a function --- The main() function
*	Function declarations are very similar to Java, syntax is:
*
*		return-type identifier ( parameters )
*
*	Making a function is split into 2 parts:
*		>	Declaration of fucntion
*		>	Definition of function
*
*	The declaration of function is simply to tell compiler that this function exists, and we will need to use it later
*	We declare a function above the main() function, same syntax as above, but no code block inside it, just end with semicolon
*
*	We define a function with the same syntax as above, but this time we define the statements we want to
*	execute inside the curly braces
*
*
*
*			function declaration		void myFunc( int param1 );
*
*			main()						int main() { code here... }
*
*			function definition			void myFunc ( int param1 ) { code here... }
*
*/


void C2_functions() {
	greetings();
	cout << endl;
}















/* =======================
*	FUNCTION PARAM & OVERLOADING
* =======================
*
*	C++ supports default parameters. We set that like some languages, using equal sign!
*
*	Function can be overloaded as well. Multiple functions can have the same identifier
*	as long as the parameters are not identical
*
*/

//	DEMO OF DEFAULT PARAMETERS
int addToIt(int n, int increment = 1) {
	return n + increment;
}

//	DEMO OF OVERLOADING FUNCTIONS

//	To use variable length arguments, you need to include header of stdarg.h
#include <stdarg.h>
double average(int nArgs, ...) {

	va_list arguments;	//	Define a type of va_list, which is a macro
	int sum = 0;

	va_start(arguments , nArgs);	//	Initialize the variable length argument with va_start macro.
									//	First argument is the va_list, second argument is the length of variable
									//	length argument

	for (int i = 0; i < nArgs; i++) {
		sum += va_arg(arguments, int);	//	Use of va_arg to access arguments. Take in the list, and second argument
	}									//	is the type. It works like iterator, retuning the next argument

	va_end(arguments);			//	Clean the memory

	return static_cast<double>(sum) / nArgs;
}

double average(int* arr) {
	int sum = 0;
	int count = 0;
	
	while (*arr != '\0') {
		sum += *arr;
		count++;
		arr++;
	}

	return static_cast<double>(sum) / count;
}








/* =======================
*	STACK AND HEAP MEMORY
* =======================
*
*	In our program, datas can take up static memory or dynamic memory
*	Those static ones are the datas whose space are determined by the programmer. Such as int a = 5; or
*	int b[] = {1,2,3,4,5};
*	In other words, the compiler knows that how much exact space the data is going to take up before
*	the program is going to be executed
*
*	The other one is the dynamic memory datas. Those data only know how much memory to take up
*	during program execution, through user inputs and some other dynamic factors
*	For example, we ask for user to enter the size to allocate for an array.
*	In other words, the compiler don't know how much exact space the data is going to take, until the
*	program executes
*
*	Those variables and datas that take up static memory, will be stored in STACK MEMORY. Remember, the stack
*	follows LIFO order. During compilation, the compiler kind of stack those data on the Stack. When
*	the program executes until a certain point (Eg: a function has returned), then the variables and functions
*	are going to get 'popped' from the stack.
*	This also means that we don't have to manage those stuff in stack memory. The data will eventually pop itself
*	when it is done being used
*
*	HEAP memory on the other hand, stores dynamic memory data. Heap kind of means messy, pile of stuff.
*	It is a pool of memory made available to be used by those dynamic memory datas.
*	When we need to allocate some space for the dynamic memory data, it kind of randomly get thrown into
*	the heap memory (random spaces), and thus is less efficient for accessing.
*
*	Since of the way heap memory works, we will have to usually deal with POINTERS when dealing with
*	dynamic memory data.
*	Also, C++ don't have the garbage collector like in Java and other languages. Therefore the program don't
*	know when we've done using the data and shall be discarded. The discarding and freeing the memory part
*	needs to be done by the programmer itself, otherwise it will lead to memory leak, where memory is only
*	freed when the program ends.
*
*	In C++, we allocate for dynamic memory using 'new' keyword. It will return the pointer to the start of the
*	allocated heap memory.
*	To free up the allocated memory on the other hand, use 'delete' keyword. See:
*
*
*/


void CS2_stackAndHeapMemory() {
	int size;
	cout << "Enter your size of array!" << "\n";
	cin >> size;

	int* arr = new int[size];

	for (int i = 0; i < sizeof(arr) / sizeof(int); i++) {
		cout << "Enter your array element #" << (i + 1) << ": ";
		cin >> arr[i];
	}
	for (int i = 0; i < sizeof(arr) / sizeof(int); i++) {
		cout << "Element at index #" << i << " is: " << arr[i] << "\n";
	}

	delete[] arr;


}












/* =======================
*		REFERENCES
* =======================
*
*	A reference variable is a referecne to an existing variable. When we access the value of the
*	reference variable, we are actually accessing the original variable!
*
*	Therefore, C++ allows us to manipulate data in computer memory, which is more performance!
*
*	Reference variable is created using ampersand character & before the identifier name.
*
*	Apart from that, ampersand sign & can be also used to return the reference of a variable itself
*
*/


void CS2_references() {
	string food = "pizza";
	string& ref = food;

	cout << "Original: " << food << endl;
	cout << "Reference: " << ref << endl;

	ref = "spaghetti";

	cout << "Original: " << food << endl;
	cout << "Reference: " << ref << endl;
	cout << endl;
}






















/* =======================
*		POINTERS
* =======================
*
*	A variable by itself, is a container storing a value
*	A pointer, is a ADDRESS variable, storing the address of a memory, which contains the data of the variable.
*
*	The difference between reference variable and pointer variable is,
*	>	Pointers store directly the address of the variable
*	>	References store as well address of the variable, but we can use it like using the original variable itself
*
*	>	When we cout pointers, we get address. When we cout references, it will be original value instead
*	>	We don't need dereference references, but we need to dereference pointers before using
*
*
*
*	>	An int variable stores an integer value
*	>	A int pointer will store the address of an integer variable
*
*
*	There are 2 operators associated with pointers:
*	>	&			to get the memory address of variable instead of the variable value itself
*	>	*		-	Use before a variable identifier, meaning to dereference it. (To find the actual data)
*				-	Use after a variable identifier, meaning that this will be a type that receives pointer, not only variable itself
*
*	Eg:
*				int var = 12345;
*				int* address;				// This is a int pointer type. Will take in address which points to int variable
*				address = &var				// If & was used, it will return the address of variable, not the value
*				cout << *address << endl;	// Since * was used to dereference, it will return variable value instead of address
*
*/


void CS2_pointers() {
	int var = 12345;
	int* address;
	address = &var;

	cout << "Variable: " << var << endl;
	cout << "Variable Address: " << &var << endl;
	cout << "Address: " << address << endl;
	cout << "Dereferenced address: " << *address << endl;
	cout << endl;
}















/* =======================
*	POINTER IN FUNCTION
* =======================
*
*	When we want to mutate the variable in a externally called function, we have to pass in the
*	address reference to the variable instead of the variable itself.
*	That way the function is able to mutate the value of the variable itself instead of creating an own
*	copy of it and use the copy inside the function, not mutating the original variable
*
*/


void CS2_pointersInFunc() {
	int num = 1;

	for (int i = 0; i < 5; i++) {
		incrementNum(&num);
	}
}
























/* =======================
*	POINTER IN ARRAYS
* =======================
*
*	By default, the array identifier is actually the address of the first element in the array
*	Therefore, these are equivalent:
*
*		int arr[] = {1,2,3}
*
*		cout << arr << endl;
*		cout << &arr[0] << endl;			// These 2 are equivalent
*
*	Since arrays are stored in continuous space in memory, incrementing the address will lead us to the
*	next element in the array. We can use that to access the elements in an array!
*
*/


void CS2_pointersInArray() {
	string elem[] = { "Element 1" , "Element 2", "Element 3" };

	string* address = elem;		// Or use &elem[0]

	int idx = 0;
	do {
		cout << "Address: " << address << ", Value: " << *address << endl;
		address++;
		idx++;
	} while (idx < 3);

}


























/* =======================
*	CONST
* =======================
*
*	Const is like a promise to the compiler. A promise that we won't mutate that variable in any way.
*	However, there are ways to bypass the promise and still mutate the variable itself
*	
*	There are certain ways we can apply the 'const' keyword. See:
* 
*	>	Adding 'const' before of the pointer sign (*) -- Pointer unaffected. Value affected
*		
*			int const *a = &n;
*			const int* a = &n;
* 
*		This means we cannot modify the VALUE, AKA the stuff inside the memory that is pointed.
*		Since pointer is unaffected, we can actually reassign the pointer to point to other memory locations
* 
*	
*	>	Adding 'const' after the pointer sign (*) -- Pointer affected. Value unaffected
*		
*			int* const a = &n;
*		
*		This means we cannot modify the POINTER, AKA the pointer cannot be reassigned to pointed to other memory location.
*		However since memory is unaffected, we can actually mutate the value inside the memory
* 
* 
*	>	Adding 'const' both before and after the pointer sign (*) -- Both pointer and value affected
* 
*			const int* const a = &n;
* 
*		We cannot reassign the pointer, while also cannot mutate the value in the memory of the pointer location
* 
*	---------------------------------------------------------------------------------------------------------------
* 
*	Using const in class pointers means we are not able to modify the object's value, and not able to use any of the
*	object's method that are not declared 'const'
* 
*	Class member methods that are declared const must not be able to mutate the object's member variables in any way, except
*	those who are declared 'mutable'
* 
*	To declare a class member method as const, syntax:
*		int getX() const { ... }
* 
*	To create an object which is const, syntax:
* 
*		const MyClass obj;
*	
*	Or by pointers and new keyword,
* 
*		const MyClass* obj = new MyClass();
* 
*		**Remember that if const is behind the pointer operator, it just means that the pointer cannot be reassigned. The member
*		  function which are non-const in this case can be accessed!
* 
*
*/


void CS2_const() {

	int n = 123;
	int m = 456;

	int* const a = &n;		//	Pointer operator before const. The pointer is const. The value is not
	
	// a = &m;		//ERROR
	*a = 123;		//OK

	int const* b = &n;
	const int* c = &n;		//	Pointer operator after const. The value is const, the pointer is not

	// *b = 123;		//ERROR
	c = &m;			//OK

	std::cout << *c << std::endl;


	const int* const d = &n;	//	Const is before and after pointer operator. Both value and pointer is const

	// *d = 123;			//ERROR
	// d = &m;			//ERROR

}















/* ==============================
*	OBJECT LIFETIME
================================ 
*	
*	Objects or datas that is allocated on the stack will get automatically deleted when it goes out of scope, kind of similar
*	to how Stack pops the items on top and the stuff is gone forever.
*	
*	Therefore, it is crucial that we don't do functions like so:
* 
*		int* createArray () {
*			int arr[50];
*			return arr;
*		}
* 
*	When it comes to actual time we want to use the array returned, we will run into error. This is because createArray function
*	has its own scope. We defined the array inside of that scope, and allocated it on the stack memory. 
*	After the array pointer is returned, the program goes out of the createArray function scope, and the array is basically 
*	'popped' from the stack memory.
* 
*	Some workarounds is to:
*		>	Allocate it on the heap, which is basically never released until programmer tells it to
*		>	Instead of creating array in it, create a function which takes in the array as argument instead to do stuff
*/

int* createArray() {
	int* arr = new int[50];
	return arr;
}
void fillArray(int val, int* arr, int size) {
	for (int i = 0; i < size ; i++) {
		arr[i] = val;
	}
}

void CS2_objectLifetime() {
	int* arr = createArray();
	fillArray(3, arr, 50);

	std::cout << arr[2] << std::endl;

	delete[] arr;
}
















/* ==============================
*	SMART POINTERS
================================
*
*	Since C++11, smart pointers are introduced, and are recommended to be used for stuff that are allocated on the heap memory
* 
*	What smart pointers are is basically a wrapper class which object is allocated on the stack, but stores an pointer to
*	an object or variable that is allocated on the heap. Upon going out of scope, since the smart pointer is stored on the
*	stack memory, its destructor will be called. In that destructor, it will delete the object or variable on the heap memory.
*	This creates an automation to free heap memory without having to use 'delete' keyword explicitly by us.
* 
*	To use smart pointers, include the header file <memory>
*		#include <memory>
* 
*	There are basically 3 types:
*		>	std::unique_ptr
*		>	std::shared_ptr
*		>	std::weak_ptr
* 
*	Unique pointer is a smart pointer that is most commonly used, and shall never be copied.
*	Reason is that copying the unique pointer, will lead to 2 pointers pointing to same block of memory in the Heap. Those
*	pointers may be in different scope, and once one of them gets out of scope, the stuff in the heap memory is basically deleted.
*	This will cause all other copied unique pointers to not work anymore!
* 
*	How to use:
*	
*	Note that smart pointers are templated (To allow it containing different datatypes). So we must specify the Datatype in
*	the arrow brackets
* 
*		1. Passing value by constructor. 
*			
			std::unique_ptr <Entity> obj ( new Entity() );

		2. Passing value directly by assignment operator

			std::unique_ptr <Entity> obj = new Entity();



	Now, if we want to have multiple copies of the pointer, we could use std::shared_ptr.
	It basically stores a reference counter, which keep tracks of how many active pointers are still 'alive'
	Every time a pointer goes out of scope, the counter decrements, and once it reaches 0, only then the stuff on the heap memory
	is deleted
* 
* 
*			//	Notice that we shall use the templated function 'make_shared' to create the object. This is for extra safety,
*			//	not mandatory though
*	
*			std::shared_ptr <Entity> obj = std::make_shared <Entity> ();
* 
*			std::shared_ptr <Entity> copy = obj;				//	This will copy the pointer. See COPY CONSTRUCTORS in Cheat Sheet 3
* 
* 
* 
* 
* 
*	A weak pointer is basically a weak shared pointer. It allows copies of the pointer, but does not count towards the reference
*	count. Say if there is 2 shared_ptr and 5 weak_ptr pointing to the same stuff in the heap memory. If the 2 shared_ptr
*	goes out of scope, then the stuff in the heap memory will be deleted, leaving the 5 weak_ptr fully useless.
* 
*			std::weak_ptr <Entity> weak = obj;			
*/

#include <memory>

void CS2_smartPointer() {

	{
		std::unique_ptr <int> arr ( new int[50] );
		arr.get()[5] = 69;					//Use get() to obtain the raw pointer
		
		std::cout << arr.get()[5] << std::endl;

	}	//End of scope. The heap allocated int array will be destructed


	struct Entity {
	public:
		string name;

		Entity(string name): name(name) {
			std::cout << "Entity COnstructed. Name: " << name << std::endl;
		}

		~Entity() {
			std::cout << "Entity Destroyed. Name: " << name << std::endl;
		}
	};

	{
		std::weak_ptr <Entity> weak1;

		{
			std::shared_ptr <Entity> shr1 = std::make_shared <Entity>("Alex");	
			std::cout << "Ref counter now is " << shr1.use_count() << std::endl;	//Here reference counter shall be 1

			weak1 = shr1;				
			std::cout << "Ref counter now is " << shr1.use_count() << std::endl;	//Since it is weak pointer, ref counter unchanged

			{
				std::shared_ptr<Entity> shr2 = shr1;	//	Ref counter shall be 2 now
				std::cout << "Ref counter now is " << shr1.use_count() << std::endl;

				if (auto p = weak1.lock()) {
					std::cout << p->name << std::endl;		//Here name shall print correctly
				}
				
			}			
			//End of scope for shr2 pointer

			std::cout << "Ref counter now is " << shr1.use_count() << std::endl;		//Here ref counter shall be back to 1.
		}
		//End of scope for shr1 pointer. Entity shall be destructed here

		if (auto p = weak1.lock()) {		//Since Entity is deleted, now weak1 is null ptr.
			std::cout << p->name << std::endl;		
		}
		else {
			std::cout << "Unable to lock weak1 pointer. Probably the Entity is already deleted\n";
		}

	}



}




















/* ==============================
*	ARROW OPERATORS
================================
*
*	An arrow operator (->) is really just a shortcut to DEREFERENCE a pointer, and access its properties using the dot operator (.)
* 
*	Instead of 
*		(*ptr).func();
*	We can
*		ptr->func();
* 
*	One trick is we can overload the arrow operator itself so it returns the correct thing that we want to be returned.
*	The best example is a self made smart pointer which when used arrow operator, shall always return the pointer stored in the
*	smart pointer object. 
* 
*	Also, we can check for the offset of a variable in a struct. This is a hacky trick
*/

struct Entity {
	int x, y, z;

	void printXYZ() {
		std::cout << x << " " << y << " " << z << std::endl;
	}
};

class ScopedPtr {
private:
	Entity* ptr;
public:
	ScopedPtr(Entity* ptr) : ptr(ptr) {}
	~ScopedPtr() {
		delete ptr;
	}
	Entity* operator->() {
		return ptr;
	}
};


void CS2_arrowOperator() {
	
	{
		ScopedPtr myPtr(new Entity());
		myPtr->x = 10;
		myPtr->y = 20;
		myPtr->z = 30;
		myPtr->printXYZ();
	}
	//	Destructed myPtr


	//	Let's find the offset in memory, of the z variable (Used long because size of pointer may be larger than int)
	long offset = reinterpret_cast<long>(&((Entity*)nullptr)->z);
	std::cout << "Offset of Z is " << offset << std::endl;

}

















/*
*	============================
*		DYNAMIC MEMORY
*	============================
*
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



void CS2_dynamicMemory() {
	cout << "Enter your array size: ";
	int n;
	cin >> n;
	int* myArr = new int[n];

	for (int i = 0; i < n; i++) {
		cout << "Enter your Number #" << i + 1 << ": ";
		cin >> myArr[i];
	}

	for (int i = 0; i < n; i++) {
		printf("Element at index #%d is %d \n", i, myArr[i]);
	}

	delete[] myArr;			//	After done, release the memory!!!

}




/*	=======================
*	RANDOM NUMBER GENERATION
*	=======================
*
*	In C++, random numbers are generated through rand() function. Unlike Java or other languages, it generates
*	INTEGERS from 0 to RAND_MAX, which is guaranteed to be at least 32767 (Depending on machines)
*
*	To use this function, one has to include the header file <cstdlib>.
*		#include <cstdlib>
*
*	Since of the way it generate integers and not floating point numbers, to obtain our range, we would use
*	modulo operator (%) to limit our upper boundary, along with (+) to set the lower boundary
*
*	Eg:	Set to generate from 10 to 20
*		int myRandom = 10 + ( rand() % 11 );
*	See: If rand() is 0, we will be getting 10
*		 At max ( rand() % 11 ) will be 10. Added with 10 will be 20 at max
*
*
*	Now, to make it more random, we shall set the SEED used to generate the random numbers using function
*	srand( seed ). This function only need to be called once, and it returns nothing. The argument that we pass
*	in is the seed (Number).
*	A common way to do this is to use the system time, which is the seconds passed since year 1970 or so.
*	We obtain that time using header file <ctime> and using function time( arg ) to obtain the time in seconds.
*	The arg specifies the location of memory to put the time in. We shall pass in NULL so that no memory is
*	allocated for obtaining time.
*
*		#include <ctime>
*		#include <cstdlib>
*		srand( time(nullptr) );
*
*		int myRand = 10 + ( rand() % 11 );
*
*/


//	Here is a program that generates number in range [10-20] 10000 times, and count the frequency for each number


#include <cstdlib>
#include <ctime>

void CS2_randomGenerator() {
	srand(time(0));

	int freq[11] = {};		//If i initialize with empty one, it will set all to 0. If I don't, it will be
							//whatever in the memory

	int ran;
	for (int i = 0; i < 10000; i++) {
		ran = 10 + (rand() % 11);
		freq[ran - 10] ++;
	}
	for (int i = 0; i < 11; i++) {
		cout << "Frequency of " << i << " is " << freq[i] << endl;
	}

}