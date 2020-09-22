
#include <iostream> 
#include <string>
using namespace std;




/*
	C++ was created back in 1980, which is inspired by SIMULA and C language
	It is faster in performance, since it operates closer to hardware, less abstraction
	It is a compiled language (Not interpreted)
	Statically typed language (No dynamic type, no ability to change the type of the variables)
*/

/* =======================
*		BASICS
* =======================
*
*	First to use input and output, we have to include the iostream header file
*
*		#include <iostream>
*
*	An header file add functionality to our C++ programs. It is kind of like importing other codes into our
*	program
*	A header file usually contains declarations and nothing else. Definition of functions and variables are
*	usually contained in source file (.cpp) instead
*
*	Another thing is declaring namespaces. Declaring namespaces allow us to use names for objects and
*	variables from the library without calling the namespace itself.
*
*	We can choose to not include the namespace std, but that would mean everytime we want to use cout and cin,
*	we need to do so:
*	BTW, << is called insertion operator
*
*		std:cin >> something
*		std:cout << something
*
*	With std namespace imported, we can omit specifying the std namespace
*
*
*	Like most languages, we need a main() function which is the starting point of the program.
*	It is a function which return type is int, probably meaning exit status code
*
*		int main() {
*			...code
*		}
*
*	To print into and obtain the input from user, we would use cin and cout like talked before, which is in std namespace
*
*	***Another bonus: To get cleaner output from console, use
			system("pause>0");
		But ensure that it is at end of program. It causes the program to pause actually!
*/

void CS1_basics() {
	cout << "Enter your name: ";
	string name;
	cin >> name;
	cout << "Hello " << name << endl;
}













/* =======================
*		TYPES
* =======================
*
*	Variables needed to be specified a type. Variables are spaces allocated on the memory which stores some data that
*	program needs.
*
*	Some commonly used types are:
*		>	int			-4 Bytes, 32 bit
*		>	float		-4 Bytes, 32 bit
*		>	double		-8 Bytes, 64 bit
*		>	char		-1 Bytes (ASCII)	(Use single quotes)
*		>	string							(Use double quotes)
*		>	bool		-1 Bytes
*
*	NOTE: To be able to use string type, we need to include its header <string>
*		#include <string>
*	Although some compilers automatically do it for us, we shall include it ourselves
*
*	Some modifiers can be applied to integers, like Signed, Unsigned, Long, Short
*
*	We can make a constant using 'const' keyword
*/


void CS1_types() {
	int age = 25;
	age = 15;

	const float PI = 3.142;
	//PI = 2.31;			//ERROR!

}



















/* =======================
*		OPERATORS
* =======================
*
*	Arithmetic:				+
							-
							*
							/
							%
							++
							--

	Assignment:				=
							+=
							-=
							*=
							/=
							%=		(Stores back the modulo)
							&=		(AND)
							|=		(OR)
							^=		(XOR)
							>>=		(LEFT SHIFT)
							<<=		(RIGHT SHIFT)

	Comparison:				==
							!=
							>
							<
							>=
							<=

	Logical:				&&
							||
							!
*/
















/* =======================
*		STRINGS
* =======================
*
*	String are objects in C++, just like in Java
*
*	String has an append() function which is much efficient than + operator to concatenate strings
*
*	String has a length() function to obtain the length.
*	The same goes for size() function. Both are of the
*
*	We can access string characters just like array using square brackets []
*
*	We can even mutate the string characters by setting it
*
*
*	Regarding C++ input, cin considers a space (whitespace, tabs etc...) as terminating character.
*	Therefore we shall use another function instead:
*
*		getline( src, variableToStore );
*
*	Like:
*
*		string inputVar;
*		getline( cin, inputVar );
*/


void CS1_strings() {
	string part1 = "Hello ";
	string part2 = part1.append("World!");

	cout << part2 << endl;
	cout << "Length: " << part2.length() << endl;
	cout << "Size: " << part2.size() << endl;
	part2[0] = 'J';
	cout << part2 << endl;


}















/* =======================
*		MATH
* =======================
*
*	Some built in functions are max() and min()
*	>	max(x,y)
*	>	min(x,y)
*
*
*	Other math functions, we have to include <cmath> header file
*			#include <cmath>
*
*	>	sqrt(x)
*	>	round(x)
*	>	log(x)
*	>	abs(x)
*	>	floor(x)
*	>	pow(x,y)
*	and many more...
*
*/

#include <cmath>

void CS1_math() {
	int n = 50;
	float f = sqrt(n);
	float r = round(1.413);
	float l = log(100);
	int p = pow(2, 4);
}














