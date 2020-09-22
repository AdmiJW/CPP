#include <iostream>
#include <string>

using namespace std;

/*
*	MORE ON CLASSES --- (SOLOLEARN)
* 
*/





/*
*	HEADER FILES AND SOURCE FILES
* 
*	Header files usually contain function prototypes (AKA function declaration) and variable declarations.
*	It might also contain templates for the class (Defines the class, but the member variables and methods
*	are not defined)
* 
*	The real definition part is included in the source code file (.cpp file), which uses Scope Resolution operator
*	
*	Scope Resolution Operator (::) is used for accessing stuff in classes. It is particularly useful when we
*	want to define member variables and methods outside of the class itself. 
*	Since we already defined the class in the header file, in the main source code file we would just use the scope
*	resolution operator. This prevents us from defining the class again, while defining its member variables and
*	methods
*
*	See:
*
*/


// --- Inside Header file (myclass.h)
#ifndef MYCLASS_H
#define MYCLASS_H	

	//	This is an example of class template. It is a legit class, but all the stuff inside is just declarations
	class MyClass {
	public:
		MyClass(int);					//Constructor declaration
		void printStuff(string);		//printStuff(string) method declaration
		void printA();					//printA() method declaration
		~MyClass();						//Destructor declaration
	protected:
	private:
		int A;
		static string message;
	};

#endif


//	Inside the source file (myclass.cpp)

// #include "myclass.h"						<- Since myclass.h don't really exist, i comment it

	//	Now only we define the methods and variables
	MyClass::MyClass(int a = 0) {
		A = a;
	}
	void MyClass::printStuff(string str) {
		cout << str << endl;
	}
	void MyClass::printA() {
		cout << A << endl;
	}
	string MyClass::message = "Hello World";






















/*
*	DESTRUCTORS
*
*	Class destructors are called when 'delete' keyword or equivalent is called on the pointer to the object
*	instance.
*	It is also called automatically when the execution of program hits the end of scope. The object instance
*	is said to go out of scope, and the destructor is executed to clean up any allocated memory in the heap (dynamic)
* 
*	Destructors, like constructors, has same name as the class. The only difference is that it is prefixed with
*	a tilde sign (~). It can't return any value, nor can have any parameters
*
*/

class myDestructor {
public:
	~myDestructor() {
		cout << "myDestructor instance destroyed properly!" << endl;
	}
};

void CS4_destructor() {
	myDestructor instance1;

}		//	When program hits this ending curly braces, destructor is called














/*
*	SELECTION OPERATOR
* 
*	When we want to access the object members, there are few cases:
*		>	Access through the object itself or its references.
*			In that case, we would use dot operator (.)
*		
*			obj.func();
* 
*		>	Access through the object's pointer
*			In that case, we would use the arrow operator (->)
*			
*			objPtr->func();
* 
*		>	Other ways include to dereference it first then use dot operator
* 
*			(*objPtr).func();
* 
*		>	Vice versa, we can make the object a pointer then access with arrow operator

			(&obj)->func();

		In above two usages, brackets are important to convert object to pointer first and vice versa
*
*/


class MySelection {
public:
	void func() {
		cout << "Hello" << endl;
	}
};

void CS4_selection() {
	MySelection obj;

	obj.func();
	
	MySelection* ptr = &obj;
	ptr->func();

	(*ptr).func();

	(&obj)->func();
}





















/*
*	CONSTANTS
* 
*	Any variable declared with keyword 'const' cannot have its value changed. (Except when use const_cast )
*
*	Constants are helpful in certain opimizations, like in a for loop, the value of the variable don't have to be
*	accessed everytime
* 
*	
*	We can make objects const as well. This object now cannot have its member variables modified. Call to member
*	methods that modify the member variables are not allowed also.
*	Those member variables must only be initialized during declaration by the constructor. See Later topic
* 
*	A const object will only have access to methods that also declared with const keyword, which kinds of promises
*	the compiler that this function will not modify any of the member variables
*	Syntax:
*			void func() const {...}
* 
*	An exception is that a member variable is declared with a 'mutable' keyword. In that case, the variable can be
*	easily modified by a constant object, and const functions
*/

