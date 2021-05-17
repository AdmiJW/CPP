
#include <string>
#include <iostream>

using namespace std;

/*
*	INHERITANCE
* 
*	To perform inheritance from a base class into a derived class, which the derived class inherits all the member
*	variables and methods from the base class, use the following syntax:
*	
*		class Derived: public Base {
*			...
*		}
* 
*	The 'public' is an access modifier which can be specified when performing inheritance:
*		public		>	All members of the base class remain the same visibility. Private members in base class
*						still isn't accessible in the derived class
*		protected	>	Public and protected members in the base class will become protected in the derived class
*		private		>	All members of the base class will become private members in derived class
*		
*	If we don't specity the access modifier, like
*		
*		class Derived: Base { ... }
* 
*	It will default to private
* 
*	
*	Those stuffs are not inherited. We could not call them like other members of base class:
*		>	Constructor & Destructor
*		>	Overloaded operator functions 
*		>	Friend function declararions
* 
*	
*	The order in which constructor and destructor are called is as follows:
*			
*		Base Constructor > Derived Constructor -----------> Derived Destructor > Base Destructor
* 
* 
* 
*	By default, when an object of derived class is instantiated, the default constructor of the base class is called.
*	(Of course it will throw error if in base class there is no default constructor)
*	To change to another constructor in the base class, we need to call that constructor in the constructor
*	initializer list in the derived class constructor
* 
*		DerivedClassConstructor(int a): BaseClassConstructor(a) {...}
*/


class Animal {
	string sound;

public:
	Animal(): sound("") {}
	Animal(string sound) : sound(sound) {}

	void makeSound() {
		cout << this->sound << endl;
	}
};


class Bird : public Animal {

public:
	Bird() : Animal() {}
	Bird(string sound) : Animal(sound) {}

	void fly() {
		cout << "Bird is flying... " << endl;
		makeSound();
	}
};


void CS5_inheritance() {
	Bird bird("Gawk");
	bird.fly();
	bird.makeSound();
}
















/*
*	POLYMORPHISM
* 
*	Polymorphism basically means that a call to member function will cause different implementation to be executed
*	depending on the type of object (Which class) that invokes the function.
*	
	This is mainly done through function overriding and virtual functions
*	Also, polymorphism allows a pointer to store different instances of different derived classes
* 
* 
* 
* 
*	VIRTUAL FUNCTIONS
* 
*	When we declare a function as 'virtual' (especially in base class), when the classes are compiled, the 
	compiler will create what is called	as Vtable, which stores the different implementations of the same function
	in different derived classes.

	Without virtual functions being declared, the compiler calls the implementation of the function based on the
	type of pointer which stores the instance.
	Eg:
		Base* obj = new Derived();
		obj->func();
	Here the implementation of func() called is that in the Base classes, not the one overridden in Derived.

	With declaration of virtual function, the compiler will actually check and compare the actual instance of
	the object, and call the correct implementation of the function, not by the pointer type

	>	Using pointers is said to be more efficient because it directly points to the memory location. Using variable
		names on the other hand means compiler has to search for the corresponding memory location storing the data
		first

	>	It is said to be good practice to declare the pointers in Base class. This is because the exact pointer
		can be set to another instance of another derived class easily, and even though those are differnent
		classes, they can be easily stored in data structures like an array etc.

		Eg of Java:
			List<Integer> li = new ArrayList<>();
			li = new LinkedList<>();


	In short, by default compiler will always choose implementations based on the pointer type. Now, with
	virtual functions, compiler will check the actual instance of the class pointed by the pointer to select
	the proper, overridden method

	----------------------------------------------------------------------------------------------------

	The same goes with destructors (but not constructors, as to construct an object we need exact type). Without virtual,
	destructors get called based on the pointer type and not on its actual class, which can easily lead to memory leak!!!
*	
*/

class Enemy {
protected:
	int power;
public:
	Enemy(int power = 0) : power(power) {}
	virtual ~Enemy() {}			//Virtual destructor because different classes might allocate different memories.

	virtual void attack() {
		cout << "Enemy dealt " << power << " damage!" << endl;
	}
};

class Monster : public Enemy {
public:
	Monster(int power = 0) : Enemy(power) {}

	void attack() {
		cout << "Monster dealt " << power << " damage!" << endl;
	}
};

class Mafia : public Enemy {
public:
	Mafia(int power = 0) : Enemy(power) {}

	void attack() {
		cout << "Mafia dealt " << power << " damage!" << endl;
	}
};

void CS5_polymorphism() {
	Enemy* enemies[3];
	enemies[0] = new Enemy(50);
	enemies[1] = new Monster(100);
	enemies[2] = new Mafia(200);

	for (int i = 0; i < 3; i++) {
		enemies[i]->Enemy::attack();		//	Will still call the base class's implementation of attack
		enemies[i]->attack();				//	Since VTable is set up, although the pointer is of type Enemy,
											//	it will call the correct implementation based on the actual instance
	}

	for (int i = 0; i < 3; i++) {
		delete enemies[i];
	}
}























/*
*	ABSTRACT CLASSES
* 
*	Maybe we don't have a meaningful implementation of a virtual function in the base class. Maybe you don't
*	want anyone to instantiate an instance of the base class. The base class's purpose is just to used as pointer
*	to point to instances of the derived class.
* 
*	In that case, that base class is called abstract class, which is a lot like interfaces and abstract classes in
*	Java.
*	
*	To create abstract classes, we don't need any special keyword. All we need is a PURE VIRTUAL FUNCTION
*	in the class, which is a virtual function that don't have any body definitions for it.
* 
*	Syntax:
*		virtual void func() = 0;
* 
*	Note that we kinda assign the function to 0. What this does is telling the compiler that this virtual function
*	has no body, which is PURE VIRTUAL FUNCTIONS.
* 
*	Now the compiler knows that
*	>	All derived class must have this function implemented. Derived class must override the function. Otherwise
*		compiler will just throw an error
*	>	This class is no longer instantiable. We can't create objects out of this class anymore, just like how we
*		can't instantiate abstract classes and interfaces in Java
*/


class Enemy2 {
protected:
	int power;
public:
	Enemy2(int power) : power(power) {}
	virtual ~Enemy2() {}
	virtual void attack() = 0;
};

class Monster2: public Enemy2 {
public:
	Monster2(int power) : Enemy2(power) {}
	void attack() override {				//	Use of override keyword to show overridden method
		cout << "It's Monster's turn" << endl;
		cout << "Monster dealt " << power << " damage!" << endl;
	}
};

class Mafia2 : public Enemy2 {
public:
	Mafia2(int power) : Enemy2(power) {}
	void attack() override {
		cout << "It's Mafia's turn" << endl;
		cout << "Mafia dealt " << power << " damage!" << endl;
	}
};

#include <cstdarg>	//	Use to able to use ellipsis ... in argument
void CS5_abstractClass() {

	//	Enemy2* enem = new Enemy2(50);			// Error. Trying to instantiate abstract class

	Enemy2* arr[2];
	arr[0] = new Monster2(100);
	arr[1] = new Mafia2(200);

	for (Enemy2* pt : arr) {
		pt->attack();
		delete pt;
	}

	*arr = NULL;

}