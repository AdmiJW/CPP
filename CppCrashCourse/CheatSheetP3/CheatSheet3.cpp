#include <iostream>
#include <string>
using namespace std;

/*
*	==================================
*		CLASSES
*	=================================
*	
	In C++, Creating a class is pretty similar to that of in Java.
	>	Using keyword 'class' followed by the class identifier. 
	>	Codes enclosed in curly braces
	
	However, the access specifiers are set by using one of the access specifiers, and in a python-y way,
	as such:

	>	public:
	>	protected:
	>	private:		(Default)





		class myClass {
			public:
				...properties and method which shall be public (Able to access directly)
			private:
				...properties and method which only can accessed in class
			protected:
				...properties and method which only can accessed in class and subclass (child class)
		}

		Unlike Java, we dont construct objects using 'new'. We simply just declare the variable and that's it!


		myClass class1;		// That's it!!
















	==================================
*		CONSTRUCTORS
*	=================================
	
	Constructors are a handy method to help us initialize the object. It has such rules:
		>	It must has no return type
		>	It must be same name as class
		>	We put constructor method in public access specifier



		class myClass {
			public:
				...properties

				myClass( ...params ) {
					...code to set up
				}
		}


		myClass class ( ...arguments );



















	==================================
*		CLASS METHODS
*	=================================
* 
*	Constructor can be thinked as one of class methods. Therefore we create class methods in a very similar way
* 
*	We call the class method in very similar way. Using dot notation ( obj.method ) (The same goes for proeperties)
*	HOWEVER, if what we have is the class pointer, then we use arrow notation ( objPoint -> method ) (The same goes for properties)
* 
* 
*		class myClass {
*		public:
*			...properties
*			myClass( ...params ) {
*				settingUp...
*			}
*			returntype myMethod (...params) {
*				...doStuff
*			}
*		}
* 
*		myClass class1 ( ...arguments);
*		class1.myMethod( ...arguments);
* 
*		myClass* pointer = &class1;
*		pointer -> myMethod(...arguments);
* 
* 
* 
* 
*		
* 
* 
* 
* 
* 
* 
* 
* 
* 
* ==================================
*	CLASS METHOD: OUTSIDE DEFINITION
* ==================================
* 
* Class methods can be defined outside the class itself. We'll need to use the scope resolution ::
* modifier for this
* However, to define the function outside the class, the function must first be declared inside the class.
* 
* Since constructor is kind of a class method, it is also possible to define constructor outside of the class
* 
* 
*	class MyClass {
*	public:
*		MyClass( ...params );
*		void myMethod( ...params );				// Method declaration MUST in class first!
*	}
* 
* 
*	MyClass::MyClass ( ...params ) {
*		...constructor definition
*	}
* 
*	void MyClass::myMethod ( ...params) {
*		...function definition
*	}
*	
* 
* 
* 
* 
* 
* 
* 
* 
* 
* 
* 
* 
* 
* 
* 
* 
* 
* 
* 
* 
* 
* 
* 
* 
* 
* 
*	==================================
*		ENCAPSULATION
*	=================================
* 
*	Encapsulation states that object properties shall not be publicly accessible, and shall only be
*	modified or obtained using getters or setters
* 
*	In C++ this is done by putting the properties itself in private access specifier block, while the
*	getters and setters in the public access specifier
* 
*	Note that if we want to have access to properties in subclasses, properties shall be placed in
*	protected instead
* 
*	
* 
*		class myClass {
*		private:
*			string prop1;
*			int prop2;
*		public:
*			myClass ( ...params ) { ...initialize }
*			getProp1() { return prop1; }
*			setProp1(string newval) { prop1 = newval; }
*			getProp2() { return prop2; }
*			setProp2(int newval) { prop2 = newval; }
*		}
* 
* 
* 
* 
* 
* 
* 
* 
* 
* 
* 
* 
* 
* 
* 
* 
* 
* 
*	==================================
*		INHERITANCE
*	=================================
* 
*	Extending classes in C++ is quite different syntax from Java.
* 
*	There are 2 things to do to extend a class:
*		>	At subclass class definition, a colon directly follows the identifier, putting public followed
*			by the superclass identifier
* 
*			Eg:			class mySubClass: public mySuperClass { ...implement }
*		
*			(The public access specifier means that whatever is public in mySuperClass, it shall be public in
*			mySubClass toos)
* 
*		>	In the constructor of subclass, a colon directly follows the parameter list, then the super class
*			along with the supposed arguments that shall go into the superclass constructor
*			Kinda similar to the creating object syntax, without mentioning the datatype
* 
*			Eg:	
*					class mySubClass: public mySuperClass {
*					public:
*						mySubClass( int forSub, int arg ): mySuperClass(forSub) {
*							...initialization
*						}
*					}
* 
* 
*		C++ supports multilevel inheritance. Which means a class can be subclass of its superclass, which is
*		also a subclass of a superclass
* 
*		C++ also supports multiple inheritance, unlike in JAva. This is done through comma seperated list
*		in inheritance
* 
*			class MySubClass: public SuperClass1, public SuperClass2, public SuperClass3 {
*				...class stuff
*			}
* 
* 
* 
* 
* 
* 
* 
* 
* 
* 
* 
* 
* 
*	==================================
*		POLYMORPHISM
*	=================================
* 
*	Polymorphism gives objects ability to be represented in many forms
* 
*	Remember, protected access specifiers make child class able to access properties from superclass, but not
*	from outside
* 
*	Polymorphism is mainly achieved by:
* 
*		>	Using the base class as datatype, but the object stored is that of derived type
*		>	Overriding methods to behave kind of differently
* 
* 
* 
* 
* 
* 
* 
* 
* 
* 
* 
* 
* 
* 
* 
* 
* 
* 
* 
* 
* 
*	==================================
*		SIMPLE FILE HANDLING
*	=================================
* 
*	To handle files, we will need to include the <fstream> header library file into our program.
*	Inside fstream, there are some classes that we will need to make objects out of to read and write files
* 
*	>	ofstream				(Output File Stream)
*	>	ifstream				(Input File Stream)
*	>	fstream					(Combination)
* 
*	The constructor takes in an arguemnt which is the file path to our file
* 
*	
*	To write items into our file, we will use the Insertion Operator <<
*		
*		ifstream << "Hello World \n";
* 
* 
*	To read files, we shall use While loop along with the getline() function.
* 
*		string strVariable;
*		while ( getline( myOfstream, strVariable ) ) {			// Getline will read line from the ifstream, and
*																// store it in the strVariable, then return true
*																// or false whether it is successful
			cout << strVariable;
		}






























	==================================
*		EXCEPTION HANDLING
*	=================================
* 
*	We handle exceptions using 3 keywords like in Java:
*		> try
*		> catch
*		> throw
* 
*	If we want to catch any of the exception, use the ellipsis ...
* 
*	try {
*		int test = 15;
*		if (test > 10) {
*			throw (test);
*		}
*	} catch (...) {
*		cout << "ERROR!";
*	}
*
*	
*/


int main() {

}