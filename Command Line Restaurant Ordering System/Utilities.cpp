#include <string>
#include <iostream>
#include <fstream>

#ifndef PRINT(X)
	#define PRINT(X) std::cout << X
#endif

#ifndef PRINTLN(X)
	#define PRINTLN(X) std::cout << X << std::endl
#endif

#ifndef BREAKLINE
	#define BREAKLINE std::cout << '\n'
#endif


int obtainUserChoice( int lowerBound = 0, int upperBound = 1, const std::string& prompt = "Please enter your choice: " ) {
	int choice;
	std::string dump;
	
	PRINT('\n' << prompt);
	std::cin >> choice;
	
	while (choice < lowerBound || choice > upperBound) {
		PRINTLN("Invalid Input. Valid input only ranges from " << lowerBound << " to " << upperBound);
		PRINT('\n' << prompt);

		std::cin.clear();					//	If invalid input, the cin fail() will set to true. Clear it to proceed
		std::cin.ignore(INT32_MAX, '\n');	//	Ignore all characters until newline character
		std::cin >> choice;
	}

	std::cin.ignore(INT32_MAX, '\n');	//Valid input but \n left in the input buffer.
	PRINT('\n');
	return choice;
}


std::ifstream getReadFileBuffer( const std::string& filePath ) {
	std::ifstream f;
	f.open(filePath);

	if (!f) {
		std::string err = "Unable to read file from location: ";
		err += filePath;
		err += "!\n";
		throw err;
	}
	return f;
}


std::ofstream getWriteFileBuffer(const std::string& filePath) {
	std::ofstream f;
	f.open(filePath);

	if (f.fail()) {
		std::string err = "Unable to open/create file from location: ";
		err += filePath;
		err += "!\n";
		throw err;
	}
	return f;
}


std::fstream getFileBuffer(const std::string& filePath) {
	std::fstream f;
	f.open(filePath, std::ios_base::app);

	if (f.fail()) {
		std::string err = "Unable to open/create file from location: ";
		err += filePath;
		err += "!\n";
		throw err;
	}
	return f;
}


void pressEnterToContinue( const std::string& prompt = "Press Enter to continue... ") {
	PRINT(prompt);
	std::cin.ignore(INT32_MAX, '\n');
	PRINTLN("");
}