/*
Assignment 4
________________________________________________________
Group Member:
			  Soh Jun Wei 						- A20EC0151
			  Muhammad Naim 					- A20EC0096
			  Ethan Leong Yi Thian 				- A20EC0033
________________________________________________________
Section     : 08
Group       : 07
Case Study  : 06
Lecturer	: Dr.Adila Firdaus binti Arbain
*/



#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>
#include <string>
#include <cstring>
#include <cstdlib>
#include <stdlib.h>

using namespace std;

// function prototype
double** getInputFile(int&);
double** make2DDoubleArray(int, int);
bool** make2DBoolArray(int, int);
void delete2DDoubleArray(double**, int);
void delete2DBoolArray(bool**, int);
void getAverage(double*);
void getHighest(double*);
void checkFlood(double**, bool**, bool**, int);
void checkDraught(double**, bool**, bool**, int);
void outputFile(bool**, bool**, int);
string getStatus(bool*, bool*);
string getList(bool*);





int main()
{
	int noOfWeeks = 0;
	//calling function to input the file

	double** weeks = getInputFile(noOfWeeks);
	bool** isFlood = make2DBoolArray(noOfWeeks, 7);
	bool** isDraught = make2DBoolArray(noOfWeeks, 7);
	bool** isOverflow = make2DBoolArray(noOfWeeks, 7);


	//calling function to check flood and draught
	checkFlood(weeks, isFlood, isOverflow, noOfWeeks);
	checkDraught(weeks, isDraught, isOverflow, noOfWeeks);

	//display week with its average rain amount, day of highest rain amount and highest rain amount in the week 
	for (int i = 0; i < noOfWeeks; ++i)
	{
		cout << "Week #" << i + 1 << endl;
		getAverage(weeks[i]);
		getHighest(weeks[i]);
		cout << endl;
	}

	cout << "Status, Flood and Drought Successfully written to output form!";
	//calling function to output the file
	outputFile(isFlood, isDraught, noOfWeeks);

	delete2DDoubleArray(weeks, 7);
	delete2DBoolArray(isFlood, 7);
	delete2DBoolArray(isDraught, 7);
	delete2DBoolArray(isOverflow, 7);

	return 0;
}



// function which input the file and copy data from file
double** getInputFile(int& noOfWeeks) {
	ifstream infile;
	infile.open("CS6.txt");//open the file "CS6.txt" 
	string line;
	int temp;

	while (!infile.eof()) {
		getline(infile, line);
		noOfWeeks++;
	}

	double** rainAmounts = make2DDoubleArray(noOfWeeks, 7);
	infile.close();
	infile.open("CS6.txt");

	for (int i = 0; i < noOfWeeks; i++)
	{
		infile >> temp;	//discard week number
		for (int x = 0; x < 7; x++)
			infile >> rainAmounts[i][x];
	}

	return rainAmounts;
}



double** make2DDoubleArray(int row, int col) {
	double** arr2d = new double* [row];
	for (int i = 0; i < row; ++i)
		arr2d[i] = new double[col];


	return arr2d;
}



bool** make2DBoolArray(int row, int col) {
	bool** arr2d = new bool* [row];
	for (int i = 0; i < row; ++i)
		arr2d[i] = new bool[col];

	return arr2d;
}



void delete2DDoubleArray(double** toDel, int row) {
	for (int i = 0; i < row; ++i)
		delete[] toDel[i];
	delete[] toDel;
}



void delete2DBoolArray(bool** toDel, int row) {
	for (int i = 0; i < row; ++i)
		delete[] toDel[i];
	delete[] toDel;
}



// function which calculate the average rain amount of the week
void getAverage(double* week)
{
	double sum = 0;
	for (int j = 0; j < 7; j++)
		sum += week[j];
	double averageRain = sum / 7.0;
	cout << "Average amount is " << averageRain << ".\n";
}



// function which determine the highest rain amount and the day of highest rain amount of the week
void getHighest(double* week)
{
	double highest = week[0];
	for (int i = 1; i < 7; ++i)
		if (highest < week[i])
			highest = week[i];

	cout << "The highest rain amount is " << highest << ".\n";

	cout << "The highest amount of rain occurred at day:";
	for (int i = 0; i < 7; ++i)
		if (week[i] == highest)
			cout << " " << i + 1;
	cout << ".\n";
}



