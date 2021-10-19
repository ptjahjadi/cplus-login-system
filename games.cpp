#include <iostream>
#include <cstring>
#include <fstream>
#include <stdlib.h>
#include <cctype>
#include <map>
#include <math.h>
#include "functions.h"
using namespace std;

// Function to output game instructions, launch the game, and update user balance post-game
AccountDetails play_game(AccountDetails play_account, int account_number, string game_number) {
    int bet_amount;
    #if _WIN32  
        system("cls");
    #else
        system("clear");
    #endif
    // Show the instructions of the game depending on the game played
    announce_game(play_account, game_number);
    do {
        // Ask users to input bet amount. It must be higher than 0 and must not exceed their existing balance
        cin >> bet_amount;
        #if _WIN32  
            system("cls");
        #else
            system("clear");
        #endif

        if (bet_amount == 0) {
            return play_account;
        }

        // Play the game if the bet amount is valid
        if (check_bet_validity(play_account, bet_amount)) {
            if (game_number == "1") {
                play_account = high_low(play_account, bet_amount);
            }
            else if (game_number == "2") {
                play_account = casino_war(play_account, bet_amount);
            }
            else if (game_number == "3") {
                play_account = blackjack(play_account, bet_amount);
            }
            // Update the user's account balance to the text file after any changes in their balance
            write_account_balance(play_account, account_number);
            cout << "Your balance is now " << play_account.balance << ". Would you like to play again? Input a new bet amount or 0 to exit.\n";
        }
    } while (bet_amount != 0);
    return play_account;
}

// Function to announce game instructions 
void announce_game (AccountDetails play_account, string game_number) {
    if (game_number == "1") {
        cout << "Welcome to High-Low! Here is how to play:\nYou bet a certain amount of money from your balance.\n"
        "You and the host will be generated a number between 1-20.\nYou win money equal to your bet if your number is higher than the host.\n"
        "You lose your bet if your number is lower than the host.\nYour bet is returned in case of a tie.\n\n"
        "How much would you like to bet? Your current balance is " << play_account.balance << ". Input 0 to exit.\n";
    }
    else if (game_number == "2") {
        cout << "Welcome to Casino War! Here is how to play:\nYou bet a certain amount of money from your balance.\n"
        "You and the host will receive a random playing card from 2 to A.\nThe order of value ascending is as follows:\n"
        "2, 3, 4, 5, 6, 7, 8, 9, 10, J, Q, K, A.\nYou win money equal to your bet if your card's value is higher than the host.\n"
        "You lose your bet if your card's value is lower than the host.\n"
        "In the case of a tie, you can double your bet and go to war with another round, or surrender with half your bet.\n"
        "During the war, you win credits equal to your original bet if your card is equal or more valuable than your host.\n\n"
        "How much would you like to bet? Your current balance is " << play_account.balance << ". Input 0 to exit.\n";
    }
    else if (game_number == "3") {
        cout << "Welcome to Blackjack! Here is how to play:\nYou will be given two cards. Each card has a value equal to the number of that card.\n"
        "Aces are worth 1, face cards (J, Q, K) are worth 10.\nThe host will also be given two cards, with one card revealed to you.\n"
        "You can hit and draw another card or stand.\nIf your total value is 22 or higher, you bust and lose your bet.\n"
        "After standing, the host will reveal their other card.\nThe host will stand on 17 or higher.\n"
        "If the host's total value is 22 or higher, they bust and you win your bet.\n"
        "When both players do not bust:\n- You win money equal to your bet if your total value is higher than the host.\n"
        "- You lose your bet if your total value is lower than the host.\n"
        "- Your bet is returned in case of a tie.\n"
        "How much would you like to bet? Your current balance is " << play_account.balance << ". Input 0 to exit.\n";
    }
}

// Function checks whether or not the player's bet is valid for playing
int check_bet_validity (AccountDetails play_account, int bet_amount) {
    if (bet_amount > play_account.balance) {
        cout << "\nYour bet is higher than your available balance. Your balance is " << play_account.balance << ". Please input a lower bet or 0 to exit.\n";
        return 0;
    }
    else if (bet_amount <= 0) {
        cout << "\nInvalid bet amount! Please input a bet higher than 0 or input 0 to exit:\n";
        return 0;
    }
    return 1;
}

