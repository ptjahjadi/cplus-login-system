#include <iostream>
#include <cstring>
#include <fstream>
#include <cctype>
using namespace std;

// Maximum ID and password length is 20
#define MAX_LENGTH 21

class AccountDetails {
    public:
        char* user_id; // user ID
        char* user_password; // user password
        int id_len; // length of user ID
        int pass_len; // length of user password
        float balance;
    
    // Function to initialise account balance. Default is 100.
    void initialise_balance() {
        balance = 100;
    }
};  

void registration();
void login();
int check_alnum(char* string_check);
void check_num_accounts(int *num_accounts);
AccountDetails* retrieve_account_details (AccountDetails* accounts, int num_accounts);
void account_activity(char* user_id, char* user_password, float *user_balance);

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
    

    new_user.user_id = (char*)malloc(sizeof(char) * MAX_LENGTH);
    new_user.user_password = (char*)malloc(sizeof(char) * MAX_LENGTH);

    #if _WIN32
        system("cls");
    #else
        system("clear");
    #endif

    cout << "Welcome! Please input your desired user ID (5-20 characters) or input 0 to exit:\n";

    // Ensure that the user ID is alphanumeric and between 5 to 20 characters
    do { 
        cin >> new_user.user_id;
        new_user.id_len = strlen(new_user.user_id);
        id_exists = 0;
        // Ensure that the user ID has not been taken by someone else
        for (i = 0; i < num_accounts; i++) {
            if (strcmp(new_user.user_id, accounts[i].user_id) == 0) {
                cout << "User ID already exists. Please input a different user ID or input 0 to exit.\n";
                id_exists = 1;
                break;
            }   
        }
        if (strcmp(new_user.user_id, "0") == 0) {
            #if _WIN32
                system("cls");
            #else
                system("clear");
            #endif
            return;
        }
        if (new_user.id_len < 5 && id_exists == 0) {
            cout << "User ID is too short. Please input a user ID between 5-20 characters or input 0 to exit.\n";
        }
        else if (new_user.id_len > 20 && id_exists == 0) {
            cout << "User ID is too long. Please input a user ID between 5-20 characters or input 0 to exit.\n";
        }
        else if (!check_alnum(new_user.user_id) && id_exists == 0){
            cout << "User ID has to be alphanumeric. Please input a user ID between 5-20 characters or input 0 to exit.";
        }
    } while (new_user.id_len < 5 || new_user.id_len > 20 || !check_alnum(new_user.user_id) || id_exists == 1);

    cout << "\nPlease set your password (5-20 characters) or input 0 to exit:\n";
    
    // Ensure that the password is alphanumeric and between 5 to 20 characters
    do {
        cin >> new_user.user_password;
        new_user.pass_len = strlen(new_user.user_password);
        if (strcmp(new_user.user_password, "0") == 0) {
            #if _WIN32
                system("cls");
            #else
                system("clear");
            #endif
            return;
        }
        if (new_user.pass_len < 5) {
            cout << "Password is too short. Please input a password between 5-20 characters or input 0 to exit.\n";
        }
        else if (new_user.pass_len > 20) {
            cout << "Password is too long. Please input a password between 5-20 characters or input 0 to exit.\n";
        }
        else if (!check_alnum(new_user.user_password)) {
            cout << "Password has to be alphanumeric. Please input a password between 5-20 characters or input 0 to exit. \n";
        }
    } while (new_user.pass_len < 5 || new_user.pass_len > 20 || !check_alnum(new_user.user_password));

    new_user.initialise_balance();
    cout << "\nYour user ID is " << new_user.user_id << " and your password is " << new_user.user_password << ".\n";
    cout << "To get started, you'll get " << new_user.balance << " balance.\n\n";

    // Append the new user's ID and password to the system
    loginfile << new_user.user_id << "," << new_user.user_password << "," << new_user.balance << "," << endl;
    loginfile.close();
    free(new_user.user_id);
    free(new_user.user_password);
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
            if (strcmp(my_id, accounts[i].user_id) == 0) {
                account_number = i;
                break;
            }
        }
        // Exit loop if the user presses 0 and would like to go back
        if (strcmp(my_id, "0") == 0) {
            #if _WIN32
                system("cls");
            #else
                system("clear");
            #endif
            return;
        }
        cout << "ID not found. Please enter a registered ID or press 0 to exit:\n";
    } while (account_number == -1);

    // Check whether the password input matches the ID's registered password, or if they would like to exit
    cout << "\nWelcome back, " << my_id << ". Please enter your password or press 0 to exit:\n";
    do {
        cin >> my_password;
        // Ask for account activity if the input matches the registered password
        if (strcmp(my_password, accounts[account_number].user_password) == 0) {
            #if _WIN32
                system("cls");
            #else
                system("clear");
            #endif
            account_activity(accounts[account_number].user_id, accounts[account_number].user_password, &accounts[account_number].balance);
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
    string line;
    // Check number of lines in loginfile, and save the string to line (as a placeholder)
    while (getline(loginfile, line)) {
        *num_accounts += 1;
    }
    loginfile.close();
}

// Function to retrieve all registered user ID and passwords 
AccountDetails* retrieve_account_details (AccountDetails* accounts, int num_accounts){
    int i;
    int account_number = 0;
    for (i = 0; i < num_accounts; i++) {
        accounts[i].user_id = (char*)malloc(sizeof(char) * MAX_LENGTH);
        accounts[i].user_password = (char*)malloc(sizeof(char) * MAX_LENGTH);
    }

    fstream loginfile;
    loginfile.open("loginfile.txt", ios::in);
    string text;
    string account_detail = "id";

    // Alternate between recording user ID, password and account balance
    // Remove whitespaces (ws) when reading the file
    while (loginfile >> ws, getline(loginfile, text, ',')) {
        if (account_detail == "id") {
            // Convert text into a C string to be copied to the accounts class (string to char*)
            strcpy(accounts[account_number].user_id, text.c_str());
            accounts[account_number].id_len = strlen(accounts[account_number].user_id);
            account_detail = "pass";    
        }
        else if (account_detail == "pass") {
            strcpy(accounts[account_number].user_password, text.c_str());
            accounts[account_number].pass_len = strlen(accounts[account_number].user_password);
            account_detail = "balance";
        }
        else if (account_detail == "balance") {
            accounts[account_number].balance = stof(text);
            account_detail = "id";
            account_number += 1 ;
        }
    }
    loginfile.close();
    return accounts;
}

// Function to let users interact with their account after successfully logging in
void account_activity(char* user_id, char* user_password, float *user_balance) {
    string decision;
    do {
        cout << "Welcome, " << user_id << "! Your current balance is " << *user_balance <<". What would you like to do?\nPress 0 to exit.\n";
        cin>>decision;
        if (decision == "0") {
            break;
        }
        else {
            cout << "Input error!\n\n";
        }
    } while (1);
    #if _WIN32  
        system("cls");
    #else
        system("clear");
    #endif
}
