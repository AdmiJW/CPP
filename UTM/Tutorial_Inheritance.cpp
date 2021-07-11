#include <string>
#include <iostream>
using namespace std;

//===================================
//	Name: Soh Jun Wei
//	Matric No: A20EC0151
//===================================

//	Student class
class Student {
protected:
	int SID;
	string StudentName;
	int Gender;
	int Age;
public:
	Student() {}
	Student(int id, string n, int g, int a)
		: SID(id), StudentName(n), Gender(g), Age(a) {}

	virtual void AddNewStudent(int id, string n, int g, int a) = 0;
	virtual void getStudentInfo() {
		cout << "Name: " << StudentName << endl
			<< "ID: " << SID << endl
			<< "Gender: " << Gender << endl
			<< "Age: " << Age << endl;
	}
	virtual ~Student() {
		cout << "Student " << StudentName << " destroyed" << endl;
	};
};



// UnderGradStudent
class UnderGradStudent : public Student {
	string AcademicAdvisorName;
public:
	//	Constructor must exist
	UnderGradStudent() : Student() {}
	UnderGradStudent(int id, string n, int g, int a) : Student(id, n, g, a) {}

	virtual ~UnderGradStudent() {
		cout << "UnderGradStudent " << StudentName << " destroyed" << endl;
	};

	void AssignAA(int id, string n) {
		AcademicAdvisorName = n;
	}

	void AddNewStudent(int id, string n, int g, int a) {
		SID = id;
		StudentName = n;
		Gender = g;
		Age = a;

		cout << "(OVERLOADED) Undergraduate Student " << StudentName << " Added\n\n";
	}

	void getStudentInfo() {
		Student::getStudentInfo();
		cout << "Academic Advisor: " << AcademicAdvisorName << "\n\n";
	}
};



// PostGradStudent
class PostGradStudent : public Student {
	string SupervisorName;
public:
	//	Constructor must exist
	PostGradStudent() : Student() {}
	PostGradStudent(int id, string n, int g, int a) : Student(id, n, g, a) {}

	virtual ~PostGradStudent() {
		cout << "PostGradStudent " << StudentName << " destroyed" << endl;
	};

	void AssignSV(int id, string n) {
		SupervisorName = n;
	}

	void AddNewStudent(int id, string n, int g, int a) {
		SID = id;
		StudentName = n;
		Gender = g;
		Age = a;

		cout << "(OVERLOADED) Postgraduate Student " << StudentName << " Added\n\n";
	}

	void getStudentInfo() {
		Student::getStudentInfo();
		cout << "Supervisor: " << SupervisorName << "\n\n";
	}
};

