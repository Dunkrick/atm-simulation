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
  double balance;

public:
  // Constructor
  Account();
  Account(long long accNo, string holder, int userPin, double initialBalance);

  // Authentication
  bool verifyPIN(int enteredPin);

  // Banking Operations
  void checkBalance();
  void deposit(double amount);
  void withdraw(double amount);
  void changePIN(int oldPin, int newPin);

  // Getter Functions
  long long getAccountNumber();
  string getAccountHolder();
  int getPIN();
  double getBalance();

  // Setter Functions
  void setPIN(int newPin);
  void setBalance(double newBalance);
};

#endif