#pragma once

#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>

void printPretty() {
	
	int T;
	std::cin >> T;

	while (T-- > 0) {
		double A, B, C;
		std::cin >> A >> B >> C;

		std::stringstream streamA;
		streamA << std::hex << std::showbase << static_cast<int>(A) << "\n";

		std::stringstream streamB;
		streamB << std::fixed << std::setprecision(2) << std::showpos << B;
		std::stringstream streamB2;
		streamB2 << std::setfill('_') << std::setw(15) << streamB.str() << "\n";

		std::stringstream streamC;
		streamC << std::scientific << std::uppercase << std::setprecision(9) << C << "\n";

		std::cout << streamA.str() << streamB.str() << streamC.str();
	}

}


void printPretty2() {
	int T;
	std::cin >> T;

	while (T-- > 0) {
		double A, B, C;
		std::cin >> A >> B >> C;

		//	Setting preconfig
		std::cout << std::setw(0) << std::right << std::nouppercase;

		//	Format A
		std::cout << std::hex << std::showbase << static_cast<long long int>(A) << "\n";
		
		//	Undo format A
		std::cout << std::dec << std::noshowbase;

		//	Format B
		std::cout << std::fixed << std::setprecision(2) << std::showpos << std::setfill('_') << std::setw(15)
				<< B << "\n";

		//	Undo format B
		std::cout << std::noshowpos;

		//	Format C
		std::cout << std::scientific << std::uppercase << std::setprecision(9) << C << "\n";

		//	Undo format C
		std::cout.unsetf(std::ios_base::floatfield);
		std::cout.unsetf(std::ios_base::adjustfield);
		std::cout.unsetf(std::ios_base::basefield);
	}
}