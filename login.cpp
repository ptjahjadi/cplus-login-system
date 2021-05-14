#include <iostream>
#include <cstring>
#include <fstream>
#include <ctype.h>
using namespace std;

// Maximum ID and password length is 20
#define MAX_LENGTH 21
#define MAX_LIMIT 99

class AccountDetails {
    public:
        char* my_id; // user ID
        char* my_password; // user password
        int id_len; // length of user ID
        int pass_len; // length of user password
};  

void registration();
void login();
int check_alnum(char* string_check);
void check_num_accounts(int *num_accounts);
AccountDetails* retrieve_account_details (AccountDetails* accounts, int num_accounts);

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
            login();
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
    AccountDetails new_user;

    //Open the file containing user ID and passwords for appending
    fstream loginfile;
    loginfile.open("loginfile.txt", ios::app);
    

    new_user.my_id = (char*)malloc(sizeof(char) * MAX_LENGTH);
    new_user.my_password = (char*)malloc(sizeof(char) * MAX_LENGTH);

    #if _WIN32
        system("cls");
    #else
        system("clear");
    #endif

    cout << "Welcome, new user. Please input your user ID (min. 5 characters and max. 20 characters):\n";
    cin >> new_user.my_id;
    new_user.id_len = strlen(new_user.my_id);

    // Ensure that the user ID is alphanumeric and between 5 to 20 characters
    while (new_user.id_len < 5 || new_user.id_len > 20 || !check_alnum(new_user.my_id)) { 
        if (new_user.id_len < 5) {
            cout << "User ID is too short. Please input a user ID between 5-20 characters:\n";
            cin >> new_user.my_id;
        }
        if (new_user.id_len > 20) {
            cout << "User ID is too long. Please input a user ID between 5-20 characters:\n";
        }
        if (!check_alnum(new_user.my_id)){
            cout << "User ID has to be alphanumeric:\n";
        }
        cin >> new_user.my_id;
    }
    cout << "\nPlease set your password (min. 5 characters and max. 20 characters):\n";
    cin >> new_user.my_password;
    new_user.pass_len = strlen(new_user.my_password);
    
    // Ensure that the password is alphanumeric and between 5 to 20 characters
    while (new_user.pass_len < 5 || new_user.pass_len > 20 || !check_alnum(new_user.my_password)) { 
        if (new_user.pass_len < 5) {
            cout << "Password is too short. Please input a password between 5-20 characters:\n";
            cin >> new_user.my_password;
        }
        if (new_user.pass_len > 20) {
            cout << "Password is too long. Please input a password between 5-20 characters:\n";
            cin >> new_user.my_password;
        }
        if (!check_alnum(new_user.my_password)) {
            cout << "Password has to be alphanumeric:\n";
        }
        cin >> new_user.my_password;
    }
    cout << "\nYour user ID is " << new_user.my_id << " and your password is " << new_user.my_password << ".\n\n";

    // Append the new user's ID and password to the system
    loginfile << new_user.my_id << "," << new_user.my_password << "," << endl;
    loginfile.close();
    free(new_user.my_id);
    free(new_user.my_password);
}   

// Function to let user login after they registered
void login() {
    char* my_id = (char*)malloc(sizeof(char) * MAX_LENGTH);
    char* my_password = (char*)malloc(sizeof(char) * MAX_LENGTH);
    int num_accounts = 0;
    check_num_accounts(&num_accounts);
    AccountDetails* accounts = (AccountDetails*)malloc(sizeof(AccountDetails) * num_accounts);
    accounts = retrieve_account_details(accounts, num_accounts);
    cout << "Welcome back! Please input your user ID\n";
    cin >> my_id;
}

int check_alnum(char* string_check){
    int i;
    int string_length = strlen(string_check);
    for (i = 0; i < string_length; i++) {
        if(!isalnum(string_check[i])) {
            return 0;
        }
    }
    return 1;
}

void check_num_accounts(int *num_accounts) {
    fstream loginfile;
    loginfile.open("loginfile.txt", ios::in);
    string placeholder;
    while (getline(loginfile, placeholder)) {
        *num_accounts += 1;
    }
    loginfile.close();
}

AccountDetails* retrieve_account_details (AccountDetails* accounts, int num_accounts){
    int i;
    int account_number = 0;
    for (i = 0; i < num_accounts; i++) {
            accounts[i].my_id = (char*)malloc(sizeof(char) * MAX_LENGTH);
            accounts[i].my_password = (char*)malloc(sizeof(char) * MAX_LENGTH);
        }

    fstream loginfile;
    loginfile.open("loginfile.txt", ios::in);
    string text;
    string account_detail = "id";
    while (loginfile >> ws, getline(loginfile, text, ',')) {
        if (account_detail == "id") {
            strcpy(accounts[account_number].my_id, text.c_str());
            account_detail = "pass";
        }
        else {
            strcpy(accounts[account_number].my_password, text.c_str());
            account_detail = "id";
            account_number += 1;
        }
    }
    return accounts;
}