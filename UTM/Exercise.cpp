#include <string>
#include <iostream>
using namespace std;

//=================================
//	Name: Soh Jun Wei
//	M/No: A20EC0151
//=================================




//======================
//	Instructor
//======================
class Instructor {
	int ID;
	string name;
public:
	Instructor(int i, string n) : ID(i), name(n) {
		cout << "Instructor object has been created\n";
	}
	~Instructor() {
		cout << "Instructor object has been destroyed\n";
	}
	void showInfo();
};

void Instructor::showInfo() {
	cout << "** Instructor's ID: " << ID << endl;
	cout << "** Instructor's Name: " << name << endl;
}



//======================
//	Exam
//======================
class Exam {
	int ID;
	string type;
public:
	Exam(int i, string t) : ID(i), type(t) {
		cout << "Exam object has been created\n";
	}
	~Exam() {
		cout << "Exam object has been destroyed\n";
	}
	void showInfo();
};

void Exam::showInfo() {
	cout << "** Exam's ID: " << ID << endl;
	cout << "** Exam's Type: " << type << endl;
}



//================
//	Course
//================
class Course {
	int ID;
	string title;
	Instructor* cInstructor;
	Exam cExam;
public:
	Course(int i, string t, Instructor* inst, Exam e)
		:ID(i), title(t), cInstructor(inst), cExam(e)
	{
		cout << "Course object has been created\n";
	}
	~Course() {
		cout << "Course object has been destroyed\n";
	}
	void showInfo();
};

void Course::showInfo() {
	cout << "** Course ID: " << ID << endl;
	cout << "** Course Title: " << title << endl;
	cInstructor->showInfo();
	cExam.showInfo();
}



//=================
//	main
//=================
int main() {
	Instructor* i = new Instructor(100, "Johen Johnson");
	Exam e(201, "Mid-Term");
	Course c(10, "PT2", i, e);
	c.showInfo();
	return 0;
}