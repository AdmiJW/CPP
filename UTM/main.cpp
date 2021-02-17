/*==================================
//	NAME: SOH JUN WEI
//	MATRIC: A20EC0151
//	SECTION: 08
//	LECT: DR.ADILA FIRDAUS BINTI ARBAIN
===================================*/


#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <cmath>
#include <cstring>
using namespace std;


int main()
{
    char name[10][40];
    int cnt = 0;
    fstream inputfile, outputfile;


    inputfile.open("input.txt");

    outputfile.open("output.txt",ios::out);

    //c) Check for successful opening file (2 marks)
    if (!inputfile.is_open() ) {
        cout << "ERROR!! Input file could not be opened\n";
        return 0;
    }

    //d) Read data from the input file (4 marks)
    do {
        inputfile.getline(name[cnt], 40);
        cnt++;
    } while (!inputfile.eof());

    //e) Write data to the output file (3 marks)
    for (int i = cnt - 2; i >= 0; i--)
        outputfile << setw(12) << name[i] << endl;

    inputfile.close();
    outputfile.close();

    return 0;
}