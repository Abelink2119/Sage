#include <iostream>
using namespace std;

// Function to calculate base^exponent using a loop
int power(int base, int exponent) {
    int result = 1;
    for (int i = 1; i <= exponent; i++) {
        result *= base;
    }
    return result;
}

int main() {
    int base, exponent;

    cout << "Enter base: ";
    cin >> base;

    cout << "Enter exponent (non-negative integer): ";
    cin >> exponent;

    if (exponent < 0) {
        cout << "Exponent should be a non-negative integer." << endl;
    } else {
        cout << base << "^" << exponent << " = " << power(base, exponent) << endl;
    }

    return 0;
}
