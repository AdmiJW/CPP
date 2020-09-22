#pragma once

#include <iostream>
#include <string>

using namespace std;


struct Student {
	int age, standard;
	string first_name, last_name;
};


void Struct() {

	Student st;

	cin >> st.age >> st.first_name >> st.last_name >> st.standard;

	printf("%d %s %s %d", st.age, st.first_name.c_str(), st.last_name.c_str(), st.standard);

}