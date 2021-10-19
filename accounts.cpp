#include <iostream>
#include <cstring>
#include <fstream>
#include <stdlib.h>
#include <cctype>
#include "functions.h"
using namespace std;

// Function to accept a new user's ID and password for registration to the system
void registration() {
    int num_accounts = 0;   
    AccountDetails new_user;

    // Find number of accounts registered in the file
    check_num_accounts(&num_accounts);
    AccountDetails* accounts = (AccountDetails*)malloc(sizeof(AccountDetails) * num_accounts);
    // Retrieve the details of all accounts registered in the file
    accounts = retrieve_account_details(accounts, num_accounts);
    // Open the file containing user ID and passwords for appending
    fstream loginfile;
    loginfile.open("loginfile.txt", ios::app);
    
    new_user.user_id = (char*)malloc(sizeof(char) * MAX_LENGTH);
    new_user.user_password = (char*)malloc(sizeof(char) * MAX_LENGTH);
    char* password_confirm = (char*)malloc(sizeof(char) * MAX_LENGTH);

    #if _WIN32
        system("cls");
    #else
        system("clear");
    #endif

    cout << "Welcome! Please input your desired user ID (5-20 characters) or input 0 to exit:\n";

    // Ensure that the user ID is alphanumeric and between 5 to 20 characters
    do { 
        cin >> new_user.user_id;
        // Back to home page when user inputs 0
        if (strcmp(new_user.user_id, "0") == 0) {
            #if _WIN32
                system("cls");
            #else
                system("clear");
            #endif
            free(new_user.user_id);
            free(new_user.user_password);
            free(password_confirm);
            free(accounts);
            return;
        }
        new_user.id_len = strlen(new_user.user_id);
    } while (!check_id_validity(new_user.user_id, new_user.id_len, num_accounts, accounts));

    cout << "\nPlease set your password (5-20 characters) or input 0 to exit:\n";
    int pass_validity;

    // Ensure that the password is alphanumeric and between 5 to 20 characters
    do {
        cin >> new_user.user_password;
        // Back to home page when user inputs 0
        if (strcmp(new_user.user_password, "0") == 0) {
            #if _WIN32
                system("cls");
            #else
                system("clear");
            #endif
            free(new_user.user_id);
            free(new_user.user_password);
            free(password_confirm);
            free(accounts);
            return;
        }
        new_user.pass_len = strlen(new_user.user_password);

        // Ask user to confirm password by entering the password again
        cout << "\nPlease enter your password again to confirm:\n";
        cin >> password_confirm;

        if (strcmp(new_user.user_password, password_confirm)) {
            cout << "\nThe passwords do not match. Please enter a new password or press 0 to exit:\n";
            pass_validity = 0;
        }
        else {
            pass_validity = check_password_validity(new_user.user_password, new_user.pass_len);
        }
    } while (!pass_validity);

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
            }
        }
        // Exit loop if the user presses 0 and would like to go back
        if (strcmp(my_id, "0") == 0) {
            #if _WIN32
                system("cls");
            #else
                system("clear");
            #endif
            free(my_id);
            free(my_password);
            free(accounts);
            return;
        }
        else if (account_number == -1) {
            cout << "\nID not found. Please enter a registered ID or press 0 to exit:\n";
        }
    } while (account_number == -1);

    // Check whether the password input matches the ID's registered password, or if they would like to exit
    cout << "\nWelcome back, " << my_id << ". Please enter your password or press 0 to exit:\n";
    cout << "(Forgot your password? Input 1 to reset your password.)\n";

    while (1) {
        cin >> my_password;
        // Ask for account activity if the input matches the registered password
        if (strcmp(my_password, accounts[account_number].user_password) == 0) {
            #if _WIN32
                system("cls");
            #else
                system("clear");
            #endif
            account_activity(accounts[account_number], account_number);
            break;
        }

        // Exit loop if the user presses 0 and would like to go back
        else if (strcmp(my_password, "0") == 0) {
            #if _WIN32  
                system("cls");
            #else
                system("clear");
            #endif
                break;
        }

        // If the user inputs 1, assist the user in resetting their password
        else if (strcmp(my_password, "1") == 0) {
            #if _WIN32  
                system("cls");
            #else
                system("clear");
            #endif
            reset_password(accounts[account_number], account_number);
            break;
        }

        else {
        cout << "\nYour password is incorrect! Please try again or input 0 to exit. Input 1 if you forgot your password.\n";
        }
    }
    free(my_id);
    free(my_password);
    free(accounts);
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
AccountDetails* retrieve_account_details(AccountDetails* accounts, int num_accounts){
    int i;
    int account_number = 0;
    for (i = 0; i < num_accounts; i++) {
        accounts[i].user_id = (char*)malloc(sizeof(char) * MAX_LENGTH);
        accounts[i].user_password = (char*)malloc(sizeof(char) * MAX_LENGTH);
    }

    fstream loginfile;
    loginfile.open("loginfile.txt", ios::in);
    string detail;
    string account_detail = "id";

    // Alternate between recording user ID, password and account balance
    // Remove whitespaces (ws) when reading the file
    while (loginfile >> ws, getline(loginfile, detail, ',')) {
        if (account_detail == "id") {
            // Convert text into a C string to be copied to the accounts class (string to char*)
            strcpy(accounts[account_number].user_id, detail.c_str());
            accounts[account_number].id_len = strlen(accounts[account_number].user_id);
            account_detail = "pass";    
        }
        else if (account_detail == "pass") {
            strcpy(accounts[account_number].user_password, detail.c_str());
            accounts[account_number].pass_len = strlen(accounts[account_number].user_password);
            account_detail = "balance";
        }
        else if (account_detail == "balance") {
            accounts[account_number].balance = stoi(detail);
            account_detail = "id";
            account_number += 1 ;
        }
    }
    loginfile.close();
    return accounts;
}

