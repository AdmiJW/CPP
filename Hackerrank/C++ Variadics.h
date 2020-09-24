#pragma once

#include <iostream>
#include <string>

typedef long long int LONG;

template <bool... digits>
LONG reversed_binary_value_BYARRAY() {
	int size = sizeof...(digits);			//	We can use sizeof... ( ) to determine how many elements in the parameter pack
	bool bits[size] = { digits... };		//	Since ellipsis ... spreads the values out seperated by commas, it is basically
											//	forming a valid array
	int res = 0;

	for (int i = size - 1; i >= 0; i--) {
		res = res * 2 + bits[i];
	}

	return res;
}

//==================================================================

//	Function template
/*
*	We have to remember that function template doesn't allow Partial SPecialization at all, hence no expansion in template
*	specialization (...)
*	Using the general template <bool bit, bool... digits>, we have to define the base case where 
*	>	bit exists as it is
*	>	digits is of size 0
* 
*	Since it is non-type template, Specialization requires us to specify the EXACT value of the template, which is TRUE or FALSE
*	We will define those specialized function templates
*/

template<bool bit, bool... digits>			//General function template. Always get called 
LONG revFunc() {
	return bit + revFunc<digits...>() * 2;
}

template<>						//	Specialized function template: Called during base case 1: left with <true>
LONG revFunc<true>() {
	return 1;
}

template<>						//	Specialized function template: Called during base case 2: left with <false>
LONG revFunc<false>() {
	return 0;
}

template <bool... digits>
LONG reversed_binary_value() {
	return revFunc<digits...>();			//Since we need signature of <bool bit, bool... digits>, we can't recycle or overload
											//the same function. We need a helper function
}



//======================================================

//	CLASS/ STRUCT TEMPLATE

/*
*	What if we want the base case to be actually nothing, where there is no bit left?
*	Since function template doesn't allow for partial specialization, we need to DEFER the solution to a class (or struct),
*	this practice is common with many template programs
* 
*	The general template will take in parameter pack of digits, <bool...digits>. Now we can specialize the common case and base
*	case
*	>	Common case: <bool bit, bool... digits>
*	>	Base case:	<>
* 
*	We use a variable 'value' to store the result value, and is common practice too.
* 
*	Where in each case, the struct will store the exact VALUE represented by those bits, determined recursively in some way.
*	We shall use constexpr instead of const, as constexpr means the constant value can be evaluated at compile time, which
*	it does by using templates which is also expanded and evaluated at compile time.
*/

template <bool... digits>
struct revStruct;


template <bool bit, bool... digits>
struct revStruct<bit, digits...> {
	static constexpr LONG value = bit + revStruct<digits...>::value * 2;
};


template<>
struct revStruct<> {
	static constexpr LONG value = 0;
};

template <bool... digits>
LONG reversed_binary_value_STRUCT() {
	return revStruct<digits...>::value;
}