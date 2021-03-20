#include <iostream>
using namespace std;

void obtainExpression(float&, float&, char&);
float addition(float, float);
float subtraction(float, float);
float multiplication(float, float);
float division(float, float);
int modulus(int a, int b);


int main() {
    float num1, num2, answer;
    char operator1;

    cout << "Simple Calculator\n";
    cout << "By Soh Jun Wei, A20EC0151\n\n";

    obtainExpression(num1, num2, operator1);

    if (operator1 == '+')
        cout << num1 << " + " << num2 << " = " << addition(num1, num2) << endl;
    else if (operator1 == '-')
        cout << num1 << " - " << num2 << " = " << subtraction(num1, num2) << endl;
    else if (operator1 == '*')
        cout << num1 << " * " << num2 << " = " << multiplication(num1, num2) << endl;
    else if (operator1 == '/')
        cout << num1 << " / " << num2 << " = " << division(num1, num2) << endl;
    else
        cout << num1 << " % " << num2 << " = " << modulus(num1, num2) << endl;

    return 0;
}



void obtainExpression(float& num1, float& num2, char& op) {
    cout << "First Number : ";
    cin >> num1;
    cout << "Second Number : ";
    cin >> num2;
    cout << "Please entrer the operation (+ , - , * , /, %) : ";
    cin >> op;
}


float addition(float a, float b) {
    return a + b;
}


float subtraction(float a, float b) {
    return a - b;
}


float multiplication(float a, float b) {
    return a * b;
}


float division(float a, float b) {
    return a / b;
}


int modulus(int a, int b) {
    return a % b;
}