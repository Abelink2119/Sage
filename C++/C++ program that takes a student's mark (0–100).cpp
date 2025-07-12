#include <iostream>
using namespace std;

int main() {
    int mark;

    cout << "Enter student's mark  (0 - 100): ";
    cin >> mark;

    if (mark >= 50) {
        cout << "Pass" << endl;
    } else {
        cout << "Fail" << endl;
    }

    return 0;
}
