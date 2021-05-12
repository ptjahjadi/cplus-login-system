#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;

void registration();

int main() {
    // Detect the computer's operating system and either use cls for Windows or clear for Unix
    #if _WIN32
        system("cls");
    #else
        system("clear");
    #endif

    // Ask the user to register, login or exit
    int decision;
    do {
        cout << "Welcome! What would you like to do?\nPress 1 to register.\nPress 2 to login.\nPress 0 to exit.\n";
        cin >> decision;
        if (decision == 1) {
            registration();
        }
        else if (decision == 2) {
        }
        else if (decision == 0) {
            break;
        }
        else {
            cout << "Input Error!\n\n";
        }
    } while (decision != 0);

    // Exits the program after user inputs 0
    cout << "\nThank you for using this login system.\n";
    return 0;
}

// Function to accept a new user's ID and password for registration to the system
void registration() {
    char* my_id;
    char* my_password;

    //Open the file containing user ID and passwords for appending
    fstream loginfile;
    loginfile.open("loginfile.txt", ios::app);
    
    // Maximum ID and password length is 20
    int max_limit = 21;
    my_id = (char*)malloc(sizeof(char) * max_limit);
    my_password = (char*)malloc(sizeof(char) * max_limit);

    #if _WIN32
        system("cls");
    #else
        system("clear");
    #endif

    cout << "Welcome, new user. Please input your user ID (min. 5 characters and max. 20 characters):\n";
    cin >> my_id;
    while (strlen(my_id) < 5 || strlen(my_id) > 20) { 
        if (strlen(my_id) < 5) {
            cout << "User ID is too short. Please input a user ID between 5-20 characters:\n";
            cin >> my_id;
        }
        if (strlen(my_id) > 20) {
            cout << "User ID is too long. Please input a user ID between 5-20 characters:\n";
            cin >> my_id;
        }
    }
    cout<<"\nPlease set your password (min. 5 characters and max. 20 characters):\n";
    cin>>my_password;
    while (strlen(my_password) < 5 || strlen(my_password) > 20) { 
        if (strlen(my_password) < 5) {
            cout << "Password is too short. Please input a password between 5-20 characters:\n";
            cin >> my_password;
        }
        if (strlen(my_id) > 20) {
            cout << "Password is too long. Please input a password between 5-20 characters:\n";
            cin >> my_password;
        }
    }
    cout << "\nYour details are " << my_id << " and " << my_password << ".\n\n";

    //Append the new user's ID and password to the system
    loginfile<<my_id<<"\t"<<my_password<<endl;
    loginfile.close();
}   
