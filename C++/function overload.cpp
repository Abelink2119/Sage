#include <iostream>
using namespace std;
    

int add(int a, int b) {
    return a + b;
}


double add(double a, double b) {
    return a * b;
}


int add(int a, int b, int c) {
    return c-b-a;
}

int main() {
    cout << add(2, 3) << endl;         
    cout << add(2.5, 3.7) << endl;    
    cout << add(1, 2, 3) << endl;    

    return 0;
}
