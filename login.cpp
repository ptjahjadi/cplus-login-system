#include <iostream>
#include <cstring>
#include <fstream>
#include <cctype>
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
    string decision;
    do {
        cout << "Welcome! What would you like to do?\nPress 1 to register.\nPress 2 to login.\nPress 0 to exit.\n";
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
            cout << "Input Error!\n\n";
        }
    } while (1);

    // Exits the program after user inputs 0
    cout << "\nThank you for using this login system.\n";
    return 0;
}

// Function to accept a new user's ID and password for registration to the system
void registration() {
    int i, num_accounts = 0;
    int id_exists = 0;
    AccountDetails new_user;

    // Find number of accounts registered in the file
    check_num_accounts(&num_accounts);
    AccountDetails* accounts = (AccountDetails*)malloc(sizeof(AccountDetails) * num_accounts);
    // Retrieve the details of all accounts registered in the file
    accounts = retrieve_account_details(accounts, num_accounts);
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

    // Ensure that the user ID is alphanumeric and between 5 to 20 characters
    do { 
        cin >> new_user.my_id;
        new_user.id_len = strlen(new_user.my_id);
        id_exists = 0;
        for (i = 0; i < num_accounts; i++) {
            if (strcmp(new_user.my_id, accounts[i].my_id) == 0) {
                cout << "User ID already exists. Please input a different user ID.\n";
                id_exists = 1;
                break;
            }   
        }
        if (new_user.id_len < 5 && id_exists == 0) {
            cout << "User ID is too short. Please input a user ID between 5-20 characters:\n";
        }
        if (new_user.id_len > 20 && id_exists == 0) {
            cout << "User ID is too long. Please input a user ID between 5-20 characters:\n";
        }
        if (!check_alnum(new_user.my_id) && id_exists == 0){
            cout << "User ID has to be alphanumeric:\n";
        }
    } while (new_user.id_len < 5 || new_user.id_len > 20 || !check_alnum(new_user.my_id) || id_exists == 1);


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
    free(accounts);
}   

// Function to let user login after they registered
void login() {
    char* my_id = (char*)malloc(sizeof(char) * MAX_LENGTH);
    char* my_password = (char*)malloc(sizeof(char) * MAX_LENGTH);
    int num_accounts = 0;
    int account_number = -1;
    int i;
    // Find number of accounts registered in the file
    check_num_accounts(&num_accounts);
    AccountDetails* accounts = (AccountDetails*)malloc(sizeof(AccountDetails) * num_accounts);
    // Retrieve the details of all accounts registered in the file
    accounts = retrieve_account_details(accounts, num_accounts);

    #if _WIN32
        system("cls");
    #else
        system("clear");
    #endif

    cout << "Welcome back! Please input your user ID or press 0 to exit:\n";

    // Check whether the ID input by the user matches a registered ID, or if they would like to exit
    do {
        cin >> my_id;
        for (i = 0; i < num_accounts; i++) {
            if (strcmp(my_id, accounts[i].my_id) == 0) {
                account_number = i;
            }
        }
        // Exit loop if the input matches a registered ID
        if (account_number != -1) {
            break;
        }
        // Exit loop if the user presses 0 and would like to go back
        if (strcmp(my_id, "0") == 0) {
            #if _WIN32
                system("cls");
            #else
                system("clear");
            #endif
            break;
        }
        cout << "ID not found. Please enter a registered ID or press 0 to exit:\n";
    } while (1);


    if (account_number != -1) {

        // Check whether the password input matches the ID's registered password, or if they would like to exit
        cout << "\nWelcome back, " << my_id << ". Please enter your password or press 0 to exit:\n";
        do {
            cin >> my_password;
            // Exit loop if the input matches the registered password
            if (strcmp(my_password, accounts[account_number].my_password) == 0) {
                break;
            }
            // Exit loop if the user presses 0 and would like to go back
            if (strcmp(my_password, "0") == 0) {
            #if _WIN32  
                system("cls");
            #else
                system("clear");
            #endif
                break;
            }
            cout << "Your password is incorrect! Please try again or press 0 to exit.\n";
        } while (1);   

        if (strcmp(my_password, accounts[account_number].my_password) == 0) {
            cout << "Your password is correct!\n";
        }
    }
    free(my_id);
    free(my_password);
    free(accounts);
}

// Function to check whether there are punctuations or prohibited characters in a string
int check_alnum(char* string_check){
    int i;
    int string_length = strlen(string_check);
    // Return 0 if any of the characters in the string are non-alphanumeric
    for (i = 0; i < string_length; i++) {
        if(!isalnum(string_check[i])) {
            return 0;
        }
    }
    return 1;
}

// Function to check how many registered accounts are recorded in the file
void check_num_accounts(int *num_accounts) {
    fstream loginfile;
    loginfile.open("loginfile.txt", ios::in);
    string placeholder;
    while (getline(loginfile, placeholder)) {
        *num_accounts += 1;
    }
    loginfile.close();
}

// Function to retrieve all registered user ID and passwords 
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

    // Alternate between recording user ID and password
    // Remove whitespaces (ws) when reading the file
    while (loginfile >> ws, getline(loginfile, text, ',')) {
        if (account_detail == "id") {
            strcpy(accounts[account_number].my_id, text.c_str());
            accounts[account_number].id_len = strlen(accounts[account_number].my_id);
            account_detail = "pass";    
        }
        else {
            strcpy(accounts[account_number].my_password, text.c_str());
            accounts[account_number].pass_len = strlen(accounts[account_number].my_password);
            account_detail = "id";
            account_number += 1;
        }
    }
    loginfile.close();
    return accounts;
}