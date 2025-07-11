#include <iostream>
using namespace std;

int main() {
    double TC, TF;

    cout << "Enter temperature in Celsius: ";
    cin >> TC;

    TF = (TC * 9.0/5.0) + 32;

    cout << "Temperature in Fahrenheit: " << TF << endl;

    return 0;
}
