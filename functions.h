#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED    

#include <string>
using namespace std;

// Assume that the longest possible input is 999 characters long
#define MAX_LENGTH 999

// There are 13 different values between 2 and A.
#define PLAYING_CARD_VAL_SIZE 13

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

    void alter_balance(int winnings) {
        balance = balance + winnings;
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
void account_activity(AccountDetails login_account, int account_number);\
AccountDetails play_game(AccountDetails play_account, int account_number, string game_number);
void announce_game (AccountDetails play_account, string game_number);
int check_bet_validity (AccountDetails play_account, int bet_amount);
AccountDetails high_low(AccountDetails play_account, int bet_amount);
AccountDetails casino_war(AccountDetails play_account, int bet_amount);
AccountDetails blackjack(AccountDetails play_account, int bet_amount);
void write_account_balance(AccountDetails login_account, int account_number);

#endif