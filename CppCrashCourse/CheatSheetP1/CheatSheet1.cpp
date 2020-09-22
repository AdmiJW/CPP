
#include <iostream> 
#include <string>
using namespace std;



int main() {

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

	cout << "Enter your name: ";
	string name;
	cin >> name;
	cout << "Hello " << name << endl;














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

	int age = 25;
	age = 15;

	const float PI = 3.142;
	//PI = 2.31;			//ERROR!
























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

	string part1 = "Hello ";
	string part2 = part1.append("World!");

	cout << part2 << endl;
	cout << "Length: " << part2.length() << endl;
	cout << "Size: " << part2.size() << endl;
	part2[0] = 'J';
	cout << part2 << endl;


















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

	string animals[10] = { "dog", "cat", "rabbit" };	//The array is of size 10, but only first 3 elements are initialized
	cout << animals[1] << endl;
	cout << animals[4] << endl;
	animals[4] = "Donkey";
	cout << animals[4] << endl;


















	/* =======================
	*	CONDITIONAL OPERATORS
	* =======================
	*
	*	If else statement is very similar to Java
	*
	*	Even the ternary operator. Except we can perform statements in it
	*
	*/

	bool toLog = true;
	bool isHello = false;

	string str = isHello ? "Hello World" : "Bye World";

	toLog ? cout << str << endl
		: cout << "No Logging" << endl;


















	/* =======================
	*		ENUMS
	* =======================
	*
	*	Enums are a collection of constant values. We can define an enum in curly braces, and use it like a datatype
	*/


	enum Colors { RED, BLUE, GREEN, YELLOW, ORANGE };

	Colors myColor = RED;

	switch (myColor) {
	case RED: cout << "Red is passionate!" << endl;
		break;
	case BLUE: cout << "Blue is gloomy!" << endl;
		break;
	case GREEN: cout << "Green is good for your eye!" << endl;
		break;
	case YELLOW: cout << "Yellow is kinda joyful!" << endl;
		break;
	case ORANGE: cout << "Orange is more joyful than yellow" << endl;
		break;
	default: cout << "I wonder what is this color?" << endl;
	}























	/* =======================
	*		LOOPS
	* =======================
	*
	*	While loops and do while loops are a lot similar in Java.
	*	For loops as well, but note that arrays, does not have any property that gives us the array length
	*/


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





