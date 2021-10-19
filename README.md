# CPLUS Login System
Create an account with this program and play games using your accounts!
## Aim
The aim of this project is to let users store their ID and passwords. Future work would include features that let users interact with their accounts. This program is written in C++.

The program is divided into phases (WIP):
* Phase 1A (12 May 2021): The program is able to store User ID and password to a file. Users would be able to register their accounts using this program.
* Phase 1B (14 May 2021): The program can read all the stored IDs and passwords in a file.
* Phase 1C (15 May 2021): Users can now login using their existing ID and password if they have already registered. The program will also prevent registration using existing user IDs.
* Phase 2A (19 Jul 2021): Several quality fixes such as allowing users to cancel registration and users would only receive one error message when the ID or password input using registration does not match the requirements. Added an account balance for each user and allows users to access their accounts after logging in. 
* Phase 2B (7 Aug 2021): Split the code into 3 files: the main file, function file, and header file. Users can now reset their password if they forgot their password after registering.
* Phase 2C (29 Aug 2021): Fixes to the reset password feature: the program does not accept password resets if the new password is too short, long or contains non-alphanumeric characters. New users must also confirm their password by entering it twice before registering.
* Phase 3A (18 Sep 2021): Included a new game "high-low", where users can play to win more balance. 
* Phase 3B (19 Oct 2021): Included two new games: "Casino War" and "Blackjack". Blackjack is currently in-development.

## Guide
* 'login' : Contains the program that is used to register or login to user's accounts.
* 'main.cpp': Contains the main function file, written in C++. This includes the main menu and prompt to register or login.
* 'games.cpp': Contains the code for all games implemented in this program.
* 'accounts.cpp': Contains the code to manage user accounts such as logging in and resetting password
* 'functions.h': Header file that contains all C++ macros, function prototypes and classes for this program.
* 'validity.cpp': Contains the functions used to check whether a user ID or password is valid for use.
* 'loginfile.txt': Contains the file that stores user ID and passwords. 

## Setting Up
This program is written using Visual Studio Code in Ubuntu, but can be run using any mainstream operating system and can be written in any IDE. 
In order to modify this program and compile it, pleasure ensure you have a G++ compiler. [Steven Zeil's tutorial](https://www.cs.odu.edu/~zeil/cs250PreTest/latest/Public/installingACompiler/) provides a great guide to set up the compiler.
Any command-line interpreter can be used to run the program (Windows CMD, Ubuntu Terminal, etc.).

## Future Work
Future updates for Phase 3C include developing two values for Aces (1 and 11, currently Ace has a value of only 1), and an insurance system when the host's face up card is an Ace for the BLackjack game.
