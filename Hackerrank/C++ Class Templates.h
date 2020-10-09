#pragma once


#include <iostream>
#include <string>


// Template class
template <typename T>
class AddElements {
private:
    T a;
public:
    AddElements(T& a) : a(a) {}

    //  Template function as class method
    T add(T& b) {
        return a + b;
    }
};


//  Template specialization
template<>
class AddElements<std::string> {
private:
    std::string str;
public:
    AddElements(std::string& str) : str(str) {}

    std::string concatenate(std::string& str2) {
        return str + str2;
    }
};


int start_up() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    return 0;
}

int static r = start_up();