// Function to play the high-low game
AccountDetails high_low(AccountDetails play_account, int bet_amount){
    // Generate a random number between 1-20 for both the player and the host
    srand(time(NULL));
    int player_number = rand() % 20 + 1; 
    int host_number = rand() % 20 + 1;
    cout << "\nYour number is " <<  player_number << ".\n";
    cout << "The host's number is " << host_number << ".\n\n";
    // Update the account's balance depending on the results
    if (player_number > host_number) {
        cout << "You win " << bet_amount << " credits!\n\n\n";
        play_account.alter_balance(bet_amount);
    }
    else if (player_number == host_number) {
        cout << "It's a tie! Your bet is returned.\n\n\n";
    }
    else {
        cout << "You lose " << bet_amount << " credits!\n\n\n";
        play_account.alter_balance(-bet_amount);
    }
    return play_account;
}

// Function to play casino war
AccountDetails casino_war(AccountDetails play_account, int bet_amount) {
    // Create a map that associate each card with a value
    map<string, int> cw_value = {{"2", 2}, {"3", 3}, {"4", 4}, {"5", 5}, 
    {"6", 6}, {"7", 7}, {"8", 8}, {"9", 9}, {"10", 10}, {"J", 11}, {"Q", 12},
    {"K", 13}, {"A", 14}};

    // Generate a random card for the player and the host
    string card_possibilities[PLAYING_CARD_VAL_SIZE] = {"2", "3", "4", "5", "6", "7", "8", "9",
    "10", "J", "Q", "K", "A"};
    srand(time(NULL));
    int player_number = rand() % PLAYING_CARD_VAL_SIZE;
    string player_card = card_possibilities[player_number];
    int host_number = rand() % PLAYING_CARD_VAL_SIZE;
    string host_card = card_possibilities[host_number];

    cout << "\nYour card is " << player_card <<".\n";
    cout << "The host's card is " << host_card <<".\n\n";

    // Update the account's balance depending on the results
    if (cw_value[player_card] > cw_value[host_card]) {
        cout << "You win " << bet_amount << " credits!\n\n\n";
        play_account.alter_balance(bet_amount);
    }
    else if (cw_value[player_card] < cw_value[host_card]) {
        cout << "You lose " << bet_amount << " credits!\n\n\n";
        play_account.alter_balance(-bet_amount);
    }
    else {
        // In case of a tie, check whether the user can go to war with another bet
        if (play_account.balance >= 2*bet_amount) {
            string tie_decision;
            cout << "It's a tie! Do you want to go to war by betting " << bet_amount << " credits, or surrender and receive only " << (bet_amount/2) << " credits?\n"
            "Input 1 to go to war. Input 0 to surrender.\n";
            do {
                cin >> tie_decision;
                // Go to war, generating another card for the user and the host
                if (tie_decision == "1") {
                    string player_card = card_possibilities[rand() % PLAYING_CARD_VAL_SIZE];
                    string host_card = card_possibilities[rand() % PLAYING_CARD_VAL_SIZE];
                    cout << "\nYour card is " << player_card <<".\n";
                    cout << "The host's card is " << host_card <<".\n\n";

                    if (cw_value[player_card] >= cw_value[host_card]) {
                        cout << "You win " << bet_amount << " credits!\n\n\n";
                        play_account.alter_balance(bet_amount);
                    }
                    else if (cw_value[player_card] < cw_value[host_card]) {
                        cout << "You lose " << (2*bet_amount) << " credits!\n\n\n";
                        play_account.alter_balance(-(2*bet_amount));
                    }
                }
                // Surrender 
                else if (tie_decision == "0") {
                    cout << "You lose " << (1 + bet_amount/2) << " credits and " << (bet_amount/2) << " credits are returned to you.\n\n";
                    play_account.alter_balance(-ceil(1 + bet_amount/2));
                }
                else {
                    cout << "Invalid input! Input 1 to go to war. Input 0 to surrender.\n";
                }
            } while (tie_decision != "0" && tie_decision != "1");
        }

        // If the user can not afford to go to war, automatically surrender half the bet
        else {
            cout << "It's a tie! However you have insufficient funds to go to war, so you surrender by default and receive " << (bet_amount/2) << " credits.\n";
            play_account.alter_balance(-ceil(bet_amount/2));
        }
    }
    return play_account;
}

