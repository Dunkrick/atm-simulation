#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <iostream>
#include <string>

using namespace std;

class Account {
private:
  long long accountNumber;
  string accountHolder;
  int pin;
  long long balance;

public:
  // Constructor
  Account();
  Account(long long accNo, string holder, int userPin,
          long long initialBalance);

  // Authentication
  bool verifyPIN(int enteredPin);

  // Banking Operations
  void checkBalance();
  void deposit(long long amount);
  void withdraw(long long amount);
  void changePIN(int oldPin, int newPin);

  // Getter Functions
  long long getAccountNumber();
  string getAccountHolder();
  int getPIN();
  long long getBalance();

  // Setter Functions
  void setPIN(int newPin);
  void setBalance(long long newBalance);
};

#endif