#pragma once

#include <iostream>
#include <string>

using namespace std;


class A {
	int callA;
public:
	A() : callA(0) {}
	void inc() {
		callA++;
	}
	int getA() {
		return callA;
	}
protected:
	void func(int& a) {
		a *= 2;
		inc();
	}
};


class B {
	int callB;
public:
	B() : callB(0) {}
	void inc() {
		callB++;
	}
	int getB() {
		return callB;
	}
protected:
	void func(int& b) {
		b *= 3;
		inc();
	}
};

class C {
	int callC;
public:
	C() : callC(0) {}
	void inc() {
		callC++;
	}
	int getC() {
		return callC;
	}
protected:
	void func(int& c) {
		c *= 5;
		inc();
	}
};



class D: public A, public B, public C {
	int val;
public:
	D() :A(), B(), C(), val(1) {}
	void update_val(int new_val) {
		while (new_val >= 1) {
			if (new_val % 5 == 0) {
				new_val /= 5;
				C::func(val);
			}
			else if (new_val % 3 == 0) {
				new_val /= 3;
				B::func(val);
			}
			else {
				new_val /= 2;
				A::func(val);
			}
		}
	}
	void check(int);
};