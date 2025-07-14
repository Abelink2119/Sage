#include <iostream>
using namespace std;

int main() {
    int n;

    cout << "Enter height of the Christmas tree: ";
    cin >> n;

    
    for (int i = 0; i < n-1; i++) cout << " ";
    cout << "*" << endl;

    
    for (int i = 1; i <= n; i++) {
        
        for (int j = 0; j < n - i; j++) {
            cout << " ";
        }
       
        for (int j = 0; j < 2 * i - 1; j++) {
            cout << "*";
        }
        cout << endl;
    }

    
    for (int i = 0; i < n - 1; i++) cout << " ";
    cout << "|" << endl;

    return 0;
}
