#include <iostream>
using namespace std;

double celsiusToFahrenheit(double TC) {
    return (TC * 9.0/5.0) + 32;
}

int main() {
    double TC, TF;

    cout << "Enter temperature in Celsius: ";
    cin >> TC;

    TF = celsiusToFahrenheit(TC);

    cout << "Temperature in Fahrenheit: " << TF << endl;

    return 0;
}
