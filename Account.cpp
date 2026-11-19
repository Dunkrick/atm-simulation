#include "Account.h"
#include <iomanip>

Account::Account() {
  accountNumber = 0;
  accountHolder = "";
  pin = 0;
  balance = 0;
}

Account::Account(long long accNo, string holder, int userPin,
                 long long initialBalance) {
  accountNumber = accNo;
  accountHolder = holder;
  pin = userPin;
  balance = initialBalance;
}

bool Account::verifyPIN(int enteredPin) { return pin == enteredPin; }

void Account::checkBalance() {
  cout << "\n-----------------------------------\n";
  cout << "Current Balance : Rs. " << (balance / 100) << "." << setw(2)
       << setfill('0') << (balance % 100) << endl;
  cout << "-----------------------------------\n";
}

void Account::deposit(long long amount) {
  if (amount <= 0) {
    cout << "\nInvalid Deposit Amount!\n";
    return;
  }

  balance += amount;

  cout << "\n-----------------------------------\n";
  cout << "Amount Deposited Successfully.\n";
  cout << "Deposited Amount : Rs. " << (amount / 100) << "." << setw(2)
       << setfill('0') << (amount % 100) << endl;
  cout << "Available Balance : Rs. " << (balance / 100) << "." << setw(2)
       << setfill('0') << (balance % 100) << endl;
  cout << "-----------------------------------\n";
}

void Account::withdraw(long long amount) {
  if (amount <= 0) {
    cout << "\nInvalid Withdrawal Amount!\n";
    return;
  }

  if (amount > balance) {
    cout << "\nInsufficient Balance!\n";
    return;
  }

  balance -= amount;

  cout << "\n-----------------------------------\n";
  cout << "Withdrawal Successful.\n";
  cout << "Withdrawn Amount : Rs. " << (amount / 100) << "." << setw(2)
       << setfill('0') << (amount % 100) << endl;
  cout << "Available Balance : Rs. " << (balance / 100) << "." << setw(2)
       << setfill('0') << (balance % 100) << endl;
  cout << "-----------------------------------\n";
}

void Account::changePIN(int oldPin, int newPin) {
  if (pin != oldPin) {
    cout << "\nIncorrect Old PIN!\n";
    return;
  }

  if (newPin < 1000 || newPin > 9999) {
    cout << "\nPIN must be a 4-digit number.\n";
    return;
  }

  pin = newPin;

  cout << "\nPIN Changed Successfully.\n";
}

long long Account::getAccountNumber() { return accountNumber; }

string Account::getAccountHolder() { return accountHolder; }

int Account::getPIN() { return pin; }

long long Account::getBalance() { return balance; }

void Account::setPIN(int newPin) { pin = newPin; }

void Account::setBalance(long long newBalance) { balance = newBalance; }