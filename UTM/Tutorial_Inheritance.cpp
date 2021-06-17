#include <string>
#include <iostream>
using namespace std;

//===================================
//	Name: Soh Jun Wei
//	Matric No: A20EC0151
//===================================

//	Student class
class Student {
	int SID;
	string StudentName;
	int Gender;
	int Age;
public:
	Student() {}
	Student(int id, string n, int g, int a)
		:SID(id), StudentName(n), Gender(g), Age(a) {}

	void AddNewStudent (int id, string n, int g, int a) {
		SID = id;
		StudentName = n;
		Gender = g;
		Age = a;
	}

	virtual void getStudentInfo() {
		cout << "Student ID: " << SID << "\n" <<
			"Name: " << StudentName << "\n" <<
			"Gender: " << Gender << "\n" <<
			"Age: " << Age << "\n";
	}
};



// UnderGradStudent
class UnderGradStudent: public Student {
	string AcademicAdvisorName;
public:
	//	Constructor must exist
	UnderGradStudent() : Student() {}
	UnderGradStudent(int id, string n, int g, int a) : Student(id, n, g, a) {}

	void AssignAA(int id, string n) {
		AcademicAdvisorName = n;
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

	void AssignSV(int id, string n) {
		SupervisorName = n;
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
	UnderGradStudent u1, u2;
	PostGradStudent p1, p2, p3;

	u1.AddNewStudent(200151, "Soh Jun Wei", 1, 20);
	u2.AddNewStudent(3, "Charles", 3, 3);
	u1.AssignAA(100, "Dr Mohd Razak Bin Samingan");
	u2.AssignAA(200, "Dr Peter");
	p1.AddNewStudent(4, "Dan", 4, 4);
	p2.AddNewStudent(5, "Ellie", 5, 5);
	p3.AddNewStudent(6, "Farid", 6, 6);
	p1.AssignSV(300, "Dr Zaini");
	p2.AssignSV(400, "Dr Naqib");
	p3.AssignSV(500, "Dr Mohan");

	Student* studs[5];
	studs[0] = &u1;
	studs[1] = &u2;
	studs[2] = &p1;
	studs[3] = &p2;
	studs[4] = &p3;

	//	Question 4
	for (int i = 0; i < 5; ++i)
		studs[i]->getStudentInfo();

	return 0;
}