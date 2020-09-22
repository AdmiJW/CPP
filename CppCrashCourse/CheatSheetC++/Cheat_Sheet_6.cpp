#include <iostream>
#include <string>

using namespace std;



/*
*	FUNCTION TEMPLATES
* 
*	There are 2 types of templates in C++: Function templates and Class templates
* 
*	Templates are like generics in Java.
* 
*	Say we have a function sum() that takes in integer arguments. If we want to have the same function but
*	takes in other datatypes like double or float, then we need to overload it.
* 
*	However, if we want to implement it for a lot of other datatypes, including user-defined ones (classes), then
*	we have to write a lot of overloaded same functions, to an extent that it will be hard to maintain, and
*	eats up quite a sum of memory
* 
*	Using templates and generics, we can avoid the necessity to overload the function for every single datatype,
*	if the implementation is identical
* 
*	Using templates, we avoid the necessity of specifying the exact datatype of variables and arguments, by using
*	template type parameters, which is like defining a name to a unknown datatype
* 
*	Function templates can be viewed as a factory of functions. It generates overloaded functions only when
*	the certain data type is used with that function template. Say we have a templated function. If in the program
*	only uses int and double as arguments, then only 2 overloaded function will be generated. 
* 
*	Example:
*/
							
template <class T>			//	After declaring template, the statement directly following it must be function or class
							//	T is the name given to the unknown type. We will be using T afterwards.		
							//	We can use names other than T. And instead of 'class', we can also use 'typename'

T sum(T a, T b) {			//	This function takes in argument a and b of type T, and return data of type T also
	cout << "Same type sum" << endl;
	return a + b;
}




template <class T, typename U>	//	For different types, we use comma to seperate them, and giving different names

T sum(T a, U b) {				//	Note that return type is that of first argument's T. If T is int and U is double,
								//	result will be parsed into int and returned in form of Int
	cout << "Different type sum" << endl;
	return a + b;
}


template <class T, class U>		//	To solve the above issue, use the newer C++ feature keyword 'auto'
								//	which automatically detects the returned data's datatype
								//	If a is int and b is double, a + b is double. Then double will be returned
auto sumAuto(T a, U b) {
	return a + b;
}

void CS6_functionTemplate() {
	int a = sum(1, 2);
	int b = sum(1, 2.345);
	int c = sumAuto(1, 2.345);

	cout << a << " " << b << " " << c << endl;
}
















/*
*	CLASS TEMPLATES
* 
*	Classes can also be applied templates. What class templates can do is that the member variables and methods
*	can use the unknown datatype. This is very commonly used in data structures like Vectors in C++ or Collections
*	in Java
* 
*	If a class was templated, if we want to define the member variables or methods outside of the class itself
*	(Using scope resolution operator), we have to declare the template type parameters again
* 
*	To create an instance of the templated class, we would need to specify the exact datatype in angle brackets,
*	which is a lot familiar if you used data structures before like 
*		>	List<Integer> li;
*		>	vector<int> li;
*/


//	Here I just declare the class. Definition will be done outside the class
template< class T, class U >
class Pair {
	T var1;
	U var2;
public:
	Pair(T, U);		//	Constructor declaration
	void printContent() {
		cout << "var1: " << var1 << ", var2: " << var2 << endl;
	}
	auto add();		//	add() method declaration

	Pair<T,U> operator+(Pair&);	//	Declaration of + operator overload
};


//	Here I will define the methods


template< class T, class U>		//Once again I need to declare the template type parameters
Pair<T, U>::Pair(T var1, U var2) : var1(var1), var2(var2) {		//	Here the Pair class must be specified the types
																//	<T, U> in angle brackets. Reason is due to
																//	template specialization covered later
};


template< typename T, typename U>
auto Pair<T, U>::add() {				//	Remember for method definition, the return type need to be specified first
	return var1 + var2;
}


//	+ operator now essentially returns a new Pair object which var1 is the sum of var1 and var2 is sum of var2
template< class T, typename U>
Pair<T,U> Pair<T, U>::operator+ (Pair& obj2) {
	T sumOfT = this->var1 + obj2.var1;
	U sumOfU = this->var2 + obj2.var2;
	Pair<T, U> newPair(sumOfT, sumOfU);
	return newPair;
}


void CS6_classTemplate() {
	Pair<int, double> obj1(10, 1.2);		//	Creation of instances, must use angle bracket and specify the
	Pair<int, double> obj2(5, 3.4);			//	exact type of the T and U
	obj1.printContent();
	obj2.printContent();

	cout << obj1.add() << endl;
	cout << obj2.add() << endl;

	Pair<int, double> obj3 = obj1 + obj2;
	obj3.printContent();

	cout << obj3.add() << endl;
}




























/*
*	TEMPLATE SPECIALIZATION - FUNCTION
* 
*	Templates will treat all data types same. In other words, regardless of the datatype itself, the very same
*	implementation (code) will be applied to them. For example, in the Pair class above, no matter the datatype,
*	sum() will always add them both
*	
*	Sometimes we want to apply a different implementation based on certain datatypes. This is where we'll use
*	TEMPLATE SPECIALIZATION.
* 
*	For function template specialization, we just repeat writing the new version of the function. Except this time
*	the template type parameters will have some unknown types left out - Those data type that we want to 
*	specialize, which in the parameter and return type, we will replace it with the exact type now
*/

template< class T, class U >
void status(T t, U u) {
	cout << "General template function " << t << " " << u << endl;
}

//	Here we will specialize the type T to be type char. This function will be run if argument of type char
//	is passed in in place of T. (Type U is still unknown)

template< class U >				// <- class T is left out because it is specialized: We know the exact type
void status(char t, U u) {
	cout << "Specialization - T is char " << t << " " << u << endl;
}


//	Here we will specialize the type T to be type char, while type U to be type double

template<>
void status(char t, double u) {
	cout << "Specialization - T is char, U is double " << t << " " << u << endl;
}



void SC6_functionTemplateSP() {
	status("Hello World", 12345);		//	General template. No specialization
	status('a', "PPAP");				//	First specialization: T is char
	status('a', 12.345);				//	Second specialization: T is char and U is double 
}

























/*
*	TEMPLATE SPECIALIZATION - CLASS
* 
*	In the case of class, it has almost the same as function template specialization. See:
*/

template <class T, class U>
class Container {
	T var1;
	U var2;
public:
	Container(T t, U u) : var1(t), var2(u) {}
	void status() {
		cout << "This is general template class with no specialization " << var1 << " " << var2 << endl;
	}
};

//	A specialized class where T is of type char
template<class U>
class Container<char, U> {
	char var1;
	U var2;
public:
	Container(char t, U u) : var1(t), var2(u) {}
	void status() {
		cout << "Specialized class - T is char " << var1 << " " << var2 << endl;
	}
};


//	A specialized class where T is of type char and U is of type double
template<>
class Container<char, double> {
	char var1;
	double var2;
public:
	Container(char t, double u) : var1(t), var2(u) {}
	void status() {
		cout << "Specialized class - T is char, U is double " << var1 << " " << var2 << endl;
	}
};


void CS6_classTemplateSP() {
	Container<string, char> obj1("Hello World", '!');		//Object instantiated based on the general template class
	Container<char, string> obj2('!', "Hello World");		//Object instantiated based on the first specialized template class
	Container<char, double> obj3('!', 3.142);				//Object instantiated based on the second specialized template class
}