////////////////////////////////////////////////////////////////////////////////
// School of Computing, Universiti Teknologi Malaysia
// SECJ/SCSJ1023 - Programming Technique II
// Semester 2, 2020/2021
// Final Exam, Problem Solving
// Student's Name: Soh Jun Wei
// Matric Number: A20EC0151
////////////////////////////////////////////////////////////////////////////////

// Code written by Adib Zaini
// Song: NEGARAKU (National Anthem of Malaysia)

// NOTE: Some Sleep() functions used to smooth the beep functions
//		 Some other just to wait

#include <iostream>
#include <windows.h> // For using Beep()

using namespace std;

int main()
{
	Sleep(1000);
	cout << "NEGARAKU (Lagu Kebangsaan Negara Malaysia)" << endl << endl;
	Beep(0, 1000); // To make next Beep() fast

	cout << "Ne";
	Beep(300, 800);

	cout << "ga";
	Beep(300, 800);

	cout << "ra";
	Beep(800, 800);

	Sleep(100);
	cout << "ku";
	Beep(600, 2100);
	Sleep(500);

	cout << endl;

	cout << "Ta";
	Beep(600, 800);

	cout << "nah";
	Beep(600, 800);

	cout << " ";

	cout << "Tum";
	Beep(1000, 800);

	cout << "pah";
	Beep(800, 800);

	cout << "nya";
	Beep(500, 800);

	cout << " ";

	Sleep(100);
	cout << "Da";
	Beep(500, 1200);

	cout << "rah";
	Beep(600, 400);

	Sleep(100);
	cout << "ku";
	Beep(700, 1600);
	Sleep(1000);

	cout << endl;

	cout << "Rak";
	Beep(300, 800);

	cout << "yat";
	Beep(500, 800);

	cout << " ";

	cout << "Hi";
	Beep(600, 800);

	Sleep(100);
	cout << "dup";
	Beep(700, 1600);
	Sleep(500);

	cout << endl;

	cout << "Ber";
	Beep(800, 800);

	cout << "sa";
	Beep(900, 800);

	cout << "tu";
	Beep(1200, 800);

	cout << " ";

	Sleep(100);
	cout << "dan";
	Beep(1000, 1000);

	cout << " ";

	cout << "Ma";
	Beep(900, 400);

	Sleep(100);
	cout << "ju";
	Beep(800, 1600);
	Sleep(500);

	cout << endl;

	for (int i = 0; i < 2; i++)
	{
		cout << "Rah";
		Beep(300, 800);

		cout << "mat";
		Beep(600, 800);

		cout << " ";

		cout << "Bah";
		Beep(800, 800);

		cout << "gia";
		Beep(1000, 1600);
		Sleep(500);

		cout << endl;

		cout << "Tu";
		Beep(800, 800);

		cout << "han";
		Beep(900, 1200);

		cout << " ";

		cout << "Kur";
		Beep(800, 400);

		cout << "ni";
		Beep(900, 800);

		cout << "a";
		Beep(1000, 800);

		Sleep(100);
		cout << "kan";
		Beep(1100, 1600);
		Sleep(500);

		cout << endl;

		cout << "Ra";
		Beep(700, 800);

		cout << "ja";
		Beep(900, 800);

		cout << " ";

		cout << "Ki";
		Beep(1100, 800);

		Sleep(100);
		cout << "ta";
		Beep(1000, 1000);
		Sleep(500);

		cout << endl;

		cout << "Se";
		Beep(800, 800);

		cout << "la";
		Beep(1000, 800);

		cout << "mat";
		Beep(900, 800);

		cout << " ";

		Sleep(100);
		cout << "Ber";
		Beep(900, 1000);

		cout << "takh";
		Beep(870, 400);

		Sleep(100);
		cout << "ta";
		Beep(800, 1600);
		Sleep(500);

		cout << endl;
	}

	system("cls");

	cout << "\n\n\n\n\n\n\n\n\n\n";
	cout << "terima kasih" << endl;
	cout << "\n\n\n\n\n\n\n\n\n\n";

	return 0;
}

