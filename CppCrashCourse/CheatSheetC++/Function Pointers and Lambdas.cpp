#include <iostream>
#include <vector>

#include <functional>


/*
 	Function Pointers are what it is: A pointer to a function - Pointer to A set of instructions for computer to execute
	This makes functions a lot more flexible: We can store them in variables, pass them as arguments of another
	function and calling them through arguments passed or variables.

	Do note that there is difference in referring to functions:
		>	func()		-	This is invoking the function func
		>	func		-	This is referring to function itself in whole

	Now, the most easiest way to have a function pointer is to have its type automatically inferred using
	'auto' keyword

	However, let's see the actual type of a function pointer:

			<return-type> ( * <identifier> ) ( <param-type...> )

	Eg Let's say we have a function 'examplefunc' of return type void, takes in one int parameter, and we would like
	it called 'myfunc'

			auto myfunc = examplefunc;
			myfunc();

			OR -----------------------

			void (*myfunc)(int) = examplefunc;
			myfunc();
*/

int examplefunc(int a, int b) {
	std::cout << "Multipling " << a << " and " << b << std::endl;
	return a * b;
}

void FPaL_1() {
	int res;

	//	Method 1 - Easiest using 'auto' keyword to auto infer type
	auto myfunc1 = examplefunc;
	res = myfunc1(1, 2);
	std::cout << "Result is " << res << std::endl;


	//	Method 2 - Use the actual type declaration
	int (*myfunc2)(int, int) = examplefunc;
	res = myfunc2(3, 4);
	std::cout << "Result is " << res << std::endl;


	//	Method 3 - typedef method
	typedef int (*mytypedef)(int, int);

	mytypedef myfunc3 = examplefunc;
	res = myfunc3(5, 6);
	std::cout << "Result is " << res << std::endl;
}












/*
	Next up, a function pointer can be passed with ease into another function. This is very useful in functional
	programming paradigm related functions like
		>	map
		>	fliter
		>	reduce
		>	forEach
	or even normal sorting where we pass in custom comparators

	To pass into a function, it has to be in parameter list, and that's it! We can already use it in our function
*/


//	The function which takes in a function pointer, which is executed on each element in vector
void forEach( const std::vector<int>& vec, void(*argFunc)(int) ) {
	for (int i : vec) {
		argFunc(i);
	}
}
//	The function that we want to be call on every element
void printSquare(int a) {
	std::cout << "Square of " << a << " is " << a * a << std::endl;
}

void FPaL_2() {
	std::vector<int> vec = { 2,4,6,8,9 };

	void (*printSqr)(int) = printSquare;
	forEach(vec, printSqr);
}













/*
	In the example above, we have to write an entire function which is to be called on each element. However, when
	we are done, we probably won't call that function anymore! Is there a way to make a 'discardable, anonymous
	function'? Yes - Lambda functions

	Lambda functions are more thought as 'inline' functions. Function itself are written inline.

	The syntax for a lambda definition goes as follows:

			[capture]( param-list ) -> return-type {
				implementation
			}

	Eg to implement the printSquare above:

			[](int a) -> void {
				std::cout << "Square of " << a << " is " << a * a << std::endl;
			}
*/

void FPaL_3() {
	std::vector<int> vec = { 3,6,9,12,15 };

	void(*printSquare)(int) = [](int a) {
		std::cout << "Square of " << a << " is " << a * a << std::endl;
	};

	forEach(vec, printSquare);


	//	Let's print cube
	forEach(vec, [](int a) -> void {
		std::cout << "Cube of " << a << " is " << a * a * a << std::endl;
	});
}


















/*
	You might wonder what is the 'capture' inside square bracket actually. Here's a brief overview

	Maybe you think that lambda function is independent: It don't have access to outside scope variables. However,
	it is very possible. Capture allows us to choose how will the value be passed into the lambda expression itself.

	>	=			- Pass by value
	>	&			- Pass by reference
	>	var_name	- Select the variable you want to pass in by value
	>	&var_name	- Select the variable you want to pass in by reference

	To essentially mutate the variable passed in, we must add a 'mutable' keyword after the parameter list.
*/


//	THe new forEach, which to use capture, must have include <functional>
//	and use type of std::function reference as parameter
void forEach2(const std::vector<int> vec, const std::function<void(int)>& myfunc) {
	for (int i : vec) {
		myfunc(i);
	}
}


void FPaL_4() {
	std::vector<int> arr = { 4,8,12,16,20 };

	// The outside variable we want to use in lambda function
	int occurrence = 0;

	//	Remember to be able to change outside variable scope, use mutable keyword
	auto countOccurrenceAndOutput = [&](int a) mutable {
		occurrence++;
		std::cout << "Occurrence " << occurrence << " Element: " << a << std::endl;
	};

	forEach2(arr, countOccurrenceAndOutput);

	std::cout << "Now Occurrence global is " << occurrence << std::endl;


	//	See what happens if I pass by value. Outside variable wouldnt change
	//	It essentially creates a closure, which a new variable is created which is defined in the function itself
	//	but unrelated to the original one
	auto countOccurrenceAndOutput2 = [=](int a) mutable {
		occurrence++;
		std::cout << "Occurrence " << occurrence << " Element: " << a << std::endl;
	};

	//	new variable defined in closure: value - 5
	forEach2(arr, countOccurrenceAndOutput2);
	std::cout << "Now Occurrence global is " << occurrence << std::endl;

	//	new variable defined in closure: value - 5
	forEach2(arr, countOccurrenceAndOutput2);
	std::cout << "Now Occurrence global is " << occurrence << std::endl;
}