/* =======================
*		ARRAYS
* =======================
*
*	We declare arrays using syntax:

		type identifier[size] = { ...values };

	Example:
		int arr[5] = {1,2,3,4,5};


	However, with initialization, we can omit the size of array. Like so:

		int arr[] = {1,2,3,4,5};


	We can partially initialize the array, only filling it with some of the values (Requires size to be specified)

		int arr[5] = {1,2,3};

	Lastly, to access an array element, use square brackets

		cout << arr[1] << endl;
*
*/


void CS1_arrays() {
	string animals[10] = { "dog", "cat", "rabbit" };	//The array is of size 10, but only first 3 elements are initialized
	cout << animals[1] << endl;
	cout << animals[4] << endl;
	animals[4] = "Donkey";
	cout << animals[4] << endl;

}
















/* =======================
*	CONDITIONAL OPERATORS
* =======================
*
*	If else statement is very similar to Java
*
*	Even the ternary operator. Except we can perform statements in it
*
*/


void CS1_conditionalOperators() {
	bool toLog = true;
	bool isHello = false;

	string str = isHello ? "Hello World" : "Bye World";

	toLog ? cout << str << endl
		: cout << "No Logging" << endl;

}
















/* =======================
*		ENUMS
* =======================
*
*	Enums are basically a user-defined data type
*	Enums, short for enumerations, are basically set of fixed, constant values. It is a way for us to give names to values.
*	We can use it to define a set of allowed values, which shall not be any other undefined values
* 
*	It is particularly useful when we want to represent state using integers, but still maintain good readibility. 
* 
*	Always remember, classic Enums in C++ are still integers.
* 
*	When undefined, the values will start from 0. We can set the initial value to start couting the enum value, or even
*	set them all!
* 
*	
*/

void CS1_enums() {
	enum Gender {
		F, M
	};

	Gender g = F;

	switch (g) {
	case F:
		std::cout << "You are a female" << std::endl;
		break;
	case M:
		std::cout << "You are a male" << std::endl;
		break;
	}


	enum MyEnum {
		A = 5,
		B = 10,
		C
	};

	std::cout << C << std::endl;		//	C is 11, because B is 10, and compiler will auto increment from the last one
}



/* =======================
*		ENUM CLASSES
* =======================
*
*	Since C++11, we shall be using Enum classes instead of classic Enums.
*	There are several problems with classic Enums:
*	
*	>	No same identifiers (Names) in different Enums:
* 
*			enum Gender {
*				F, M
*			}
*			enum Position {
*				F, M, B						//Error due to duplicated value names 'F' and 'M'
*			}
* 
*	>	No same variable name as Enum values
*	
*			enum Gender {
*				F, M
*			}
*			int F = 100;					//Error as 'F' is both an enum value and the variable identifier
* 
*	>	Not type safe as Enums are just integer values that are easily compared
* 
*			enum Gender { F, M }
*			enum Position { U, D }
* 
*			Gender g = F;
*			Position p = U;
* 
*			std::cout << (g == p) << std::endl;			//Returns 1 as 'g' and 'p' both has value F and U which is 0
* 
* 
*	Enum classes is both strongly typed and strongly scoped. 
	There is no implicit conversion to int ( like above cases where (g == p) becomes true because both are converted to value 0)
	Comparision between different enums are not allowed

	To use enum classes, just add the 'class' keyword after the 'enum' keyword

	enum class <enumName> { <values...> }

*/	

void CS1_enumClasses() {
	enum class Gender {
		F, M
	};
	enum class Position {
		U, D
	};

	Gender g = Gender::F;		//Now scope identifiers are required, just like a real class!
	Position p = Position::U;

	/*if (g == 0) {									//Invalid. comparison between enum classes and int. There is no implicit conversion
		std::cout << "Female is 0!" << std::endl;
	}*/
	if (g == Gender::F) {
		std::cout << "Gender is Female" << std::endl;
	}

	/*if (g == p) {				//Invalid. G and P are different enums. Cannot be compared
		std::cout << "G is equal to P" << std::endl;
	}*/
}

















/* =======================
*		LOOPS
* =======================
*
*	While loops and do while loops are a lot similar in Java.
*	For loops as well, but note that arrays, does not have any property that gives us the array length
*/


void CS1_loops() {
	int count1 = 1;
	while (count1 <= 10) {
		count1++;						// Forgetting to update the counter will cause inifinite loop
		cout << count1 << endl;
	}

	int count2 = 1;
	do {
		cout << count2 << endl;
		count2++;
	} while (count2 <= 10);


	string cars[] = { "Volvo", "Perodua", "Proton", "Mercedes" };

	for (int i = 0; i < 4; i++) {			//Arrays dont have any properties that give us the length! We have to hardcode it
		cout << cars[i] << endl;
	}
}







