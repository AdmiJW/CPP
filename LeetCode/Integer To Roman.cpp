#include <string>
using namespace std;

//https://leetcode.com/problems/integer-to-roman/
/*
 * 	This is a string problem, a little bit of math involved.
 *
 * 	First of all, the value can be separated into 4 parts: ones, tenths, hundreds, and thousands.
 * 	If we have a Map from value to its roman numeral representation, everything is going to be easy.
 *
 * 	------------------------------------------------------------------
 *
 * 	We can also do it logically. The only special cases is when the places value is 4 or 9. Once that
 * 	case is handled, problem is reduced to handling 5 and individual 1s only now.
 */

class Solution {
private:
	static const string map_ones[];
	static const string map_tens[];
	static const string map_hundreds[];
	static const string map_thousands[];
public:

	//	Map solution
	string intToRoman(int num) {
		int ones = num % 10;
		int tens = (num % 100) / 10;
		int hundreds = (num % 1000) / 100;
		int thousands = (num % 10000) / 1000;

		return map_thousands[thousands] + map_hundreds[hundreds] + map_tens[tens] + map_ones[ones];
	}


	//	Logical solution
	string intToRoman2(int num) {
		int ones = num % 10;
		int tens = (num % 100) / 10;
		int hundreds = (num % 1000) / 100;
		int thousands = (num % 10000) / 1000;
		string res = "";

		//	Thousands
		while (thousands-- > 0) res += 'M';

		//	Hundreds
		if (hundreds == 4) res += "CD";
		else if (hundreds == 9) res += "CM";
		else {
			if (hundreds >= 5) res += 'D';
			for (hundreds %= 5; hundreds > 0; --hundreds) res += 'C';
		}

		//	Tens
		if (tens == 4) res += "XL";
		else if (tens == 9) res += "XC";
		else {
			if (tens >= 5) res += 'L';
			for (tens %= 5; tens > 0; --tens) res += 'X';
		}

		//	Ones
		if (ones == 4) res += "IV";
		else if (ones == 9) res += "IX";
		else {
			if (ones >= 5) res += 'V';
			for (ones %= 5; ones > 0; --ones) res += 'I';
		}

		return res;
	}
};


const string Solution::map_ones[] = { "", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX" };
const string Solution::map_tens[] = { "", "X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC" };
const string Solution::map_hundreds[] = { "", "C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM" };
const string Solution::map_thousands[] = { "", "M", "MM", "MMM" };