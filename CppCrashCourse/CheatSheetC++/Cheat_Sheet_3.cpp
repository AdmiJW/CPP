#include <iostream>
#include <string>
using namespace std;


/*
	====================================
		Structured Data
	====================================

	A valid C code is valid code in C++. Before C++ had classes, C had 'struct', which is kind of similar to classes except
	that
		>	Everything is publicly accessible, unlike classes which are private by default
		>	No overhead costs. How many variables you declare, that's exactly how much memory taken (Except empty struct, which must at least
			1 byte)
		>	Struct doesn't support polymorphism and inheritance

	Note that structures can be initialized using array initialization syntax, like

		MyVector a = { 1,2,3 }

	--------------------------------------------------

	Again, be careful when passing by value into parameter. It calls copy constructor (Details see topic below), and is an expensive operation.
	Pass by reference is faster, but risk of mutating. So, safest way is to pass by CONST reference.
*/






/*
	==================================
		TYPE PUNNING
	==================================

	Unlike Java, which deals with type system enforcement VERY SERIOUSLY, C++ is kind of low level, letting us access the memory directly
	and therefore, although the type system does exist, we can bypass it with adequate knowledge equipped.

	The type punning is a technique that let us take the memory content of one variable, and access it like other datatypes. For more clarify,
	see:

		int a = 50;				
		double b = a;

	In memory, variable a is represented as 32 00 00 00
	When a is assigned to b, C++ automatically converted the memory of a to double type so the value still persists as 50.
	As result, b memory content is '00 00 00 00 00 00 49 40'

	What if we want the memory content of b be same as a? Like '32 00 00 00 ?? ?? ?? ??'
	Type punning does the job!


		int a = 50;
		double b = *(double*)&a;

	It may seem confusing. Let's see one by one:
		&a					->	Gets the memory address of a with content '32 00 00 00'
		(double*)&a			->	C type cast the address as a double pointer.
		*					->	Now, dereference the 'casted double pointer' back to its value
		
	Now, the memory content of b shall look exactly like the one in a. Except that 'a' takes up 4 bytes, and 'b' uses 8 bytes. It is going
	to have 4 bytes of extra garbage value

	------------------------------------------------------------------------

	Overall, type punning is mainly used when we want to 'memory cast' something into another type. However, practice
	cautious when using it, as it may be unintuitive and hard to read. Probably there is a better way to doing things?
*/

void CS3_typePunning() {
	
	int a = 50;						//	32 00 00 00
	double b = *(double*)&a;		//	32 00 00 00 ?? ?? ?? ??		

	cout << "a is: " << a << endl;
	cout << "b is: " << b << endl;
}









/*
	=====================================
		Unions
	=====================================

	Unions, as I like to put it, is simply a way to access some data in memory using different identifiers, as well as different types.
	It can even be said is the easier version of type punning?

	Basically, everything in a Union, ALL REFERENCE TO THE SAME BLOCK OF MEMORY! See exmaple:

	union {
		int a, float b, char c;
	}

	When a, b and c are accessed, they are all referring to the same block of memory! Therefore, if value of a changes, b and c will as well!



	====================================
		Exmaple Use Cases
	====================================

	As stated in TheCherno's videos, say we have a struct of data containing 4 int elements. We may want to treat it as array of 4, 
	a struct of 2 elements, or just each variable individually. We can do so!
*/


void CS3_unions() {
	union {
		int a; float b; char c;
	};

	a = 50;

	cout << "a is: " << a << endl;				// All of them reference to same memory location, although treated differently
	cout << "b is: " << b << endl;				
	cout << "c is: " << c << endl;
}



void CS3_unions2() {
	struct Vector4D {
		int a, b, c, d;
	};

	struct Vector2D {
		int x, y;
	};

	union {
		Vector4D vector4D;						//	Treat it as Vector4D Object

		struct {
			Vector2D vector2D_1, vector2D_2;	//	Treat it as 2x Vector2D Object
		};

		struct {
			int a, b, c, d;						//	Treat each element individually
		};

		int arr[4];								//	Treat it as array
	};

	//	Setting values
	vector4D = { 2,4,6,8 };

	//	Accessing value!
	cout << vector4D.a << endl;
	cout << vector4D.b << endl;
	cout << vector4D.c << endl;
	cout << vector4D.d << endl;

	cout << vector2D_1.x << endl;
	cout << vector2D_1.y << endl;
	cout << vector2D_2.x << endl;
	cout << vector2D_2.y << endl;

	cout << a << endl;
	cout << b << endl;
	cout << c << endl;
	cout << d << endl;

	cout << arr[0] << endl;
	cout << arr[1] << endl;
	cout << arr[2] << endl;
	cout << arr[3] << endl;
}















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
*		COPY CONSTRUCTORS
*	=================================
*	
*	In C++, whenever we assgin an object to another one, it COPIES it entirely. It will create a new object, copy all the 
*	members of the original object into the new object.
* 
*	Entity e1;
*	Entity e2 = e1;		//	This will create a new object that is exact copy of e1.
* 
*	Copying is time consuming and space consuming as well. To avoid copying, use references or pointers instead. This way
*	the one thing that gets copied is the pointer or reference, not the actual object itself.
* 
*	C++ provides us a copy constructor, which has the signature like so:
* 
*			<className> (const <className>& other) { ... }
*	When we copies stuff, it's undeniable that we have to call the constructor of the object. What copy constructor allows us to
*	do is basically determine what has to be copied and what's shall not
*	It is called when we use an assignment operator (=) on another object of the same type
* 
*	For objects that we don't want to be copied, we can disable the copy constructor, by assigning it to the 'delete' keyword
* 
*			<className> (const <className>& ohter) = delete;
* 
*	The default copy constructor only performs a shallow copy. If we want to do a deep copy, consider to write our own copy
*	constructor.
* 
*/


void CS3_copyConstructor() {

	class Entity {
	public:
		int* arr = new int[3];			//When it is copied normally, only pointer gets copied into new copied object

		Entity(int x, int y, int z) {
			arr[0] = x;
			arr[1] = y;
			arr[2] = z;
		}

		//	Here copy constructor is used so the array copied is not the same. In it we still write it as it is a normal constructor
		Entity(const Entity& other) {
			arr[0] = other.arr[0];
			arr[1] = other.arr[1];
			arr[2] = other.arr[2];
		}

		//	Prints content of array
		void printArr() {
			std::cout << arr[0] << " " << arr[1] << " " << arr[2] << std::endl;
		}
	};



	Entity e1 = Entity(1, 2, 3);
	Entity e2 = e1;		//Copy constructor will be called

	e1.arr[1] = 5;

	e1.printArr();		//1, 5, 3

	e2.printArr();		//1, 2, 3

}










/* ==================================
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
*	'throw' throws an exception manually when specified by us. We can throw anything, like a integer, double, or string.
*	
*	'try' identified a block of code that may activate specific exceptions. It will be followed by one or more 'catch'
*	blocks
* 
*	We specify what exception that we will be catching by using exception declaration in parenthesis of the 'catch'
*	block, after the keyword itself
*
*	If we want to catch any of the exception, use the ellipsis ..., which is defined in the <cstdarg> header file
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
