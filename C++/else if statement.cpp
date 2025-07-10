#include <iostream>
using namespace std;

int main() {
    int age;

    cout << "Enter your age: ";
    cin >> age;

    if (age < 0) {
        cout << "Age can't be negative!" << endl;
    } else if (age > 18) {
        cout << "Adult" << endl;
    } else {
        cout << "Not Adult" << endl;
    }

    return 0;
}
