#include <iostream>
using namespace std;

#include "MyQueue.cpp";


int main() {

	MyQueue q;
	
	for (int i = 100; i < 200; ++i) {
		q.push(i);
	}
	for (int i = 0; i < 50; ++i) {
		cout << q.poll() << endl;
	}
	for (int i = 200; i < 250; ++i) {
		q.push(i);
	}
	while (!q.isEmpty() ) {
		cout << q.poll() << endl;
	}
	

}