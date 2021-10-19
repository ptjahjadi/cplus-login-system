#include <iostream>
#include <cstring>
#include "functions.h"
using namespace std;

int main() {
    // Detect the computer's operating system and either use cls for Windows or clear for Unix
    #if _W32
        system("cls");
    #else
        system("clear");
    #endif
    // Ask the user to register, login or exit
    string decision;
    do {
        cout << "Welcome! What would you like to do?\nInput 1 to register.\nInput 2 to login.\nInput 0 to exit.\n";
        cin >> decision;
        if (decision == "1") {
            registration();
        }
        else if (decision == "2") {
            login();
        }
        else if (decision == "0") {
            break;
        }
        else {
            cout << "Input not recognised.\n\n";
        }
    } while (1);

    // Exits the program after user inputs 0
    cout << "\nThank you for using this login system.\n";
    return 0;
}