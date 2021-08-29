#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

class AccountDetails {
    public:
        char* user_id; // user ID
        char* user_password; // user password
        int id_len; // length of user ID
        int pass_len; // length of user password
        int balance; // balance of the user account
    
    // Function to initialise account balance. Default is 100.
    void initialise_balance() {
        balance = 100;
    }
};  

void registration();
void login();
int check_id_validity(char* user_id, int id_len, int num_accounts, AccountDetails* accounts);
int check_password_validity(char* user_password, int pass_len);
int check_alnum(char* string_check);
void check_num_accounts(int *num_accounts);
AccountDetails* retrieve_account_details (AccountDetails* accounts, int num_accounts);
void reset_password(AccountDetails reset_account, int account_number);
void account_activity(AccountDetails login_account);

#endif