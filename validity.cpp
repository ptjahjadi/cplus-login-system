#include <iostream>
#include <cstring>
#include "functions.h"
using namespace std;

// Function to check whether the input ID for registration is valid
int check_id_validity(char* user_id, int id_len, int num_accounts, AccountDetails* accounts) {
    // Ensure that the user ID has not been taken by someone else
    int i;
    for (i = 0; i < num_accounts; i++) {
        if (strcmp(user_id, accounts[i].user_id) == 0) {
            cout << "\nUser ID already exists. Please input a different user ID or input 0 to exit.\n";
            return 0;
        }
    }
    if (id_len < 5) {
        cout << "\nUser ID is too short. Please input a user ID between 5-20 characters or input 0 to exit.\n";
        return 0;
    }
    else if (id_len > 20) {
        cout << "\nUser ID is too long. Please input a user ID between 5-20 characters or input 0 to exit.\n";
        return 0;
    }
    else if (!check_alnum(user_id)) {
        cout << "\nUser ID has to be alphanumeric. Please input a user ID between 5-20 characters or input 0 to exit.\n";
        return 0;
    }
    return 1;
}

// Function to check whether the input password for registration or reset is valid
int check_password_validity(char* user_password, int pass_len) {
    if (pass_len < 5) {
        cout << "\nPassword is too short. Please input a password between 5-20 characters or input 0 to exit.\n";
        return 0;
    }
    else if (pass_len > 20) {
        cout << "\nPassword is too long. Please input a password between 5-20 characters or input 0 to exit.\n";
        return 0;
    }
    else if (!check_alnum(user_password)) {
        cout << "\nPassword has to be alphanumeric. Please input a password between 5-20 characters or input 0 to exit. \n";
        return 0;
    }
    return 1;
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