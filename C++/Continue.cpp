#include <iostream>
using namespace std;

int main() {
    double TC, TF;

    while (true) {
        cout << "Enter temperature in Celsius (999 to quit): ";
        cin >> TC;

        // check for exit
        if (TC == 999) {
            cout << "Exiting program.\n";
            break;
        }

        // skip invalid (negative) temperatures
        if (TC < 0) {
            cout << "Negative temperatures are not allowed. Try again.\n";
            continue;
        }

        TF = (TC * 9.0/5.0) + 32;
        cout << "Temperature in Fahrenheit: " << TF << endl;
    }

    return 0;
}
