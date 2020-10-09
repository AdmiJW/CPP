#pragma once


#include <vector>
#include <iostream>
#include <string>


class HotelRoom {
private:
	int bedroom_;
	int bathroom_;
public:
	HotelRoom(int bedroom, int bathroom) : bedroom_(bedroom), bathroom_(bathroom) {}
	virtual ~HotelRoom() {}				// Virtual destructor

	//	Function must be virtual in order for polymorphism to work correctly
	virtual int get_price() {		
		return 50 * bedroom_ + 100 * bathroom_;
	}
};

class HotelApartment : public HotelRoom {
public:
	HotelApartment(int bedroom, int bathroom) : HotelRoom(bedroom, bathroom) {}
	virtual ~HotelApartment() {}

	virtual int get_price() {
		return HotelRoom::get_price() + 100;
	}
};



void hotel_prices() {
	int T;
	std::cin >> T;
	std::vector<HotelRoom*> vector;
	vector.reserve(T);

	while (T--) {
		std::string type;
		std::cin >> type;
		int br, bt;
		std::cin >> br >> bt;

		if (type == "standard") {
			vector.push_back(new HotelRoom(br, bt));
		}
		else {
			vector.push_back(new HotelApartment(br, bt));
		}
	}

	int auto_profit;

	for (auto pt : vector) {
		auto_profit += pt->get_price();
		delete pt;
	}
	vector.clear();

	std::cout << auto_profit << std::endl;

}