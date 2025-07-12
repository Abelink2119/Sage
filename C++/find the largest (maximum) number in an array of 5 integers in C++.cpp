#include <iostream>
using namespace std;

int main() {
    int arr[5];
    int max;

    cout << "Enter 5 integers:" << endl;

    for (int i = 0; i < 5; i++) {
        cin >> arr[i];
    }

    
    max = arr[0];

    for (int i = 1; i < 5; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }

    cout << "The largest number in the array is: " << max << endl;

    return 0;
}
