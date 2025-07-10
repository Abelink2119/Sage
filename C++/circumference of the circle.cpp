#include <iostream>
using namespace std;

int main() {
    const double PI = 3.141592653589793;
    double r, c;

    cout << "Enter the radius of the circle: ";
    cin >> r;

    c = 2 * PI * r;

    cout << "The circumference of the circle is: " << c << endl;

    return 0;
}
