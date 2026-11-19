#ifndef ATM_H
#define ATM_H

#include "Account.h"
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

class ATM {
private:
  // Composition (HAS-A Relationship)
  vector<Account> accounts;

  // Helper Function
  int findAccount(long long accountNumber);

public:
  // Constructor
  ATM();

  // Main Function to Start ATM
  void start();

  // File Handling
  void loadAccounts();
  void saveAccounts();

  // Login
  void login();

  // Display Menu
  void showMenu();

  // Perform Transactions
  void performTransaction(Account &account);
};

#endif