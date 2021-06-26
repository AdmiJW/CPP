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



int main() {
	//	Question 2
	UnderGradStudent undergrad1(1, "Adam", 1, 1);
	PostGradStudent postgrad1(2, "John", 2, 2);

	//	Question 3
	Student* studs[5];
	UnderGradStudent *u1 = new UnderGradStudent(), *u2 = new UnderGradStudent();
	PostGradStudent *p1 = new PostGradStudent(), *p2 = new PostGradStudent(), *p3 = new PostGradStudent();

	u1->AddNewStudent(200151, "Soh Jun Wei", 1, 20);
	u2->AddNewStudent(3, "Charles", 3, 3);
	u1->AssignAA(100, "Dr Mohd Razak Bin Samingan");
	u2->AssignAA(200, "Dr Peter");
	p1->AddNewStudent(4, "Dan", 4, 4);
	p2->AddNewStudent(5, "Ellie", 5, 5);
	p3->AddNewStudent(6, "Farid", 6, 6);
	p1->AssignSV(300, "Dr Zaini");
	p2->AssignSV(400, "Dr Naqib");
	p3->AssignSV(500, "Dr Mohan");

	studs[0] = u1;
	studs[1] = u2;
	studs[2] = p1;
	studs[3] = p2;
	studs[4] = p3;

	//	Question 4
	for (int i = 0; i < 5; ++i)
		studs[i]->getStudentInfo();

	//	Show virtual destructor works
	for (int i = 0; i < 5; ++i)
		delete studs[i];

	return 0;
}