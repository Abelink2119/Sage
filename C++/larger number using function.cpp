#include <iostream>
using namespace std;

void findLarger(int num1, int num2) {
    if (num1 > num2) {
        cout << "Larger number is: " << num1 << endl;
    } else if (num2 > num1) {
        cout << "Larger number is: " << num2 << endl;
    } else {
        cout << "Both numbers are equal." << endl;
    }
}

int main() {
    int num1, num2;

    cout << "Enter first number: ";
    cin >> num1;

    cout << "Enter second number: ";
    cin >> num2;

    
    findLarger(num1, num2);

    return 0;
}