//function which check whether there are rain amount that overflow to determine is there a flood occur
//function which determine is there any overflow by using array named isOverflow - TRUE=overflow,FALSE=no flood 
//function which determine how many flood occured by using array named isFlood - TRUE=flood,FALSE=no flood 
void checkFlood(double** week, bool** isFlood, bool** isOverflow, int noOfWeek)
{
	for (int n = 0; n < noOfWeek; n++)
	{
		double overflow = 0;

		for (int i = 0; i < 7; ++i)
		{
			if (overflow > 0)
				isOverflow[n][i] = true;
			else
				isOverflow[n][i] = false;

			//determine overflow and flood and store in array named isOverflow and isFlood 
			if (week[n][i] + overflow > 230)
			{
				isFlood[n][i] = true;//flood
				overflow = week[n][i] + overflow - 230;
			}
			else
			{
				overflow = 0;
				isFlood[n][i] = false;//no flood
			}
		}
	}
}



//function which check whether there are rain amount that overflow to determine is there a flood occur
//function which determine is draught occur by using array named isDraught - TRUE=draught , FALSE=no draught  
void checkDraught(double** week, bool** isDraught, bool** isOverflow, int noOfWeek)
{
	for (int n = 0; n < noOfWeek; n++)
	{
		isDraught[n][0] = false;
		isDraught[n][1] = false;

		for (int i = 2; i < 7; i++)
			if (week[n][i] + week[n][i - 1] + week[n][i - 2] == 0 && isOverflow[n][i] + isOverflow[n][i - 1] + isOverflow[n][i - 2] == 0)
			{
				isDraught[n][i] = true;
				isDraught[n][i - 1] = true;
				isDraught[n][i - 2] = true;
			}
			else isDraught[n][i] = false;
	}
}



// function which output the file and send data to output file
void outputFile(bool** isFlood, bool** isDraught, int noOfWeek)
{
	ofstream outfile;
	outfile.open("Output_Form.txt");//open new file name "Output_Form.txt"
	outfile << setw(6) << left << "Week" << setw(30) << "Status" << setw(14) << "Flood(Day)" << "Drought." << endl;//set up heading style in "Output_Form.txt" 

	for (int n = 0; n < noOfWeek; n++)
	{
		outfile << setw(6) << n + 1;//send data 1,2,3... align with "Week" in the header
		outfile << setw(30) << getStatus(isFlood[n], isDraught[n]);//send data status align with "Status" in the header

		/*
			calling getList with argument (isFlood[n]) mean day of flood and (isDraught[n]) mean day of draught
		*/
		outfile << setw(14) << getList(isFlood[n]);//send data flood day align with "Flood(Day)" in the header
		outfile << getList(isDraught[n]);//send data draught day align with "Draught" in the header
		outfile << endl;
	}
}



//to determine how many day flood and is there a draught for a week to be display in align with "Status" header
string getStatus(bool* isFlood, bool* isDraught)
{
	int fldcount = 0;
	int drcount = 0;
	string str = "";
	char temp[5];

	//determine how many flood and draught
	for (int i = 0; i < 7; i++)
	{
		fldcount += isFlood[i];
		drcount += isDraught[i];
	}

	//display the status in string type
	if (drcount > 0)
		//convert number of flood(int type) to number of flood(string type), then the string as added together
		str = "Drought and " + static_cast<string>(itoa(fldcount, temp, 10)) + " day(s) Flood";
	else
		str = "No Drought and " + static_cast<string>(itoa(fldcount, temp, 10)) + " day(s) Flood";

	return str;
}



//to determine which day occur flood and draught for a week to be display in align with "Flood(Day)" or "Draught" header based on parameter passed
string getList(bool* boolArray)
{
	string str;
	char temp[5];
	int i;
	for (i = 0; i < 7; i++)
	{
		//display the first flood day or draught day 
		if (boolArray[i])
		{
			str = static_cast<string>(itoa(i + 1, temp, 10));//convert the day(int type) to day(string type) for display
			break;
		}
		else
			str = "-";
	}

	//display the following flood day or draught day
	for (i = i + 1; i < 7; i++)
		if (boolArray[i])
			str += "," + static_cast<string>(itoa(i + 1, temp, 10));//display "," then convert the day(int type) to day(string type) for display

	return str;
}
