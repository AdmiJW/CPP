
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

double calculateTotal(double test1, double assgm, double quiz, double lab, double finalExam) {
	test1 = test1 / 100 * 20;
	assgm = assgm / 100 * 30;
	quiz = quiz / 100 * 10;
	lab = lab / 100 * 10;
	finalExam = finalExam / 100 * 30;

	return test1 + assgm + quiz + lab + finalExam;
}

string assignGrade(double totalMark) {
	if (totalMark >= 90) return "A+";
	else if (totalMark >= 80) return "A";
	else if (totalMark >= 75) return "A-";
	else if (totalMark >= 70) return "B+";
	else if (totalMark >= 65) return "B";
	else if (totalMark >= 60) return "B-";
	else if (totalMark >= 55) return "C+";
	else if (totalMark >= 50) return "C";
	else if (totalMark >= 45) return "C-";
	else if (totalMark >= 40) return "D+";
	else if (totalMark >= 35) return "D";
	else if (totalMark >= 30) return "D-";
	return "E";
}

int main() {
	string name;
	double test1, assgm, quiz, lab, finalExam;
	double totalMark;
	string grade;

	cout << "Please enter Student name: ";
	cin >> name;
	cout << "Please enter Test 1 mark: ";
	cin >> test1;
	cout << "Please enter Assignment mark: ";
	cin >> assgm;
	cout << "Please enter Quiz mark: ";
	cin >> quiz;
	cout << "Please enter Lab Work mark: ";
	cin >> lab;
	cout << "Please enter final exam mark: ";
	cin >> finalExam;

	totalMark = calculateTotal(test1, assgm, quiz, lab, finalExam);

	grade = assignGrade(totalMark);

	cout << left << "\n";
	cout << setw(15) << "Student" << setw(15) << "Test 1" << setw(15) << "Assignments" << setw(15) << "Quiz" <<
		setw(15) << "Lab Works" << setw(15) << "Final Exam" << setw(15) << "Total Mark" << setw(15) << "Grade" << endl;
	cout << setw(15) << name << setw(15) << test1 << setw(15) << assgm << setw(15) << quiz << setw(15) << lab <<
		setw(15) << finalExam << setw(15) << totalMark << setw(15) << grade;

	return 0;
}