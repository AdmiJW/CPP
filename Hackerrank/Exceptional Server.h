#pragma once



#include <iostream>
#include <string>
#include <exception>
#include <vector>
#include <cmath>


class Server {
private:
	static int load;
public:
	static int compute(long long A, long long B) {
		load += 1;
		if (A < 0) {
			throw std::invalid_argument("A is negative");	// Invalid argument exception
		}
		std::vector<int>v(A, 0);
		int real = -1, cmplx = sqrt(-1);
		if (B == 0) throw 0;			//	Exception type: other
		real = (A / B) * real;
		int ans = v.at(B);		//	May throw exception
		return real + A - B * ans;
	}
	static int getLoad() {
		return load;
	}
};
int Server::load = 0;



void exceptional_server() {
	int T;
	std::cin >> T;
	while (T--) {
		long long A, B;
		std::cin >> A >> B;

		//================================
		try {
			int res = Server::compute(A, B);
			std::cout << res << "\n";
		}
		catch ( std::bad_alloc& e ) {						//	A memory error throws an exception of std::bad_alloc
			std::cout << "Not enough memory" << "\n";
		}
		//	Standard exception is thrown. Note that we SHALL use reference or pointer
		//	to refer to the exception catched. This is because the what() method is a virtual function, meaning
		//	if we use copy constructor, the what() method will always be the base class's what() method, not the derived classes's
		catch ( std::exception& e ) {						
			std::cout << "Exception: " << e.what() << "\n";
		}
		catch (...) {
			std::cout << "Other Exception" << "\n";
		}



		//================================
	}
	std::cout << Server::getLoad() << std::endl;
}