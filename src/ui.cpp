#include "../include/ui.h"
#include <iostream>
#include <conio.h>

using namespace std;

void showMenu() {
    cout << "========================\n";
    cout << "TRANSACTION SYSTEM\n";
    cout << "1 LOGIN\n";
    cout << "2 REGISTER\n";
    cout << "3 REGISTER FOR MANAGER\n";
    cout << "PRESS 1/2/3\n";
    cout << "========================\n";
}

void showTransactionMenu() {
    cout << "========================\n";
    cout << "TRANSACTION SYSTEM\n";
    cout << "1 CHANGE PASSWORD\n";
    cout << "...\n";
    cout << "PRESS 1/...\n";
    cout << "========================\n";
}

char getMenuChoice() {
    return _getch();
}

void showRegisterScreen() {
    cout << ">> REGISTER SYSTEM <<\n";
}

void showLoginScreen() {
    cout << ">> LOGIN SYSTEM <<\n";
}

void showRegisterScreenForMnger() {
	cout << ">> REGISTER SYSTEM FOR MANAGER <<\n";
}
string getInput(const string& prompt) {
    cout << prompt;
    string input;
    getline(cin, input);
    return input;
}

void showMessage(const string& message) {
    cout << message << "\n";
}

void showChangePasswordScreen() {
	cout << ">> CHANGE YOUR INFORMATION <<\n";
}

void showChanginPassScreen() {
    cout << ">> CHANGING PASSWORD <<\n";
}