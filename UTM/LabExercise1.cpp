#include <iostream>


void q15() {
	std::cout << "Question 15\n";

	// Fixed rate MYR to Turkish Lira
	const double MYR_TO_TRY = 0.5997;
	
	//	Obtain user input of the Malaysian Ringgit to be converted to Turkish_Lira
	double MYR;
	std::cout << "Enter the MYR amount to be converted to Turkish Lira: ";
	std::cin >> MYR;

	//	Convert MYR input to Turkish Lira
	double turkish_Lira = MYR * MYR_TO_TRY;

	//	Output the converted Turkish Lira
	std::cout << "RM" << MYR << " Converted to TUrkish Lira is " << turkish_Lira << "\n";
}


void q16() {
	std::cout << "Question 16\n";

	//	Obtain user input of the Minutes to be converted into Days, Hours and Minutes
	int total_Time;
	std::cout << "Enter the total time in minutes: ";
	std::cin >> total_Time;

	/*
		Calculate the Days, Hours and Minutes
		This is done by first dividing the input Minutes with (60 min * 24 hr)
		Obtain the remaining time using modulus operation, and obtain the hours by dividing the result with 60 min
		Obtain the remain_Time once again, then obtain the minutes using modulus operation
	*/
	int day = total_Time / (60 * 24);
	int remain_Time = total_Time % (60 * 24);
	int hour = remain_Time / 60;
	remain_Time %= 60;
	int minutes = remain_Time % 60;

	//	Output the converted Days, Hours and Minutes
	std::cout << "The time converted is: " << "\n";
	std::cout << day << " Day(s) " << hour << " Hour(s) " << minutes << " Minute(s)\n";
}


void q17() {
	std::cout << "Question 17\n";

	//	Fixed value of length and width
	const double length = 2.5;
	const double width = 15.3;

	//	Calculate the area based on value of length and width
	double area = length * width;

	//	Output the calculated area of the rectangle
	std::cout << "Area of the rectangle is " << area << "\n";
}



void q18() {
	std::cout << "Question 18\n";

	//	Fixed values of UnitSale, PricerPerUnit, CostPerUnit
	const int UnitSale = 1500;
	const double PricePerUnit = 20.00;
	const double CostPerUnit = 15.00;

	//	Calculate the TotalCost and TotalSale. THen, calculate TotalProfit based on previous calculation
	double TotalCost = UnitSale * CostPerUnit;
	double TotalSale = UnitSale * PricePerUnit;
	double TotalProfit = TotalSale - TotalCost;

	//	Output the calculated profit of the sales
	std::cout << "Net Profit is: " << TotalProfit << "\n";
}



void q19() {
	std::cout << "Question 19\n";

	//	Obtain user input value of Fahrenheit to be converted into Celcius
	double fahrenheit;
	std::cout << "Please input the value of Fahrenheit to Convert to Celcius: ";
	std::cin >> fahrenheit;

	//	Calculate the value of Celcius from the user input Fahrenheit
	double celcius = (fahrenheit - 32) * (5.0 / 9);

	//	Output the converted Celcius value
	std::cout << fahrenheit << " Fahrenheit converted to celcius is: " << celcius << "\n";
}