class Constant {
public:
	Constant(int a = 0, int b = 0) {
		notMutable = a;
		isMutable = b;
	}
	void changeNotMutable(int chg) {
		notMutable = chg;
	}
	void changeMutable(int chg) const {
		isMutable = chg;
	}
	int notMutable;
	mutable int isMutable;
};


void CS4_constant() {
	const Constant obj(10, 20);

	//	obj.changeNotMutable(12);			Error. changeNotMutable is not a const method.
	obj.changeMutable(66);				//	OK. changeMutable is a const method, and isMutable is mutable variable
}
























/*
*	MEMBER INITIALIZERS
* 
*	If we have const variables as class member, we can't assign them using the traditional way even
*	in the constructor! This is where we shall use MEMBER INITIALIZER LIST
* 
*	Member initializer list follows the following syntax:
*		constructor( params... ): var(param1), var(param2) { ... }
* 
*	After the constructor declaration (after parameter list), we declare a colon indicating the member initializer
*	list, then followed by a comma seperated list, which each one start with the identifier to the variable to
*	be initialized, and like a function, pass in the value to initialize. Eg:
* 
*		MyClass(int initVal): var(initVal) {...}
*
*	Member Variables MAY use member initialization list
*	Constant Member Variables MUST use member initialization list
*/

class MemberInit {
	const int myconst = 0;
public:
	//	MemberInit(int x) {
	//		myconst = x;						<< This way of initializing constant variable throws error
	//	}
	MemberInit(int x) : myconst(x) {}			//	Using member initializer list is allowed
};
















/*
*	FRIEND KEYWORD
* 
*	Private member functins are not accessible outside the class itself. However, an exception is by declaring
*	'friend' functions.
*	Friend functions are a function outside of the class itself, that takes in the object reference as argument,
*	and possesses the ability to access the object's private member variables and methods
* 
*	To do so, we must first DECLARE (not define. Actual definition is outside of the class) the friend function
*	in the class
* 
*	Syntax:
*			friend <return_type> <identifier> ( MyClass&, ...params );
* 
*	Then outside of the class, we define the function as usual. The only difference is the function can access
*	the object's private members as if it is a method in the class
* 
*/


class Friend {
private:
	string message = "Hello My Friend";				//	message is a private variable

	friend void CS4_friendFunc(Friend&, string);
};

void CS4_friendFunc(Friend& ref, string name) {
	cout << ref.message << " " << name << endl;
}























/*
*	THIS KEYWORD
* 
*	Inside the member function of a class, we might want to refer to the current instance (The instance which
*	the method belongs to). This is done by using 'this' keyword. 'this' keyword returns the pointer to
*	the current instance, therefore arrow operators (->) will be used
*
*/

class This {
	int x;
public:
	void printX() {
		cout << this->x << endl;
	}
};























/*
*	OPERATOR OVERLOADING
* 
*	Built in operators (like +, -, *, / ...) can be easily overloaded.
*	Under the hood, when operators are used, it actually calls a function respective to the operator itself
* 
*	Therefore we overload the operator by overload the operator's function, applying our own logic into it
* 
*	Syntax:
*		<return-type> operator<operator> ( <param> ) {...}
* 
*	Eg: To overload the + operator:
*		
*		MyClass operator+ (MyClass& obj2) {...}
* 
*	The return type is another object of MyClass. This is because adding usually returns a different value
*	operator keyword is followed by the actual sign of the operator +
*	The function takes in another object reference. This is because + is binary operator, requires 2 objects to
*	work with
*
*	For other operators like ==, return type shall be boolean (bool)
*/

class Coin {
	int value;
public:
	Coin(int val) : value(val) {}

	Coin operator+ (Coin& obj2) {
		int sum = this->value + obj2.value;			// Adding two coins result in new coin with value being sum of 2
		Coin newCoin(sum);
		return newCoin;
	}
};