// Function to reset a registered user's password
void reset_password(AccountDetails reset_account, int account_number) {
    char* new_password = (char*)malloc(sizeof(char) * MAX_LENGTH);
    char* new_password_confirm = (char*)malloc(sizeof(char) * MAX_LENGTH);
    int pass_validity, new_pass_len;
    cout << "Enter a new password or press 0 to exit:\n";

    do {
        cin >> new_password;
        // Return back to home page if user inputs 0
        if (strcmp(new_password, "0") == 0) {
            #if _WIN32  
                system("cls");
            #else
                system("clear");
            #endif
            free(new_password);
            free(new_password_confirm);
            return;
        }
        // Ask user to confirm password by entering the password again
        cout << "\nPlease enter your password again to confirm:\n";
        cin >> new_password_confirm;
        // Ask user to confirm password again if the passwords do not match
        if (strcmp(new_password, new_password_confirm)) {
            cout << "\nThe passwords do not match. Please enter a new password or press 0 to exit:\n";
            pass_validity = 0;
        }
        // Ask user to choose a new password if the user inputs their current password
        else if (strcmp(new_password, reset_account.user_password) == 0) {
            cout << "\nThis password is currently in use. Please enter a new password or press 0 to exit:\n";
            pass_validity = 0;
        }
        // Check if the newly input password is valid
        else {
            new_pass_len = strlen(new_password);
            pass_validity = check_password_validity(new_password, new_pass_len);
        }
    } while (!pass_validity);

    // Create a new temporary file that replaces the old user password with a new password
    fstream loginfile;
    loginfile.open("loginfile.txt", ios::in);
    fstream new_loginfile;
    new_loginfile.open("loginfile2.txt", ios::app);
    string line;
    int line_num = 0;
    string update_password = string(reset_account.user_id) + "," + string(new_password) + "," + to_string(reset_account.balance) + ",";
    while (loginfile >> ws, getline(loginfile, line)) {
        // Replace the password for the account in question
        if (line_num == account_number) {
            new_loginfile << update_password << endl;
            line_num += 1;
        }
        // Preserve details of all other accounts
        else {
            new_loginfile << line << endl;
            line_num += 1;
        }
    }
    
    // Remove the old login file and replace it with the updated one
    loginfile.close();
    new_loginfile.close();
    remove("loginfile.txt");
    rename("loginfile2.txt", "loginfile.txt");
    cout << "Your password has been changed. You can now login with your new password.\n\n";
}

// Function to let users interact with their account after successfully logging in
void account_activity(AccountDetails login_account, int account_number) {
    string decision;
    do {
        cout << "Welcome, " << login_account.user_id << "! Your current balance is " << login_account.balance <<". What would you like to do?\nInput 1 to play High-Low.\nInput 2 to play Casino War.\nInput 3 to play Blackjack.\nInput 0 to exit.\n";
        cin >> decision;
        // Let users play high-low
        if (decision == "1" || decision == "2" || decision == "3") {
            login_account = play_game(login_account, account_number, decision);
        }
        // Render other input as invalid
        else if (decision != "0") {
            cout << "Input error!\n\n"; 
        }
    } while (decision != "0");

    #if _WIN32  
        system("cls");
    #else
        system("clear");
    #endif
}

