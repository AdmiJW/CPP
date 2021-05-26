#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

//====================================
//	Name: SOh Jun Wei
//	Matric: A20EC0151
//
//	Programaming Technique II SBT
//====================================

#define MAX_BOOK 10

//======================
//	Task 1: Name class
//======================
class Name {
	string firstName;
	string lastName;
public:
	Name() : firstName(""), lastName("") {}
	Name(string f, string l) : firstName(f), lastName(l) {}

	string getFullName() {
		return firstName + " " + lastName;
	}
};


//======================
//	Task 2: Book class
//======================
class Book {
	string name;
	string category;
	double price;
	int quantity;
public:
	Book(): name(""), category(""), price(0), quantity(0) {}
	Book(string name, string category, double price)
		:name(name), category(category), price(price) {}

	string getName() const {
		return name;
	}

	string getCategory() const {
		return category;
	}

	double getPrice() const {
		return price;
	}

	int getQuantity() const {
		return quantity;
	}

	void setQuantity(int q) {
		quantity = q;
	}
};



//======================
//	Task 3: Teacher class
//======================
class Teacher {
	Name name;
	Book* books;
	string address;
	int numBook;
public:
	Teacher(string first_name, string last_name, string addr) {
		name = Name(first_name, last_name);
		address = addr;
		numBook = 0;
		books = new Book[MAX_BOOK];
	}
	~Teacher() {
		delete[] books;
	}

	void buy(Book book, int quantity) {
		if (numBook >= MAX_BOOK) {
			cout << "Sorry!! You already reached the maximum number of books purchased.";
			return;
		}

		books[numBook] = book;
		books[numBook].setQuantity(quantity);
		++numBook;
	}

	void print() {
		cout << "Name\t: " << name.getFullName() << endl;
		cout << "Address\t: " << address << endl;
		cout << "Number of books purchased: " << numBook << "\n\n";

		double totalPrice = 0;

		cout << left << fixed << setprecision(2);

		cout << setw(5) << "No" << setw(20) << "Product Name" << setw(10) << "Category"
			<< setw(10) << "Quantity" << setw(20) << "Unit Price(RM)" << setw(20) << "Amount (RM)" << endl;

		for (int i = 0; i < numBook; ++i) {
			Book& b = books[i];
			totalPrice += (b.getQuantity() * b.getPrice());

			cout << setw(5) << (i+1) << setw(20) << b.getName() << setw(10) << b.getCategory()
				<< setw(10) << b.getQuantity()  << setw(20) << b.getPrice() << setw(20) << b.getQuantity() * b.getPrice() << endl;
		}

		cout << "\nTotal Price = RM " << totalPrice << endl;
	}
};


int main() {
	Teacher teach("Fatah", "Amin", "Muar, Johor");
	Book b1("Mathematic", "Exercise", 7.8);
	Book b2("Biology", "Textbook", 12.5);
	Book b3("Physic", "Textbook", 18.4);
	Book b4("Chemistry", "Exercise", 8.9);
	teach.buy(b4, 10);
	teach.buy(b2, 13);
	teach.buy(b3, 15);
	teach.buy(b1, 11);
	teach.print();
	return 0;
}
