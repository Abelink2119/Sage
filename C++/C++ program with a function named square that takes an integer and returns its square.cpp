#include <iostream>
using namespace std;

// Function to calculate square of a number
int square(int n) {
    return n * n;
}

int main() {
    int num;

    cout << "Enter an integer: ";
    cin >> num;

    cout << "The square of " << num << " is: " << square(num) << endl;

    return 0;
}
