#include <iostream>
using namespace std;

int main() {
    int number;
    int sum = 0;

    cout << "Enter numbers (enter 0 to stop):" << endl;

    do {
        cin >> number;
        sum += number;
    } while (number != 0);

    cout << "The sum of all entered numbers is: " << sum << endl;

    return 0;
}
