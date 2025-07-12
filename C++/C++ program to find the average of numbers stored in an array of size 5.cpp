#include <iostream>
using namespace std;

int main() {
    int arr[5];
    int sum = 0;
    double average;

    cout << "Enter 5 integers:" << endl;

    for (int i = 0; i < 5; i++) {
        cin >> arr[i];
        sum += arr[i];
    }

    average = static_cast<double>(sum) / 5;

    cout << "The average of the array elements is: " << average << endl;

    return 0;
}
