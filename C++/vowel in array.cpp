#include <iostream>
using namespace std;

int main() {
    char vowels[5] = {'a', 'e', 'i', 'o', 'u'};
    int i = 0;

    cout << "Vowels are: ";
    while (i < 5) {
        cout << vowels[i] << " ";
        i++;
    }

    cout << endl;

    return 0;
}