// Function to play blackjack
AccountDetails blackjack(AccountDetails play_account, int bet_amount) {
    // Create a map that associate each card with a value
    map<string, int> bj_value = {{"2", 2}, {"3", 3}, {"4", 4}, {"5", 5}, 
    {"6", 6}, {"7", 7}, {"8", 8}, {"9", 9}, {"10", 10}, {"J", 10}, {"Q", 10},
    {"K", 10}, {"A", 1}};

    string card_possibilities[PLAYING_CARD_VAL_SIZE] = {"2", "3", "4", "5", "6", "7", "8", "9",
    "10", "J", "Q", "K", "A"};

    // Generate two cards for the player
    srand(time(NULL));
    string player_card_one = card_possibilities[rand() % PLAYING_CARD_VAL_SIZE];
    string player_card_two = card_possibilities[rand() % PLAYING_CARD_VAL_SIZE];
    int player_value = bj_value[player_card_one] + bj_value[player_card_two];
    cout << "Your cards are " << player_card_one << " and " << player_card_two << ". Value: " << player_value << ".\n";

    // Generate two cards for the host and reveal the face-up card
    string host_card_facedown = card_possibilities[rand() % PLAYING_CARD_VAL_SIZE];
    string host_card_faceup = card_possibilities[rand() % PLAYING_CARD_VAL_SIZE];
    int host_value = bj_value[host_card_faceup];
    cout << "Host's faceup card is " << host_card_faceup << ". Value: " << host_value << ".\n\n";

    string bj_decision;
    cout << "Press 1 to hit and draw another card. Press 2 to stand.\n";
    do {
        cin >> bj_decision;
        if (bj_decision == "1") {
            string new_card = card_possibilities[rand() % PLAYING_CARD_VAL_SIZE];
            player_value += bj_value[new_card];
            cout << "\nYou draw " << new_card << ". Value: " << player_value << ".\n";
        }
        else if (bj_decision == "2") {
            break;
        }
        else {
            cout << "Invalid input.\n";
        }

        if (player_value > 21) {
            cout << "You busted. You lose " << bet_amount << " credits!\n\n\n";
            play_account.alter_balance(-bet_amount);
            return play_account;
        }

        cout << "Press 1 to hit and draw another card. Press 2 to stand.\n";

    } while (bj_decision != "2");

    host_value += bj_value[host_card_facedown];
    cout << "\nHost's facedown card is " <<   host_card_facedown << ". Value: " << host_value << ".\n";
    while (host_value < 17) {
        string new_card = card_possibilities[rand() % PLAYING_CARD_VAL_SIZE];
        host_value += bj_value[new_card];
        cout << "Host draws " << new_card << ". Value: " << host_value << ".\n";
        if (host_value > 21) {
            cout << "Host busted. You win " << bet_amount << " credits!\n\n\n";
            play_account.alter_balance(bet_amount);
            return play_account;
        }
    }

    cout << "Host stands.\n\n";
    if (player_value > host_value) {
        cout << "You win " << bet_amount << " credits!\n\n\n";
        play_account.alter_balance(bet_amount);
    }
    else if (player_value < host_value) {
        cout << "You lose " << bet_amount << " credits!\n\n\n";
        play_account.alter_balance(-bet_amount);
    }
    else {
        cout << "It's a tie. Your bet is pushed and returned.\n\n\n";
    }
    return play_account;
}


// Function to update the account's balance to the text file after playing
void write_account_balance(AccountDetails login_account, int account_number) {
    int line_num = 0;
    fstream loginfile;
    loginfile.open("loginfile.txt", ios::in);

    // Create a new temporary file that contains the user's final balance
    fstream new_loginfile;
    new_loginfile.open("loginfile2.txt", ios::app);
    string line;
    string update_account = string(login_account.user_id) + "," + string(login_account.user_password) + "," + to_string(login_account.balance) + ",";
    // Rewrite the contents of the old file and update the account that has logged in
    while (loginfile >> ws, getline(loginfile, line)) {
        if (line_num != account_number) {
            new_loginfile << line << endl;
            line_num += 1;
        }
        else {
            new_loginfile << update_account << endl;
            line_num += 1;
       }
    }
    // Remove the old login file and replace it with the updated one
    loginfile.close();
    new_loginfile.close();
    remove("loginfile.txt");
    rename("loginfile2.txt", "loginfile.txt");
} 
