#include <iostream>   // for standard input and output
#include <cstdlib>    // for system("cls") or system("clear"), used to clear the screen
#include <thread>     // for sleep_for function (to pause execution)
#include <chrono>     // for chrono::seconds (time duration)

using namespace std;

int main() {
    int number = 1;  // start from multiplication table of 1

    // infinite loop to keep printing tables
    while (true) {
        // Clear screen to make output cleaner (optional)
        // Works on Windows and Linux/Mac
#ifdef _WIN32
        system("cls");      // clears screen on Windows
#else
        system("clear");    // clears screen on Linux/Mac
#endif

        // print header for current multiplication table
        cout << "Multiplication Table for " << number << ":\n";
        cout << "-----------------------------\n";

        // loop to print 1 × number to 10 × number
        for (int i = 1; i <= 10; ++i) {
            cout << number << " * " << i << " = " << number * i << endl;
        }

        // display message to let user know how to stop
        cout << "\nPress Ctrl+C to stop.\n";

        // wait for 2 seconds before showing the next table
        this_thread::sleep_for(chrono::seconds(2));

        ++number; // move to the next number
    }

    return 0; // end of program (though never reached because of infinite loop)
}
